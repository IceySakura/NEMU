#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	cpu.eip = swaddr_read(cpu.esp, DATA_BYTE) - 1;
	cpu.esp += DATA_BYTE;
	if(DATA_BYTE == 2) cpu.eip &= 0xffff;
	print_asm("ret");
}

make_helper(concat3(instr, _, SUFFIX)) {
	do_execute();
	return 1;
}

#include "cpu/exec/template-end.h"