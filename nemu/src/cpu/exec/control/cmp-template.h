#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	DATA_TYPE_S src = op_src->val;
	DATA_TYPE_S dest = op_dest->val;
	DATA_TYPE_S result = dest - src;
	// update EFLAGS
	update_eflags_pf_zf_sf((int32_t)result);
	cpu.eflags.CF = dest < src;
	cpu.eflags.OF = MSB(dest) != MSB(src) && MSB(dest) != MSB(result);
	print_asm_template2();
}

make_instr_helper(rm_imm)
make_instr_helper(i2a)
make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(rm2r)
make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"