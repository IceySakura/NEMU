#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	DATA_TYPE_S src = op_src->val;
	DATA_TYPE_S dest = op_dest->val;
	DATA_TYPE_S result = dest - src;
	Log("src = %d, dest = %d, result = %d", src, dest, result);
	// update EFLAGS
	update_eflags_pf_zf_sf((int32_t)result);
//	cpu.eflags.CF = (DATA_TYPE)dest < (DATA_TYPE)src;
//	cpu.eflags.OF = MSB(dest) != MSB(result);
	cpu.eflags.CF = result > op_dest->val;
	cpu.eflags.OF = MSB((op_dest->val ^ op_src->val) & (op_dest->val ^ result));
	print_asm_template2();
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(i2a)
make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"