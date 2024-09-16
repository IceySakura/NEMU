#include "cpu/exec/template-start.h"

#define instr je
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.ZF == 1) {
		cpu.eip += displacement;
		if(ops_decoded.is_operand_size_16) {
			cpu.eip = cpu.eip & 0xffff;
		}
	}
	print_asm_template1();
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"