/*
============================================================
  Fichero: memory.h
  Creado: 12-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 13:40:51
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "value.h"

//el nombre de la variable es un numero entero entre 0 y 999

u1 var_set();
//se extrae el primer valor del stack es el valor que se introducira y despues la variable

u1 var_get();
//se obtiene del stack el valor de la variable y se introduce en la direccion

void mem_del();
//libera el espacio de la memoria

void mem_prt();
//se imprime toda la memoria activa actual

u1 stk_psh(Value value);
//se introduce un valor en el stack

Value stk_pop();
//se obtiene el valor del stack (si existe)

void stk_del();
//libera el espacio del stack



