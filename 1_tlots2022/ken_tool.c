/*** File ken_tool.c
 *** implementazione di uno strumento automatico per la scrittura della
 *** parte iniziale del programma "ken_init.c", contenente l'inizializzazione
 *** della stringa costante "s". Programma sviluppato a supporto delle
 *** esercitazioni di laboratorio del corso di Architettura dei Calcolatori,
 *** corso di laurea in Informatica, Universita` degli studi di Genova,
 *** anno accademico 2021-2022.
 ***
 *** Copyright (C) Giovanni Chiola 2010-2022.
 *** All rights reserved.
 ***/

#include "ken_header.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
	int i;
	char c;
        INITIAL_PRINTF
	for(i=0; (c = getchar()) != EOF ; i++) {
		switch(c){
		case'\n':printf("\t\'\\n\',");break;
		case'\t':printf("\t\'\\t\',");break;
		case'\\':

/*** TO BE DONE START ***/


/*** TO BE DONE END ***/

		}
                putchar(((i+1)%10)?' ':'\n');
            }
	exit(0);
}
