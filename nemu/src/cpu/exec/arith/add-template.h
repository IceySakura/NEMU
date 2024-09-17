#include "cpu/exec/template-start.h"

#define instr add

static void do_execute () {
	DATA_TYPE result = op_dest->val + op_src->val;
	OPERAND_W(op_dest, result);
}

make_instr_helper(rm_imm)
make_instr_helper(i2a)

#include "cpu/exec/template-end.h"