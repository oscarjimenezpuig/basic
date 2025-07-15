/*
============================================================
  Fichero: inout.h
  Creado: 13-07-2025
  Ultima Modificacion: diumenge, 13 de juliol de 2025, 20:36:32
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "memory.h"

u1 io_prt();
//imprime el valor del stack (si existe)

u1 io_nln();
//salto de linea

u1 io_tab();
//tabulacion

u1 io_inp(u1 type);
//se guarda en el stack el valor introducido por el teclado (se pide tipo y longitud)


