/*
============================================================
  Fichero: value.h
  Creado: 12-07-2025
  Ultima Modificacion: dilluns, 14 de juliol de 2025, 07:22:37
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "main.h"

//estructura IDVALUE + IDTIPOVALUE + EXPRESION DEL VALUE

Value val_num_new(double val);
//crea un valor numerico

Value val_str_new(char* str);
//crea un valor cadena

Value val_cpy(Value value);
//crea un nuevo valor copiando el anterior

void val_del(Value* val);
//libera el espacio del valor

u1 val_type(Value val);
//dice el tipo del valor

u1 val_num_get(double* nval,Value val);
//consigue la expresion numerica de un valor

char* val_str_get(Value val);
//da la cadena que conforma el valor (independientemente del tipo de valor)

Value val_cast(Value val,u1 type);
//hace una copia del valor pero le cambia el tipo

void val_prt(Value val);
//imprime el valor;
