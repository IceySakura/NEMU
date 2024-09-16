#include "cpu/exec/template-start.h"

#define instr add

static void do_execute () {
	DATA_TYPE result = op_dest->val + (int8_t)op_src->val;
	OPERAND_W(op_dest, result);
}

make_instr_helper(rm_imm)

#include "cpu/exec/template-end.h"