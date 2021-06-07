run:  scanner.l  parser.y
	yacc -d -v  parser.y 
	lex scanner.l
	gcc  lex.yy.c y.tab.c "Symboltable_functions/symbolTable.c" "general_functions/lib.c" "bison_functions/bison_functions.c" "instructions/instructions.c" "quads/quads.c" -o al

clean:
	rm -f *.o  lex.yy.c y.tab.c y.tab.h parser.h parser.c y.output scanner.c 

make avm:
	gcc "vm/vm.c" "vm/exec_arith/exec_arith.c" "vm/exec_funcs/exec_funcs.c" "vm/exec_jumps/exec_jumps.c" "vm/exec_other/exec_assign.c" "vm/exec_other/exec_nop.c" "vm/exec_tables/exec_tables.c"  "general_functions/lib.c" "vm/tables.c" -o vm_exec 
