#ifndef ARRL_H
#define ARRL_H

/* arrl.h
 * The array list implementation for character strings in c.
 * 
 * Author: Batuhan BASAK
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* The initial arrl capacity */
#define INITIAL_ARRL_CAPACITY 5


/* The array list implementation for c-strings. */
struct ARRL{
    /* The underlying char pointer to store. */
    char *s;
    /* The size of underlying array. */
    int size;
    /* The capacity of underlying array. */
    int capacity;    
};


typedef struct ARRL arrl_t;

/* Initialize the given arrl l. */
void init_arrl(arrl_t *l);

/* Adds the given new character to the end of arrl */
void add_char(arrl_t *l, char c);

/* Doubles the current capacity of given arrl */
void increase_capacity_arrl(arrl_t *l);


/* Deallocates the allocated memory for given arrl. */
void dealloc_arrl(arrl_t *l);

#endif
