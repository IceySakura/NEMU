#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute() {
	cpu.esp = cpu.ebp;
	cpu.ebp = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	print_asm_template1();
}

make_helper(concat(leave_, SUFFIX)) {
	do_execute();
	return 1;
}

#include "cpu/exec/template-end.h"