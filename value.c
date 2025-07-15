/*
============================================================
  Fichero: value.c
  Creado: 12-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 14:30:38
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "value.h"

static Value valoc(u2 dimension) {
	return malloc(dimension);
}

static void zero_out(char* snum) {
	if(*snum!=0) {
		char* point=NULL;
		char* psnum=snum;
		while(*psnum!=0) {
			if(*psnum=='.' && !point) point=psnum; 
			psnum++;
		}
		if(point) {
			psnum--;
			while(psnum!=point) {
				if(*psnum=='0') *psnum=0;
				else break;
				psnum--;
			}
			*psnum=EOL;
		}
	}
}

Value val_num_new(double val) {
	char sval[256]={CVAL,CNUM};
	char* psval=sval+2;
	sprintf(psval,"%lf",val);
	zero_out(psval);
	Value v=valoc(strlen(sval)+1);
	if(v) {
		strcpy(v,sval);
	}
	return v;
}

Value val_str_new(char* str) {
	Value v=valoc(strlen(str)+3);
	if(v) {
		char* psval=v+2;
		strcpy(psval,str);
		*v=CVAL;
		*(v+1)=CSTR;
	}
	return v;
}

void val_del(Value* v) {
	if(v && *v) {
		free(*v);
		*v=NULL;
	}
}

Value val_cpy(Value v) {
	Value cv=valoc(strlen(v)+1);
	if(cv) strcpy(cv,v);
	return cv;
}

u1 val_type(Value val) {
	if(val && *val==CVAL) {
		return *(val+1);
	}
	return 0;
}

u1 val_num_get(double* nval,Value val) {
	if(val_type(val)==CNUM) {
		sscanf(val+2,"%lf",nval);
		return 1;
	}
	return 0;
}

char* val_str_get(Value val) {
	if(val && *val==CVAL) return (val+2);
	return NULL;
}

Value val_cast(Value val,u1 t) {
	if(val && *val==CVAL) {
		Value cval=valoc(strlen(val)+1);
		if(cval) {
			strcpy(cval,val);
			*(cval+1)=t;
			return cval;
		}
	}
	return NULL;
}

void val_prt(Value v) {
	if(v && *v==CVAL) {
		printf(v+2); 
	}
}
