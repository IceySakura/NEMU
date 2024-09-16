#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	DATA_TYPE_S src = op_src->val; // imm
	DATA_TYPE_S dest = op_dest->val; // r/m
	DATA_TYPE_S result = dest - src;
	OPERAND_W(op_dest, result);
	// update EFLAGS
	update_eflags_pf_zf_sf(result);
	print_asm_template2();
}

make_instr_helper(rm_imm)

#include "cpu/exec/template-end.h"