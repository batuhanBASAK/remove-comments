#include "arrl.h"

/* Initialize the given arrl l. */
void init_arrl(arrl_t *l)
{
    l->size = 0;
    l->capacity = INITIAL_ARRL_CAPACITY;
    l->s = (char*)calloc(l->capacity, sizeof(char));
}

/* Adds the given new character to the end of arrl */
void add_char(arrl_t *l, char c)
{
    if (l->size == l->capacity)
        increase_capacity_arrl(l);
    l->s[l->size++] = c;
}

/* Doubles the current capacity of given arrl */
void increase_capacity_arrl(arrl_t *l)
{
    int new_capacity = 2*l->capacity;
    char *temp = (char*)calloc(new_capacity, sizeof(char));
    for (int i = 0; i < l->size; i++)
        temp[i] = l->s[i];

    free(l->s);
    l->s = temp;
    l->capacity = new_capacity;
}


/* Deallocates the allocated memory for given arrl. */
void dealloc_arrl(arrl_t *l)
{
    free(l->s);
}
