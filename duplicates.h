//  CITS2002 Project 2 2021
//  Name(s):             Jakob Kuriata
//  Student number(s):   23278189

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

#include "datastructs.h"

//  declare global functions
extern void list_directory(char *dirname, HASHTABLE *hashtable);
extern void list_alldirectory(char *dirname, HASHTABLE* hashtable);
extern void result();
extern void result_all();
extern char *strSHA2(char *filename);
extern void find_filename(HASHTABLE* h, char* filename);
extern void find_hash(HASHTABLE* h, char* filename);
extern void hasdulps();
extern void list_duplicates(HASHTABLE* h);
extern void usage();

//  data structure to store file variables
typedef struct {
    char* file_name[MAXPATHLEN];
    char* sha2_value[MAXPATHLEN];
    char* file_dirname[MAXPATHLEN];
    int file_bytesize[MAXPATHLEN];
} FILES;

