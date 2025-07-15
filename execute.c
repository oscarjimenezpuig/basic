/*
============================================================
  Fichero: execute.c
  Creado: 13-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 13:57:17
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "execute.h"

#define EOL '\0'

struct Node {
	u2 lin;
	struct Node* prv;
};

static u1 type=CNUM;
static u1 finish_program=0; //se para la ejecucion del programa
static u1 finish_line=0; //se para la ejecucion de la linea y pasa a la siguiente
static u2 next_line=0; //guarda la siguiente linea, si es 0, seguira el orden
static u2 actual_line=0; //guarda la linea actual
static struct Node* sub_stk=NULL; //stack del gosub
static u1 noevaluate=0; //indica que esa linea no se interpreta y ha de saltar a la siguiente

static u1 ex_jmp() {
	//funcion del jump
	u1 ret=0;
	Value v=stk_pop();
	if(v && val_type(v)==CNUM) {
		double num;
		val_num_get(&num,v);
		next_line=(u2)num;
		ret=1;
	}
	val_del(&v);
	return ret;
}

static u1 ex_sub() {
	//funcion del gosub
	if(ex_jmp()) {
		struct Node* nn=malloc(sizeof(struct Node));
		if(nn) {
			nn->lin=actual_line;
			nn->prv=sub_stk;
			sub_stk=nn;
			return 1;
		}
	}
	return 0;
}

static u1 ex_ret() {
	//funcion del return
	if(sub_stk) {
		next_line=sub_stk->lin;
		struct Node* td=sub_stk;
		sub_stk=td->prv;
		free(td);
		noevaluate=1;
		return 1;
	}
	return 0;
}

static u1 ex_if() {
	u1 ret=0;
	Value v=stk_pop();
	if(v && val_type(v)==CNUM) {
		double num=0;
		val_num_get(&num,v);
		if(num==0) finish_line=1;
		ret=1;
	}
	val_del(&v);
	return ret;
}

static void sub_stk_del(struct Node* n) {
	if(n) {
		sub_stk_del(n->prv);
		free(n);
	}
}

static u1 tok_exe(struct Token* token) {
	//segun el tipo de palabra se realiza una cosa o otra
	char* word=token->str;
	if(*word==CINS) {
		u1 instruccion=0;
		sscanf(word+1,"%hhi",&instruccion);
		switch(instruccion) {
			case END:
				finish_program=1;
				return 1;
			case REM:
				finish_line=1;
				return 1;
			case SET:
				return var_set();
			case GET:
				return var_get();
			case PRT:
				return io_prt();
			case NLN:
				return io_nln();
			case TAB:
				return io_tab();
			case INP:
				return io_inp(type);
			case JMP:
				return ex_jmp();
			case SUB:
				return ex_sub();
			case RET:
				return ex_ret();
			case IF:
				return ex_if();
			case NUM:
				type=CNUM;
				return 1;
			case STR:
				type=CSTR;
				return 1;
			case ADD:
				return ula_add();
			case PRD:
				return ula_prd();
			case OPS:
				return ula_ops();
			case INV:
				return ula_inv();
			case GRT:
				return ula_grt();
			case EQU:
				return ula_equ();
			case NOT:
				return ula_not();
			case AND:
				return ula_and();
			case OR:
				return ula_or();
			default:
				return 0;
		}
	} else if(*word==CVAL) {
		Value val=NULL;
		if(*(word+1)==CNUM) {
			double num;
			sscanf(word+2,"%lf",&num);
			val=val_num_new(num);
		} else if(*(word+1)==CSTR) {
			val=val_str_new(word+2);
		}
		if(val) return stk_psh(val);
		else return 0;
	} else return 0;
}

static u1 lin_exe(struct Line* line) {
	u1 noerror=1;
	struct Token* ptok=line->tok;
	while(ptok && noerror && !finish_program && !finish_line) {
		noerror &= tok_exe(ptok);
		ptok=ptok->prv;
	}
	return noerror;
}

u1 prg_exe(Program p) {
	u1 noerror=1;
	struct Line* plin=p.fst;
	while(plin && noerror && !finish_program) {
		actual_line=plin->num;
		if(!noevaluate) {
			noerror &= lin_exe(plin);
			finish_line=0;
		} else noevaluate=0;
		if(next_line) {
			plin=prg_lin_fnd(p,next_line);
			noerror=(plin==NULL)?0:1;
			next_line=0;
		} else plin=plin->nxt;
	}
	sub_stk_del(sub_stk);
	sub_stk=NULL;
	return noerror;
}





		






	

