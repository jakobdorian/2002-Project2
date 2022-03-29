//  CITS2002 Project 2 2021
//  Name(s):             Jakob Kuriata
//  Student number(s):   23278189

#include "duplicates.h"

int filecount = 0;
int totalbytes = 0;
int uniquecount = 0;
int uniquebytes = 0;
int filecount_all = 0;
int totalbytes_all = 0;
int uniquecount_all = 0;
int uniquebytes_all = 0;
int size = 0;

FILES f;
char* duplicate_dirname[MAXPATHLEN];

//  checks if chosen directory has duplicates
void hasdulps()
{
    if(uniquecount == filecount){
        exit(EXIT_SUCCESS);
    } else{
        exit(EXIT_FAILURE);
    }
}
//  searches directory for inputted hash
void find_hash(HASHTABLE* h, char* filename)
{
    int foundfiles = 0;
    for(int i = 0; i < size; i++){
        if(strcmp(f.sha2_value[i], filename) == 0){
            printf("%s\n", f.file_dirname[i]);
            foundfiles++;
        } 
    }
    if(foundfiles >= 1){
        exit(EXIT_SUCCESS);
    } else{
        exit(EXIT_FAILURE);
    }
}
//  searches directory for inputted filename
void find_filename(HASHTABLE* h, char* filename)
{
    int foundfiles = 0;
    for(int i = 0; i < size; i++){
        if(strcmp(f.file_name[i], filename) == 0){
            printf("%s\n", f.file_dirname[i]);
            foundfiles++;
        }
    }
    if(foundfiles >= 1){
        exit(EXIT_SUCCESS);
    } else{
        exit(EXIT_FAILURE);
    }
}
//  print results for all files
void result_all()
{
    //  checks if the directory is empty or invalid
    if(filecount_all == 0 && totalbytes_all == 0){
        usage();
    }
    printf("total number of files: %i\n", filecount_all);
    printf("total number of bytes: %i\n", totalbytes_all);
    printf("total number of unique files: %i\n", uniquecount_all);
    printf("total number of unique bytes: %i\n", uniquebytes_all);
}
//  prints results for regular files
void result()
{
    //  checks if the directory is empty or invalid
    if(filecount == 0 && totalbytes == 0){
        usage();
    }
    printf("total number of files: %i\n", filecount);
    printf("total number of bytes: %i\n", totalbytes);
    printf("total number of unique files: %i\n", uniquecount);
    printf("total number of unique bytes: %i\n", uniquebytes);
}
//  reads the chosen directory and stores important information about each regular file into a data structure
void list_directory(char *dirname, HASHTABLE* h)
{
    DIR     *dirp;
    struct dirent   *dp;
    struct stat stat_buffer;
    //  checks if the directory can be opened (read-only)
    dirp = opendir(dirname);
    if(dirp == NULL){
        perror( dirname );
        exit(EXIT_FAILURE);
    }
    //  read from the directory, until it reaches the ends
    while((dp = readdir(dirp)) != NULL){
        // checks if file is a regular file
        if(dp -> d_type == DT_REG && dp -> d_name[0] != '.'){
            char newdir[MAXPATHLEN] = {0};
            strcat(newdir, dirname);
            strcat(newdir, "/");
            strcat(newdir, dp -> d_name);
            if(stat(newdir, &stat_buffer) == 0){
                totalbytes = totalbytes + (int)stat_buffer.st_size;

                f.file_name[size] = dp -> d_name;
                f.file_dirname[size] = strdup(newdir);
                f.file_bytesize[size] = (int)stat_buffer.st_size;
                f.sha2_value[size] = strSHA2(newdir);
                //  searches the hashtable if the SHA2 value is stored there already, determines if a file is unique
                if(hashtable_find(h, f.sha2_value[size]) == false){
                    uniquecount++;
                    uniquebytes = uniquebytes + f.file_bytesize[size];
                }
                //  searches the hashtabsle if the SHA2 value is stored there already, then it stores the duplicate directory into a DS
                if(hashtable_find(h, f.sha2_value[size]) == true){
                    duplicate_dirname[size] = f.file_dirname[size];
                }

                //  if SHA2 value is not already in the hashtable, add it
                hashtable_add(h, f.sha2_value[size]);
                hashtable_add(h, f.file_name[size]);
                //hashtable_add(h, f.dfile_bytesize[size]);
                size++;
                filecount++;
            }
        //  checks if file is a directory, if so it updates dirname to the new directory then searches for files recursively
        } else if (dp -> d_type == DT_DIR && dp -> d_name[0] != '.'){
            char newdir[MAXPATHLEN] = {0};
            strcat(newdir, dirname);
            strcat(newdir, "/");
            strcat(newdir, dp -> d_name);
            list_directory(newdir, h);
        }
    }
    //  close directory
    closedir(dirp);
}
//  reads the chosen directory and stores important information about all files into a data structure
void list_alldirectory(char *dirname, HASHTABLE* h)
{
    DIR     *dirp;
    struct dirent   *dp;
    struct stat stat_buffer;
    //  checks if the directory can be opened (read-only)
    dirp = opendir(dirname);
    if(dirp == NULL){
        perror( dirname );
        exit(EXIT_FAILURE);
    }
    //  read from the directory, until it reaches the ends
    while((dp = readdir(dirp)) != NULL){
        //if(strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0){
    
        char newdir[MAXPATHLEN] = {0};
        strcat(newdir, dirname);
        strcat(newdir, "/");
        strcat(newdir, dp -> d_name);
        if(stat(newdir, &stat_buffer) == 0){
            totalbytes_all = totalbytes_all + (int)stat_buffer.st_size;
            
            f.file_name[size] = dp -> d_name;
            f.file_dirname[size] = strdup(newdir);
            f.file_bytesize[size] = (int)stat_buffer.st_size;
            f.sha2_value[size] = strSHA2(newdir);
            //  searches the hashtable if the SHA2 value is stored there already, determines if a file is unique
            if(hashtable_find(h, f.sha2_value[size]) == false){
                uniquecount_all++;
                uniquebytes_all = uniquebytes_all + f.file_bytesize[size];
            }
            //  searches the hashtable if the SHA2 value is stored there already, then it stores the duplicate directory into a DS
            if(hashtable_find(h, f.sha2_value[size]) == true){
                duplicate_dirname[size] = f.file_dirname[size];
            }
            //  if SHA2 value is not already in the hashtable, add it
            hashtable_add(h, f.sha2_value[size]);
            hashtable_add(h, f.file_name[size]);
            size++;
            filecount_all++;
            //}
        }
        //  checks if file is a directory, if so it updates dirname to the new directory then searches for files recursively
        if (dp -> d_type == DT_DIR && strcmp(dp -> d_name, ".") != 0 && strcmp(dp -> d_name, "..") != 0){
            char newdir[MAXPATHLEN] = {0};
            strcat(newdir, dirname);
            strcat(newdir, "/");
            strcat(newdir, dp -> d_name);
            list_alldirectory(newdir, h);
        }
    }
    //  close directory
    closedir(dirp);
}
//  prints all duplicate files
void list_duplicates(HASHTABLE* h)
{
    for(int i = 0; i < size; i++){
        if(duplicate_dirname[i] != NULL){
            printf("%s\t", duplicate_dirname[i]);   
        }
    }
}

