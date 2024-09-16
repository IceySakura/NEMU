#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + DATA_BYTE + 1);
	cpu.eip += op_src->val;
	if(DATA_BYTE == 2) cpu.eip &= 0xffff;
	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"