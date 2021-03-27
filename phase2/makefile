run:  scanner.l symbolTable.c parser.y
	yacc -d -v  parser.y 
	lex scanner.l
	gcc lex.yy.c y.tab.c symbolTable.c lib.c -o al

clean:
	rm -f *.o  lex.yy.c y.tab.c y.tab.h parser.h parser.c y.output scanner.c 
