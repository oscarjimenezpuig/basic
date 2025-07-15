/*
============================================================
  Fichero: inout.c
  Creado: 13-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 04:27:13
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "inout.h"

u1 io_prt() {
	Value v=stk_pop();
	if(v) {
		val_prt(v);
		val_del(&v);
		return 1;
	}
	return 0;
}

u1 io_nln() {
	printf("\n");
	return 1;
}

u1 io_tab() {
	for(u1 k=0;k<TABLEN;k++) printf(" ");
	return 1;
}

u1 io_inp(u1 type) {
	char c=0;
	char str[INPSIZ];
	char* ptr=str;
	while((c=getchar())!='\n' && ptr-str<INPSIZ) {
		*ptr++=c;
	}
	*ptr=0;
	if(type==CNUM) {
		double val;
		sscanf(str,"%lf",&val);
		return stk_psh(val_num_new(val));
	} else if(type==CSTR) return stk_psh(val_str_new(str));
	else return 0;
}

	
	
