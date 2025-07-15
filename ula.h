/*
============================================================
  Fichero: ula.h
  Creado: 13-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 07:21:10
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include "inout.h"

u1 ula_add();
//suma dos valores del stack (numericos)

u1 ula_prd();
//multiplica dos valores del stack (numericos)

u1 ula_ops();
//hace el opuesto de un valor numerico

u1 ula_inv();
//hace el inverso de un valor (si es diferente de cero)

u1 ula_grt();
//dice si el primer valor es superior al segundo (en caso de cadenas orden alfabetico
//donde el que este antes se considera mayor)

u1 ula_equ();
//dice si son iguales (dos valores o cadenas)

//operaciones booleanas donde true es un numero diferente de 0

u1 ula_not();
//coge un valor numerico y lo transforma en 0 si este es diferente de 0, o en 1 si es 0

u1 ula_and();
//and (binaria)

u1 ula_or();
//or (unaria)
