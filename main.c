/*
============================================================
  Fichero: main.c
  Creado: 12-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 14:32:02
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "execute.h"

#define nln puts("");

void finish() {
	mem_del();
	stk_del();
}

#define ln(N) l=prg_lin_new(p,N)
#define li(S) prg_lin_ins(l,S)

void programa(Program* p) {
	struct Line* l=NULL;
	ln(10);
	li("$2");
	li("&n3");
	li("&n-23.45");
	ln(20);
	//li("$2");
	//li("&n3");
	//li("&n1234");
	ln(30);
	li("$0");
}

void ejecucion(Program p) {
	puts("Execution");
	u1 noerror=prg_exe(p);
	if(noerror) puts("Ok");
	else puts("Error");
}

int main() {
	Program p=prg_new();
	programa(&p);//dbg
	puts("Program");
	prg_prt(p);
	ejecucion(p);
	mem_prt();//dbg
	prg_del(&p);
	finish();
	return 0;
}
