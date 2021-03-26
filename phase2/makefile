run:  scanner.l lib.c
	yacc -d -v  parser.y 
	lex scanner.l
	gcc lex.yy.c lib.c y.tab.c -o al

clean:
	rm -f *.o al lex.yy.c y.tab.c y.tab.h parser.h parser.c y.output scanner.c
