#include "ic17out.h"

#include "ifj17builtins.c"

static void writeVariable(FILE *f, struct DIM *var)
{
	struct DIM value;
	struct TWCode def = {
		.instr = I_DEFVAR,
		.var1 = var,
	};
	struct TWCode assign = {
		.instr = I_MOVE,
		.var1 = var,
		.var2 = &value,
	};
	value = *var;
	value.frame = FRAME_CONST;
	writeInstuction(f, def);
	writeInstuction(f, assign);
}

static void writeVariables(FILE *f, struct tree *vars)
{
	struct tree_iter it;

	if (!vars)
		return;

	tree_iter_init(&it, vars);
	while (tree_iter_next(&it)) {
		writeVariable(f, it.item.payload);
	}
	tree_iter_tear(&it);
}


static void writeGetArgument(FILE *f, struct DIM *arg)
{
	struct DIM var;
	struct TWCode def = {
		.instr = I_DEFVAR,
		.var1 = &var,
	};
	struct TWCode pop = {
		.instr = I_POPS,
		.var1 = &var,
	};
	var = *arg;
	var.frame = FRAME_LOCAL;
	writeInstuction(f, def);
	writeInstuction(f, pop);
}

static void writeGetArguments(FILE *f, list *args)
{
	int i, n;
	struct DIM *arg;

	if (!args)
		return;

	n = list_size(args);
	for (i = 0; i < n; i++) {
		arg = list_index(args, i);
		writeGetArgument(f, arg);
	}
}

static void writeInstructions(FILE *f, list *ins)
{
	int i, n;
	struct TWCode *in;

	if (!ins)
		return;

	n = list_size(ins);
	for (i = 0; i < n; i++) {
		in = list_index(ins, i);
		writeInstuction(f, *in);
	}
}

static void writeDeclareReturn(FILE *f, struct DIM *var)
{
	if (!var || var->dataType == DATA_TYPE_VOID)
		return;

	fputs("DEFVAR LF@&ret\n", f);
	switch (var->dataType) {
		case DATA_TYPE_BOOL:
			fputs("MOVE LF@&ret bool@false\n", f);
			return;
		case DATA_TYPE_INT:
			fputs("MOVE LF@&ret int@0\n", f);
			return;
		case DATA_TYPE_DOUBLE:
			fputs("MOVE LF@&ret float@0.0\n", f);
			return;
		case DATA_TYPE_STRING:
			fputs("MOVE LF@&ret string@\n", f);
			return;
	}
}

static void writeFunction(FILE *f, struct Function *fn)
{
	if (!fn)
		return;

	fprintf(f, "LABEL %s\n", fn->name.str);
	fputs("CREATEFRAME\nPUSHFRAME\n", f);
	fputs("DEFVAR LF@&tmp1\nDEFVAR LF@&tmp2\n", f);
	writeDeclareReturn(f, fn->_return);
	// variable definitions
	writeVariables(f, fn->variables);

	writeGetArguments(f, fn->parameters);

	writeInstructions(f, fn->commands);

	// end of function
	fprintf(f, "LABEL %s%%&end\n", fn->name.str);
	if (fn->_return && fn->_return->dataType != DATA_TYPE_VOID)
		fputs("PUSHS LF@&ret\n", f);
	fputs("POPFRAME\nRETURN\n", f);
}

static void writeFunctions(FILE *f, struct tree *fns)
{
	struct tree_iter it;

	if (!fns)
		return;

	tree_iter_init(&it, fns);
	while (tree_iter_next(&it)) {
		writeFunction(f, it.item.payload);
	}
	tree_iter_tear(&it);
}

void writeProgram(FILE *f, struct Program *p)
{
	fputs(".IFJcode17\n", f);
	fputs("JUMP &%body\n", f);

	print_builtins(f);

	writeFunctions(f, p->functions);

	writeFunction(f, p->scope);
	fputs("LABEL &%body\n", f);
	writeVariables(f, p->globalVariables);
	if (p->scope)
		fputs("CALL &main\n", f);
}
