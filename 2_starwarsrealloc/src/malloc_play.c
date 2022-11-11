/*
 * malloc_play.c: bizzarro programma per studiare il comportamento delle system call
 *                malloc(), realloc() e free().
 *
 * versione 1.6 del 21/03/2022
 *
 * Programma sviluppato a supporto del laboratorio di
 * Architettura dei Calcolatori del corso di laurea triennale
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova, anno accademico 2021/2022.
 *
 * Copyright (C) 2013-2022 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include<stdlib.h>
#include<stdio.h>

/*** Just playing with the malloc(), realloc(), free()
 *** system calls in order to guess how memory management
 *** is implemented on this machine. If you get SEGMENTATION
 *** FAULT while addressing unallocated heap memory, just run
 *** the program with different "min" and/or "max" values,
 *** explicitly given on the command line through argv[]
 ***/
int main(int argc, char**argv){
    unsigned char *p, *q, *oldp;
    int sz=1, min=-16, max=60;

#define check_pointer(p) if ( p == NULL ) { \
            printf("could not allocate p\n"); \
            exit(0); \
          }

#define print_array(a,f,t,n) { int i, j=1; \
            for ( i = f ; i <= t ; i++, j = (j+1)%4 ) \
                printf("%s[%3d]=%3hhu%c",n,i,a[i],j?'\t':'\n'); \
            printf("\n"); \
          }

    if ( argc > 1 )
        sscanf(argv[1],"%d",&sz);
    if ( sz <= 0 )
        sz = 1;
    else if ( sz > 300 )
        sz = 300;
    if ( argc > 2 )
        sscanf(argv[2],"%d",&min);
    if ( min > -1 )
        min = -1;
    else if ( min < -50 )
        min = -50;
    if ( argc > 3 )
        sscanf(argv[3],"%d",&max);
    if ( max < sz )
        max = sz;
    else if ( max > (sz+100) )
        max = sz+100;
    printf("... allocating %d unsigned chars to pointer p, min=%d, max=%d\n\n",sz,min,max);
    p = (unsigned char*)malloc(sz);
    check_pointer(p)
    *p = 'p';
    print_array(p,min,max,"p")
    printf("\n... allocating %d more unsigned chars to a different pointer q\n\n",sz);
    q = (unsigned char*)malloc(sz);
    check_pointer(q)
    *q = 'q';
    print_array(q,3*min,max,"q")
    print_array(p,min,max,"p")
    sz += 4;
    printf("\n... reallocating %d unsigned chars to p\n\n",sz);
    oldp = p;
    p = (unsigned char*)realloc((void*)p,sz);
    check_pointer(p)
    sprintf(p,"startp");
    print_array(p,min,max,"p")
    print_array(oldp,min,max,"oldp")
    sz += 35;
    printf("\n... reallocating %d unsigned chars to p\n\n",sz);
    p = (unsigned char*)realloc((void*)p,sz);
    check_pointer(p)
    sprintf(p,"modifiedp");
    print_array(p,min,max,"p")
    print_array(oldp,min,max,"oldp")
    sz -= 35;
    printf("\n... reallocating %d unsigned chars to p (again)\n\n",sz);
    p = (unsigned char*)realloc((void*)p,sz);
    check_pointer(p)
    print_array(p,min,max,"p")
    print_array(oldp,min,max,"oldp")
    printf("\n... freeing p\n\n");
    free((void*)p);
    print_array(p,min,max,"p")
    printf("\n... freeing q\n\n");
    free((void*)q);
    print_array(q,3*min,max,"q")
/*** see also what happens if you uncomment the following instruction and explain why ***/
/*
    free((void*)oldp);
*/
    exit(0);
}
