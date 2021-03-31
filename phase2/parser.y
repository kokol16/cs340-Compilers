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
short is_local_id=0;
int yyerror( char * msg );
unsigned int  scope=0;

%}
%union {
    
	float num;
    //float real;
	char * str;
}
%start program
%token <num> NUMBER
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

//%type <str> lvalue
//%type <str> member
/*%type <num> assignexpr
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

assignexpr: lvalue {               
                                    short status = symbolTable_lookup_exists(symbolTable,scope,yylval.str);
                                    if(status == ERROR_FUNC) {
                                         if(is_local_id){
                                           print_Red();
                                           fprintf(stderr, "error assign to function in line %d\n",yylineno);
                                           reset_Red();
                                         }
                                    }
                                    } ASSIGN  expr {is_local_id=0;}  
    
                                   


primary:  lvalue
          | call
          | objectdef
          | LEFT_BRACKETS funcdef RIGHT_BRACKETS 
          | const ;

lvalue:   ID                    {
                                     fprintf(stderr, "ID \n");  
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                  
                                    var = create_var($1,scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                
                                    if(symbolTable_lookup_exists(symbolTable,scope,(char * )$1)==0)
                                    {

                                            symbolTable_insert(symbolTable ,bucket );   
                                    }
                                    else
                                    {
                                        /*if (symbolTable_lookup_exists_exact_scope(symbolTable,0,$1)==0  && symbolTable_lookup_function(symbolTable , scope-1) 
                                        && symbolTable_lookup_exists_exact_scope(symbolTable,scope,$1)==0  )*/
                                        unsigned int tmp_scope=1,func_scope=-1,id_scope;
                                        short  is_function_blocking=1;
                                        while(tmp_scope<scope)
                                        {
                                            if (symbolTable_lookup_function(symbolTable , tmp_scope) )
                                            {
                                                func_scope=tmp_scope;

                                            }
                                            tmp_scope++;
                                        }
                                        //fprintf(stderr, "fun scope : %d\n",func_scope);
                                        if(func_scope==-1) is_function_blocking=0;
                                        else
                                        {
                                            id_scope =find_bucket_scope(symbolTable,$1);
                                            //fprintf(stderr, "id scope : %d\n",id_scope);

                                            if(id_scope==-1) { fprintf(stderr,"lalalala\n"); is_function_blocking=1;}
                                            else if(id_scope <= func_scope) {is_function_blocking=1;}
                                            else is_function_blocking=0;
                                        }   


                                        if (symbolTable_lookup_exists_exact_scope(symbolTable,0,$1)==0 || symbolTable_lookup_exists_exact_scope(symbolTable,0,$1)==ERROR_FUNC
                                         && is_function_blocking )
                                        {
                                                if ( !is_library_func(symbolTable,$1) )
                                                {
                                                    print_Red(); 
                                                    fprintf(stderr,"error no access to this variable  %s in line :%d \n",$1,yylineno); 
                                                    reset_Red();

                                                }
                                        }
                                        //eisai prosbasimos?
                                        
                                    }

                                
                                
                                }
          | LOCALL ID           {  
                                    short is_local_id=1;
                                    
                                    SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    //printf("%s\n",$2);               

                                    var = create_var($2,scope,yylineno);
                                    if(scope!=0) bucket=create_bucket_var( 1 ,  var  ,LOCAL );
                                    else bucket=create_bucket_var( 1 ,  var  ,GLOBAL );
                                    if (symbolTable_lookup_exists_exact_scope(symbolTable,  scope,(const char*)$2)==0    )                               
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
                                    if(symbolTable_lookup_exists_exact_scope(symbolTable,0,(char*)$2)==0 ) {
                                    print_Red(); 
                                    fprintf(stderr,"global variable doesnt exist in line %u \n",yylineno); 
                                    reset_Red();
                                    }
                                }
          | member ;

member:    lvalue DOT ID
            | lvalue LEFT_SQUARE expr RIGHT_SQUARE
            | call DOT ID
            | call LEFT_SQUARE expr RIGHT_SQUARE ;

call:      call LEFT_BRACKETS elist RIGHT_BRACKETS
            | lvalue callsuffix {   fprintf(stderr, "lvalue call suffix \n");              }
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
  

funcdef: FUNCTION   ID  {
                            Function * func;
                            SymbolTableEntry * bucket;
                            func=create_func($2 , scope , yylineno);
                            bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                            short status = symbolTable_lookup_exists_exact_scope(symbolTable,scope,$2);
                            if(is_library_func(symbolTable,$2))
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:formal shadows libfunc in line : %d\n",yylineno); 
                                    reset_Red();
                            }
                            else if (status==ERROR_FUNC )
                            {
                                    print_Red(); 
                                    fprintf(stderr,"error:function %s exists line : %d\n",$2,yylineno); 
                                    reset_Red();
                            }
                            else if(status==ERROR_VAR)
                            {
                                print_Red(); 
                                fprintf(stderr,"%s is variable line : %d \n",$2 ,yylineno); 
                                reset_Red();

                            }
                            else 
                            {
                                //fprintf(stderr,"staus : %d\n",status);
                                symbolTable_insert(symbolTable, bucket);
                            }
                            


                        } LEFT_BRACKETS {scope++;}  idlist {  create_arguments(symbolTable,$4,scope);      }  RIGHT_BRACKETS  block_func {

                                                                 


                                                                    }
                                                                
         |FUNCTION {Function * func;
                            SymbolTableEntry * bucket;
                            func=create_func(NULL , scope , yylineno);
                            bucket=create_bucket_func( 1 ,  func  ,USERFUNC );
                            symbolTable_insert(symbolTable, bucket);
                                                }
                            LEFT_BRACKETS {scope++;} idlist {  create_arguments(symbolTable,$3,scope);    } RIGHT_BRACKETS block_func 
                                                                    {
                                                                    
                                                                    }


const: NUMBER | STRING | NIL | TRUE | FALSE;

idlist: ID  { SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var($1,scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                    if(is_library_func(symbolTable,$1)){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc in line %d\n",yylineno); 
                                       reset_Red();
                                    }
                                    else  if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,$1)!=0){
                                        print_Red(); 

                                       fprintf(stderr,"error:formal redeclaration in line %d\n",yylineno); 
                                       reset_Red();

                                     } 
                                     else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
            }
        | ID {                      SymbolTableEntry * bucket;
                                    Variable * var  ;       
                                    var = create_var($1,scope,yylineno);
                                    bucket=create_bucket_var( 1 ,  var  ,FORMAL );
                                     if(symbolTable_lookup_exists_exact_scope(symbolTable,scope,$1)!=0){
                                        print_Red(); 
                                       fprintf(stderr,"error:formal redeclaration in line : %d\n",yylineno); 
                                       reset_Red();
                                     }else if(is_library_func(symbolTable,$1)){
                                        print_Red(); 

                                        fprintf(stderr,"error:formal shadows libfunc in line %d\n",yylineno); 
                                       reset_Red();

                                     }else{
                                       symbolTable_insert(symbolTable,bucket);
                                     }          
                                   
                                    }  COMMA idlist { /*printf("lineee : %d\n",yylineno);*/ }
        
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
    symbolTable_print_scopes(symbolTable,4);
    //if(output_file!=NULL)
    //fclose(output_file);
//    fclose(yyin);
}

