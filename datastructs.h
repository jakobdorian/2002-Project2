//  CITS2002 Project 2 2021
//  Name(s):             Jakob Kuriata
//  Student number(s):   23278189

//   workshop implementation of list and hashtable

//  OUR SIMPLE LIST DATATYPE - A DATA ITEM, AND A POINTER TO ANOTHER LIST
typedef struct _list {
     char           *string;
     struct _list   *next;
} LIST;
//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN hashtable.c :
//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	HASHTABLE	*hashtable_new(void);
//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *, char *string);
//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *string);
//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }
//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN list.c :
//  'CREATE' A NEW, EMPTY LIST
extern	LIST	*list_new(void);
//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	LIST	*list_add(  LIST *list, char *newstring);
//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
extern	bool	 list_find (LIST *list, char *wanted);
//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	void	 list_print(LIST *list);
