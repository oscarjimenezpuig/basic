/*
============================================================
  Fichero: ula.c
  Creado: 13-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 07:23:54
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "ula.h"

typedef char Str[INPSIZ];

static double na,nb,nr;

static u1 pop_num_val(u1 number) {
	//extraccion de una seria de valores del tipo numero del stack
	Value va,vb;
	va=vb=NULL;
	u1 ret=0;
	if(number) {
		va=stk_pop();
		if(va && val_type(va)==CNUM) {
			val_num_get(&na,va);
			val_del(&va);
			if(number>1) {
				vb=stk_pop();
				if(vb && val_type(vb)==CNUM) {
					val_num_get(&nb,vb);
					val_del(&vb);
					ret=1;
				}
			} else ret=1;
		};
	} else ret=1;
	val_del(&va);
	val_del(&vb);
	return ret;
}

static u1 push_num_val() {
	Value vr=val_num_new(nr);
	if(vr) return stk_psh(vr);
	else return 0;
}

u1 ula_add() {
	if(pop_num_val(2)) {
		nr=na+nb;
		return push_num_val();
	}
	return 0;
}

u1 ula_prd() {
	if(pop_num_val(2)) {
		nr=na*nb;
		return push_num_val();
	}
	return 0;
}

u1 ula_ops() {
	if(pop_num_val(1)) {
		nr=-na;
		return push_num_val();
	}
	return 0;
}

u1 ula_inv() {
	if(pop_num_val(1) && na!=0) {
		nr=1/na;
		return push_num_val();
	}
	return 0;
}

static u1 chrgrt(char* a,char* b) {
	char* pa=a;
	char* pb=b;
	while(*pa!=EOL) {
		if(*pa<*pb) return 1;
		else if(*pa>*pb) return 0;
		else {
			pa++;
			pb++;
		}
	}
	if(*pb==EOL) return 0;
	else return 1;
}

u1 ula_grt() {
	int ret=0;
	if(pop_num_val(2)) {
		nr=(na>nb)?1:0;
		ret=1;
	} else {
		Value va=stk_pop(va);
		Value vb=stk_pop(vb);
		if(va && val_type(va)==CSTR && vb && val_type(vb)==CSTR) {
			nr=chrgrt(va+2,vb+2);
			ret=1;
		}
		val_del(&va);
		val_del(&vb);
	}
	if(ret) {
		Value vr=val_num_new(nr);
		ret=stk_psh(vr);
	}
	return ret;
}

u1 ula_equ() {
	int ret=0;
	if(pop_num_val(2)) {
		nr=(na==nb)?1:0;
		ret=1;
	} else {
		Value va=stk_pop(va);
		Value vb=stk_pop(vb);
		if(va && val_type(va)==CSTR && vb && val_type(vb)==CSTR) {
			nr=(strcmp(va+2,vb+2)==0)?1:0;
			ret=1;
		}
		val_del(&va);
		val_del(&vb);
	}
	if(ret) {
		Value vr=val_num_new(nr);
		ret=stk_psh(vr);
	}
	return ret;
}

u1 ula_not() {
	int ret=0;
	if(pop_num_val(1)) {
		nr=(na!=0)?0:1;
		Value vr=val_num_new(nr);
		ret=stk_psh(vr);
	}
	return ret;
}

u1 ula_and() {
	int ret=0;
	if(pop_num_val(2)) {
		nr=0;
		if(na!=0 && nb!=0) nr=1;
		Value vr=val_num_new(nr);
		ret=stk_psh(vr);
	}
	return ret;
}

u1 ula_or() {
	int ret=0;
	if(pop_num_val(2)) {
		nr=0;
		if(na!=0 || nb!=0) nr=1;
		Value vr=val_num_new(nr);
		ret=stk_psh(vr);
	}
	return ret;
}




