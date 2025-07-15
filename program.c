/*
============================================================
  Fichero: program.c
  Creado: 14-07-2025
  Ultima Modificacion: dilluns, 14 de juliol de 2025, 19:05:39
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "program.h"

Program prg_new() {
	return (Program){NULL,NULL};
}

static void token_del(struct Token* t) {
	if(t) {
		token_del(t->prv);
		free(t->str);
		free(t);
	}
}

static void line_del(struct Line* l) {
	if(l) {
		line_del(l->nxt);
		token_del(l->tok);
		free(l);
	}
}

void prg_del(Program* p) {
	line_del(p->fst);
	*p=(Program){NULL,NULL};
}	

struct Line* prg_lin_new(Program* p,u2 nl) {
	struct Line* l=NULL;
	if(nl && nl<=PRGSIZ && prg_lin_fnd(*p,nl)==NULL && (!p->lst || p->lst->num<nl)) {
		l=malloc(sizeof(struct Line));
		if(l) {
			if(!p->fst) p->fst=p->lst=l;
			else {
				p->lst->nxt=l;
				p->lst=l;
			}
			l->tok=NULL;
			l->nxt=NULL;
			l->num=nl;
			
		}
	}
	return l;
}

struct Line* prg_lin_fnd(Program p,u2 nl) {
	struct Line* pl=p.fst;
	while(pl) {
		if(pl->num==nl) return pl;
		pl=pl->nxt;
	}
	return NULL;
}

u1 prg_lin_ins(struct Line* l,char* s) {
	if(l && s) {
		struct Token* t=malloc(sizeof(struct Token));
		if(t) {
			t->str=malloc(strlen(s)+1);
			if(t->str) {
				strcpy(t->str,s);
				t->prv=l->tok;
				l->tok=t;
				return 1;
			} else {
				free(t);
				t=NULL;
			}
		}
	}
	return 0;
}

static void lin_prt(struct Line* l) {
	struct Token* t=l->tok;
	printf("% 4i: ",l->num);
	while(t) {
		printf("%s ",t->str);
		t=t->prv;
	}
	printf("\n");
}	

void prg_prt(Program p) {
	struct Line* l=p.fst;
	while(l) {
		lin_prt(l);
		l=l->nxt;
	}
	printf("\n");
}


