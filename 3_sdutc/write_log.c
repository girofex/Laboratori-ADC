/*
 * write_log.c: implementazione dell'esercizio "Stardate UTC: Captain's Log".
 *
 * versione 1.6 del 12/04/2022
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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

/*** The following 2 constants may be changed for debugging purposes ***/
#define FNAM "captains_log"
#define SS 128

void fail_errno(const char * msg) {
    perror(msg);
    exit(1);
}

void fail(const char * msg) {
    fprintf(stderr,"ERROR: %s\n",msg);
    exit(1);
}


int main(int argc, char** argv){
    char string[SS], *msg;
    struct tm btm;
    time_t now_t = time(NULL); /* get current time */
    struct flock fls;
    int fc, fd, tm_sz, rc, wc;

/*** TO BE DONE START ***/
    /* open() log file in R/W mode, create it if it doesn't exist already,
       and check the returned value */
    
    fd = open(FNAM, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    
    if(fd == -1)
    
/*** TO BE DONE END ***/

        fail_errno("Could not open log file in R/W mode");
    
    /*** Prepare string to append ***/
    memset((void*)string,0,sizeof(string));

/*** TO BE DONE START ***/
    /* call gmtime_r() and strftime() to print current date in *
     * standard RFC3339 format, followed by ", " into "string" */
    
    strftime(string, sizeof(string), "%Y-%m-%d %XZ, ", gmtime_r(&now_t, &btm));
    	
/*** TO BE DONE END ***/

    if ( argc < 2 )
        msg = "???";
    else
        msg = argv[1];

/*** TO BE OPTIONALLY MODIFIED START ***/

    strncat(string,msg,sizeof(string)-tm_sz-2);
    strcat(string,"\n");

/*** TO BE OPTIONALLY MODIFIED END ***/


    /*** Acquire a POSIX Advisory Write lock on the entire file ***/

/*** TO BE DONE START ***/
    /* initialize "fls" struct */
    
    fls.l_type = F_WRLCK;
    fls.l_whence = SEEK_SET;
    fls.l_start = 0;
    fls.l_len = 0;
    fls.l_pid = fcntl(fd, F_GETLK);

/*** TO BE DONE END ***/

    while ( (fc = fcntl(fd,F_SETLKW,&fls)) < 0 && errno == EINTR ); /*** wait ***/
    if ( fc < 0 )
        fail_errno("Could not acquire write lock on log file");


/*** TO BE OPTIONALLY MODIFIED START ***/
    /* include log registration time, avoiding possible "string" overflow */

/*** TO BE OPTIONALLY MODIFIED END ***/

    /*** append string to the end of the log file ***/

/*** TO BE DONE START ***/
    /* call lseek() to move pointer to the end of the file */
    
    lseek(fd, 0, SEEK_END);

/*** TO BE DONE END ***/

    for ( rc = strlen(string), msg = string ; rc > 0 ; rc -= wc )
        if ( (wc = write(fd,(const void*)string,(size_t)rc)) < 0 ) {

/*** TO BE DONE START ***/
            /* check errno comparing with EINTR */
            
            if(errno == EINTR)
            	fail_errno("Interrupted function call");

/*** TO BE DONE END ***/

        } else
            msg += wc;
        
    if ( argc >= 3 ) { /*** hold lock until reading a new line ***/
        printf("holding lock until you hit <ENTER>\n"); fflush(stdout);
        getchar();
      }
    close(fd); /*** this also releases the Advisory Write lock on the log file ***/
    exit(0);
}
