#include "cpu/exec/template-start.h"

#define instr setne
static void do_execute() {
	OPERAND_W(op_src, cpu.eflags.ZF == 0);
	print_asm_template1();
}
make_instr_helper(rm)
#undef instr

#include "cpu/exec/template-end.h"