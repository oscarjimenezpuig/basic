/*
============================================================
  Fichero: memory.c
  Creado: 12-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 14:31:42
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

static char* memory=NULL;
static u4 memcap=0; //capacidad maxima de la memoria
static u4 memlen=0; //memoria ocupada

static u1 var_name_chk(Value var) {
	if(*var==CVAL && *(var+1)==CNUM) {
		double num;
		sscanf(var+2,"%lf",&num);
		double ent=(u2)num;
		if((ent==num) && num>=0 && num<VARSIZ)	return 1;
	}
	return 0;
}

static Variable var_new(Value* variable,Value* value) {
	//crea una nueva variable
	Variable var=NULL;
	if(var_name_chk(*variable) && value) {
		var=malloc(strlen(*value)+strlen(*variable+2)+2);
		if(var) {
			*var=CVAR;
			strcpy(var+1,*variable+2);
			strcat(var,*value);
			val_del(variable);
			val_del(value);
		}
	}
	return var;
}

static u1 var_name_comp(char* name,char* pmem) {
	//compara el nombre buscado con el encontrado en la memoria
	char* pname=name;
	while(*pmem!=CVAL) {
		if(*pname!=*pmem) return 0;
		pname++;
		pmem++;
	}
	return (*pname=='\0');
}

static char* var_find(char* var_name) {
	//busca la variable con nombre
	if(memory) {
		char* pmemory=memory;
		while(*pmemory!='\0') {
			if(*pmemory==CVAR) {
				if(var_name_comp(var_name,pmemory+1)) {
					return pmemory;
				}
			}
			pmemory++;
		}
	}
	return NULL;
}

static void var_erase(char* init) {
	//borra la variable que empieza en init
	char* pmemory=init+1;
	while(*pmemory!='\0' && *pmemory!=CVAR) pmemory++;
	strcpy(init,pmemory);
	memlen=strlen(memory)+1;
}

static u1 mem_increase(u4 dimension) {
	//incrementa la memoria en la dimension dicha
	if(!memory) {
		memory=malloc(dimension);
		if(memory) {
			*memory=0;
			memcap=dimension;
			return 1;
		}
	} else {
		void* ptr=realloc(memory,memcap+dimension);
		if(ptr) {
			memory=ptr;
			memcap+=dimension;
			return 1;
		}
	}
	return 0;
}

u1 var_set() {
	u1 noerror=0;
	Value var=stk_pop();
	if(var) {
		char* pm=var_find(var+2);
		if(pm) var_erase(pm);
		Value val=stk_pop();
		if(var && val) {
			Variable nvar=var_new(&var,&val);
			if(nvar) {
				noerror=1;
				u4 nvarlen=strlen(nvar);
				if(nvarlen+memlen>memcap) {
					u4 incdim=nvarlen+memlen-memcap;
					incdim=(memcap==0)?incdim+1:incdim;
					noerror=mem_increase(incdim);
				}
				if(noerror) {
					strcat(memory,nvar);
					memlen=strlen(memory)+1;
				}
				free(nvar);
			}
		}
	}
	return noerror;
}

static Value val_get(char* pmem) {
	char* inival=NULL;
	while(*pmem!=CVAL) pmem++;
	inival=pmem;
	char* endval=NULL;
	while(*pmem!=CVAR && *pmem!='\0') pmem++;
	endval=pmem;
	u4 size=endval-inival+1;
	Value val=malloc(size);
	if(val) {
		char* pval=val;
		char* pmem=inival;
		while(pmem!=endval) {
			*pval++=*pmem++;
		}
		*pval='\0';
	}
	return val;
}

u1 var_get() {
	u1 ret=0;
	Value var=stk_pop();
	if(var) {
		char* pv=var_find(var+2);
		if(pv) {
			Value val=val_get(pv);
			if(val) {
				ret=stk_psh(val);
			}
		}
		val_del(&var);
	}
	return ret;
}

void mem_del() {
	free(memory);
	memory=NULL;
}

void mem_prt() {
	printf("MEMORY (Used: %i Capacity: %i) {",memlen,memcap);
	if(memory) {
		printf("%s",memory);
	}
	printf("}\n");
}


struct Node {
	Value val;
	struct Node* prv;
};

struct Node* stack=NULL;

u1 stk_psh(Value v) {
	if(v) {
		struct Node* nn=malloc(sizeof(struct Node));
		if(nn) {
			nn->val=v;
			nn->prv=stack;
			stack=nn;
			return 1;
		}
	}
	return 0;
}

Value stk_pop() {
	Value v=NULL;
	if(stack) {
		struct Node* td=stack;
		stack=td->prv;
		v=td->val;
		free(td);
	}
	return v;
}

void stk_del() {
	Value v=NULL;
	while((v=stk_pop())) {
		val_del(&v);
	}
}


			

	




