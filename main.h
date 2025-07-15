/*
============================================================
  Fichero: main.h
  Creado: 12-07-2025
  Ultima Modificacion: dimarts, 15 de juliol de 2025, 13:35:00
  oSCAR jIMENEZ pUIG                                       
============================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//constantes

//dimensiones
#define TOKSIZ 32 //maxima longitud de un token
#define PRGSIZ 9999 //numero maximo de lineas de un programa
#define VARSIZ 1000 //maximo numero de variables
#define TABLEN 4 //espacios que tiene un tabulador
#define INPSIZ 256 //maximo numero de caracteres que se puede introducir en el input

//indicativos
#define CINS '$' //signo de instruccion
#define CVAL '&' //signo de valor
#define CVAR '#' //signo de la variable (solo cuando esta almacenada en la memoria)

#define CNUM 'n' //signo del numero en un valor
#define CSTR 's' //signo de string en un valor

//instrucciones
#define END 0 //final de ejecucion
#define REM 1 //añadir comentarios
#define SET 2 //definir variable
#define GET 3 //conseguir valor variable
#define PRT 4 //imprimir valor
#define NLN 5 //salto de linea
#define TAB 6 //tabulacio
#define INP 7 //entrada de valor
#define JMP 8 //salta a una linea
#define SUB 9 //va a la linea donde empieza la subrutina
#define RET 10 //retorno de la subrutina
#define IF 11 //condicion
#define NUM 100 //tipo numerico
#define STR 101 //tipo string
#define ADD 200 //suma
#define PRD 201 //producto
#define OPS 202 //opuesto
#define INV 203 //inversos
#define GRT 204 //mayor
#define EQU 205 //igual
#define NOT 206 //not
#define AND 207 //and
#define OR 208 //or

//secuencias escape
#define EOL '\0'

//tipos

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef char* Value;
typedef char* Variable;

struct Token {
	char* str;
	struct Token* prv;
};

struct Line {
	u2 num;
	struct Token* tok;
	struct Line* nxt;
};

typedef struct {
	struct Line* fst;
	struct Line* lst;
} Program;

