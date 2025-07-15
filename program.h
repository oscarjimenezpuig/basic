/*
============================================================
  Fichero: program.h
  Creado: 14-07-2025
  Ultima Modificacion: dilluns, 14 de juliol de 2025, 12:45:24
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "ula.h"

Program prg_new();
//se inicia un programa

void prg_del(Program* p);
//liberamos la memoria ocupada por el programa

struct Line* prg_lin_new(Program* p,u2 line_number);
//se crea una nueva linea (el valor de line_number debe ser superior al anterior, si no no se crea)

struct Line* prg_lin_fnd(Program p,u2 line_number);
//se busca la nueva linea

u1 prg_lin_ins(struct Line* l,char* token);
//se inserta un token en una linea

void prg_prt(Program p);
//se imprime el programa por lineas
