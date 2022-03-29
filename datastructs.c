//  CITS2002 Project 2 2021
//  Name(s):             Jakob Kuriata
//  Student number(s):   23278189

#include "duplicates.h"
#define	HASHTABLE_SIZE 3

uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}
//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
HASHTABLE *hashtable_new(void)
{
    HASHTABLE   *new = malloc(HASHTABLE_SIZE * sizeof(LIST *));

    CHECK_ALLOC(new);
    return new;
}
//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_add(HASHTABLE *hashtable, char *string)
{
    uint32_t h   = hash_string(string) % HASHTABLE_SIZE;    // choose list

    hashtable[h] = list_add(hashtable[h], string);
}
//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *string)
{
    uint32_t h	= hash_string(string) % HASHTABLE_SIZE;     // choose list

    return list_find(hashtable[h], string);
}
//  'CREATE' A NEW, EMPTY LIST - JUST A NULL POINTER
LIST *list_new(void)
{
    return NULL;
}
//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *wanted)
{
    while(list != NULL) {
	if(strcmp(list->string, wanted) == 0) {
	    return true;
	}
	list	= list->next;
    }
    return false;
}
//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(char *newstring)
{
    LIST *new       = malloc( sizeof(LIST) );
    CHECK_ALLOC(new);
    new->string     =  strdup(newstring);
    CHECK_ALLOC(new->string);
    new->next       =  NULL;
    return new;
}
//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newstring)
{
    if(list_find(list, newstring)) {            // only add each item once
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(newstring);
        new->next   = list;
        return new;
    }
}
//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
	    printf("%s", list->string);
	    if(list->next != NULL) {
	        printf(" -> ");
            }
	    list	= list->next;
        }
	printf("\n");
    }
}

