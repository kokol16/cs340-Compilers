%{
#include"symbolTable.h"
#include <stdio.h>
#include "lib.h"
extern FILE * yyin;
extern int yylineno; 
int func_line=0;
SymbolTable *  symbolTable;
FILE *output_file;
int yylex(void);
int yyerror( char * msg );
unsigned int  scope=0;

%}
%union {
    
	int num;
    float real;
	char * str;
}
%start program
%token <num> NUMBER
%token <real> REAL
%token <str> ID
%token  <str>  IF ELSE WHILE FOR FUNCTION RETURN  BREAK CONTINUE AND  NOT  OR  LOCALL TRUE FALSE NIL STRING EQUALS PLUS
%token <str>ASSIGN MINUS UMINUS ASTERISK DIVISION PERCENT DIFFERENT PLUS_PLUS MINUS_MINUS GREATER LESS GREATER_EQUALS LESS_EQUALS
%token <str>SEMICOLON COMMA COLON DOUBLE_COLON DOT Diaeresis LEFT_BRACE RIGHT_BRACE LEFT_SQUARE RIGHT_SQUARE LEFT_BRACKETS RIGHT_BRACKETS  

%right ASSIGN
%left OR
%left AND 
%nonassoc EQUALS DIFFERENT  
%nonassoc GREATER GREATER_EQUALS LESS_EQUALS LESS
%left PLUS MINUS
%left ASTERISK  PERCENT DIVISION
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT Diaeresis
%left LEFT_SQUARE RIGHT_SQUARE
%left LEFT_BRACKETS RIGHT_BRACKETS

/*%type <num> expr
%type <num> assignexpr
%type <num> term*/

%%         
program: statements   ;
stmt:   expr SEMICOLON   {}  /*trexei xwris to SEMICOLON*/
        | ifstmt 
        | whilestmt 
        | forstmt 
        | returnstmt 
        | BREAK SEMICOLON
        | CONTINUE SEMICOLON
        | block
        | funcdef
        |SEMICOLON
        ;
statements: statements stmt
            |stmt;

expr:   assignexpr
        |expr PLUS expr
        |expr MINUS expr
        |expr ASTERISK expr
        |expr DIVISION expr
        |expr PERCENT expr
        |expr GREATER expr
        |expr GREATER_EQUALS expr
        |expr LESS  expr
        |expr LESS_EQUALS expr
        |expr EQUALS expr
        |expr DIFFERENT expr
        |expr AND expr
        |expr OR expr
        | term;

        

term:   LEFT_BRACKETS expr RIGHT_BRACKETS
        | MINUS expr %prec UMINUS
        | NOT expr
        | PLUS_PLUS lvalue
        | lvalue PLUS_PLUS
        | MINUS_MINUS lvalue
        | lvalue MINUS_MINUS
        | primary ;

assignexpr: lvalue ASSIGN expr  {}

primary:  lvalue
          | call
          | objectdef
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS 
          | const ;

lvalue:   ID                    {
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    //printf("%s\n",$2);               
                                    //fprintf(stderr,"$1 : %s  scope : %d line : %d\n",$1,scope,yylineno);
                                    var = create_var($1,scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                
                                    if(!symbolTable_lookup_exists(symbolTable,scope,(char * )$1))
                                    {
                                            symbolTable_insert(symbolTable ,bucket );   
                                    }
                                    else
                                    {
                                        //printf("im here for : %s in line %d in scope %d \n", $1,yylineno,(scope-1));
                                        if (!symbolTable_lookup_exists_exact_scope(symbolTable,0,$1)  && symbolTable_lookup_function(symbolTable , scope-1))
                                        {

                                            print_Red(); fprintf(stderr,"error no access to this variable in line :%d \n",yylineno); reset_Red();
                                        }
                                        //eisai prosbasimos?
                                        
                                    }

                                
                                
                                }
          | LOCALL ID           {  
                                    printf("lala2222\n");
                                    
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    //printf("%s\n",$2);               

                                    var = create_var($2,scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                    if (!symbolTable_lookup_exists_exact_scope(symbolTable,  scope,(const char*)$2)    )                               
                                    {
                                        if(is_library_func(symbolTable,(const char*)$2) ) 
                                        {
                                            print_Red(); fprintf(stderr,"error conflict with library function in line :%d \n",yylineno); reset_Red();
                                        }
                                        else
                                        {
                                            symbolTable_insert(symbolTable, bucket);

                                        }
                                    }
                                   
                                        //error 


                                }
          | DOUBLE_COLON ID     {   
                                    if(!symbolTable_lookup_exists_exact_scope(symbolTable,0,(char*)$2) ) {
                                    print_Red(); 
                                    fprintf(stderr,"global variable doesnt exist\n"); 
                                    reset_Red();
                                    }
                                }
          | member ;

member:    lvalue DOT ID
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE
            | call DOT ID
            | call LEFT_SQUARE expr RIGHT_SQUARE ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS
            | lvalue callsuffix
            | LEFT_BRACKETS funcdef RIGHT_BRACKETS LEFT_BRACKETS elist RIGHT_BRACKETS;

callsuffix: normcall
            | methodcall ;

normcall: LEFT_BRACKETS elist RIGHT_BRACKETS;

methodcall:    Diaeresis ID LEFT_BRACKETS elist RIGHT_BRACKETS; /* equivalent to lvalue.ID'('lvalue, elist')';*/

elist:   expr    
        | expr COMMA elist
        |    ;
            
objectdef: LEFT_SQUARE  elist  RIGHT_SQUARE
           |LEFT_SQUARE  indexed  RIGHT_SQUARE
           |LEFT_SQUARE  RIGHT_SQUARE ;

indexed:    indexedelem  
            | indexedelem COMMA  indexed
            |   ;

indexedelem: LEFT_BRACE expr COLON expr RIGHT_BRACE;

block: LEFT_BRACE {scope++;}  RIGHT_BRACE  {symbolTable_hide(symbolTable, scope); scope--;}       
       |LEFT_BRACE {scope++;}  statements  RIGHT_BRACE {symbolTable_hide(symbolTable, scope); scope--;} ;  
       
block_func: LEFT_BRACE  RIGHT_BRACE  {symbolTable_hide(symbolTable, scope); scope--;}       
       |LEFT_BRACE   statements  RIGHT_BRACE {symbolTable_hide(symbolTable, scope); scope--;} ;  
  

funcdef: FUNCTION   ID {func_line=yylineno;} LEFT_BRACKETS {scope++;}  idlist RIGHT_BRACKETS block_func {
                                                                    Function * func;
                                                                    Variable **arguments;
                                                                    SymbolTableEntry ** arguments_buckets;
                                                                    unsigned int size;
                                                                   // printf("%s\n",);
                                                                    arguments=sanitize_arguments((char*)$4, &size,scope,func_line);
                                                                    //printf("scope : %d ,line : %d\n",scope,func_line);
                                                                    SymbolTableEntry * bucket;
                                                                    printf("func name : %d\n",USERFUNC);
                                                                    func=create_func($2 , scope , func_line,arguments,size);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    print_args(func);
                                                                    if (!symbolTable_lookup_exists(symbolTable,  scope,(const char*)$2) )
                                                                    {
                                                                        if(arguments!=NULL)//no argumens provided
                                                                        {
                                                                            arguments_buckets=create_arguments_buckets(arguments,size);
                                                                            symbolTable_insert_args(symbolTable ,arguments_buckets,size);
                                                                        }
                                                                       
                                                                        symbolTable_insert(symbolTable, bucket);

                                                                    } 
                                                                    //free(arguments);


                                                                    }
                                                                
         |FUNCTION LEFT_BRACKETS {scope++;} idlist RIGHT_BRACKETS block_func {
                                                                    Function * func;
                                                                    Variable **arguments;
                                                                    SymbolTableEntry ** arguments_buckets;
                                                                    unsigned int size;

                                                                    arguments=sanitize_arguments((char*)$2, &size,scope,yylineno);
                                                                    SymbolTableEntry * bucket;
                                                                    func=create_func(NULL , scope , yylineno,arguments,size);
                                                                    bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                                                                    //print_args(func);
                                                                    print_args(func);

                                                                    if(arguments!=NULL)//no argumens provided
                                                                    {
                                                                        arguments_buckets=create_arguments_buckets(arguments,size);
                                                                        symbolTable_insert_args(symbolTable ,arguments_buckets,size);
                                                                    }
                                                                       
                                                                    symbolTable_insert(symbolTable, bucket);

                                                                     
                                                                    //free(arguments);
                                                                    }


const: NUMBER | STRING | NIL | TRUE | FALSE;

idlist: ID  { /*printf("%s:",$1); printf("lineee2 : %d\n",yylineno);*/}
        | ID { /*printf("%s:",$1); printf( "lineee : %d\n",yylineno)*/ }  COMMA idlist { /*printf("lineee : %d\n",yylineno);*/ }
        |   ;

ifstmt: IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt  ELSE stmt   { /*printf("if statement\n");*/ }
        | IF LEFT_BRACKETS expr RIGHT_BRACKETS stmt; 
whilestmt: WHILE LEFT_BRACKETS expr RIGHT_BRACKETS stmt;

forstmt:  FOR LEFT_BRACKETS elist SEMICOLON  expr SEMICOLON  elist RIGHT_BRACKETS stmt;

returnstmt: RETURN expr SEMICOLON {/*printf("return\n");*/} 
            |  RETURN SEMICOLON;


%%

int yyerror( char * msg )
{
    print_Red();
    fprintf(stderr ,"%s in line : %d \n", msg,yylineno);
    reset_Red();

}
int main(int argc , char * argv[])
{
    if(argc==2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"error can't read file\n");
            return -1;
        }   
        
    }
    else if (argc>2)
    {
        if(!( yyin=fopen(argv[1],"r") )  )
        {
            fprintf(stderr,"error can't read file\n");
            return -1;
        } 
        output_file=fopen(argv[2],"w");
        if(output_file==NULL)
        {
            fprintf(stderr,"error can't open write file\n");
            return -1;
        }
    }
    else
    {
        yyin=stdin;
    }
  
    symbolTable = symbolTable_create();
    //yylex();
    //yyin=stdin;
    yyparse() ;
    //symbolTable_print(symbolTable);
    //symbolTable_print_scope_list(symbolTable, 1);

    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

