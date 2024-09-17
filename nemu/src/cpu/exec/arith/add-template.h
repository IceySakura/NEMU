#include "cpu/exec/template-start.h"

#define instr add

static void do_execute () {
	DATA_TYPE_S src = op_src->val;
	DATA_TYPE_S dest = op_dest->val;
	DATA_TYPE_S result = dest + src;
	OPERAND_W(op_dest, result);
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"