run:  scanner.l  parser.y
	yacc -d -v  parser.y 
	lex scanner.l
	gcc lex.yy.c y.tab.c "Symboltable_functions/symbolTable.c" "general_functions/lib.c" "bison_functions/bison_functions.c" "quads/quads.c" -o al

clean:
	rm -f *.o  lex.yy.c y.tab.c y.tab.h parser.h parser.c y.output scanner.c 
