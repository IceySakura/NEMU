#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);

/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_help(char *args);

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

// Execute for N steps, N default for 1
static int cmd_si(char *args)
{
	int n;
	if(args == NULL)
	{
		n = 1;
	}
	else
	{
		sscanf(args, "%d", &n);
	}
	cpu_exec(n);
	return 0;
}

// Display register value or watchpoint value
static int cmd_info(char *args)
{
	if(args == NULL)
	{
		printf("info r, display register value.\n");
		printf("info w, display watchpoint value.\n");
	}
	else if(args[0] == 'r')
	{
		printf("eax\t\t0x%08x\t\t%d\n", cpu.eax, cpu.eax);
		printf("ecx\t\t0x%08x\t\t%d\n", cpu.ecx, cpu.ecx);
		printf("ebx\t\t0x%08x\t\t%d\n", cpu.ebx, cpu.ebx);
		printf("edx\t\t0x%08x\t\t%d\n", cpu.edx, cpu.edx);
		printf("esi\t\t0x%08x\t\t%d\n", cpu.esi, cpu.esi);
		printf("edi\t\t0x%08x\t\t%d\n", cpu.edi, cpu.edi);
		printf("ebp\t\t0x%08x\t\t%d\n", cpu.ebp, cpu.ebp);
		printf("esp\t\t0x%08x\t\t%d\n", cpu.esp, cpu.esp);
		printf("eip\t\t0x%08x\t\t%d\n", cpu.eip, cpu.eip);
	}
	return 0;
}

// Display ram value
static int cmd_x(char *args)
{
	int n;
	swaddr_t addr;
	sscanf(args, "%d %x", &n, &addr);
	int i;
	for(i = 0; i < n; i++)
	{
		if(i % 4 == 0)
		{
			printf("0x%08x: ", addr + i * 4);
		}
		printf("0x%08x ", swaddr_read(addr + i * 4, 4));
		if(i % 4 == 3)
		{
			printf("\n");
		}
	}
	if(i % 4 != 0)
	{
		printf("\n");
	}
	return 0;
}

// Calculate expr value
static int cmd_p(char *args)
{
	bool success = true;
	uint32_t result = expr(args, &success);
	if(success)
	{
		printf("0x%08x\n", result);
	}
	else
	{
		printf("Invalid expression.\n");
	}
	return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Execute for N steps, N default for 1", cmd_si},
	{ "info", "Display register value or watchpoint value", cmd_info},
	{ "x", "Display ram value", cmd_x},
	{ "p", "Calculate expr value", cmd_p},

	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
