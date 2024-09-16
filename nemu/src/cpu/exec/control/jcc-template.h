#include "cpu/exec/template-start.h"

#define instr je
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.ZF == 1)
		cpu.eip += displacement;
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jbe
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.CF == 1 || cpu.eflags.ZF == 1)
		cpu.eip += displacement;
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jb
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.CF == 1)
		cpu.eip += displacement;
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jle
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.ZF == 1 || cpu.eflags.SF != cpu.eflags.OF)
		cpu.eip += displacement;
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#define instr jl
static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	if (cpu.eflags.SF != cpu.eflags.OF)
		cpu.eip += displacement;
	print_asm_template1();
}
make_instr_helper(i)
#undef instr

#include "cpu/exec/template-end.h"