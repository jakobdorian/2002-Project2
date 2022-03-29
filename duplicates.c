//  CITS2002 Project 2 2021
//  Name(s):             Jakob Kuriata
//  Student number(s):   23278189

#include "duplicates.h"

//  reports errors with command line options
void usage()
{
    printf("invalid option! or directory is empty!\n");
    printf("usage:\n");
    printf("-a ~ shows and prints results for all files in the directory\n");
    printf("-A ~ produces no output at all, terminating with EXIT_SUCCESS\n");
    printf("-f filename ~ finds and lists all relative paths of the filename entered\n");
    printf("-h hash ~ finds and lists all relative paths of the hash entered\n");
    printf("-l ~ prints the relative paths of files that are duplicates\n");
    printf("-q ~ duplicates executes quietly with either EXIT_SUCCESS if there are no duplicates and EXIT_FAILURE if there are duplicates\n");
    printf("example ~ ./duplicates -a directory\n");
    printf("exiting...\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    struct stat stat_buffer;
    HASHTABLE *hashtable = hashtable_new();
    int opt;
    int dircheck = 1;

    if(argc <= 1){
        usage();
    }

    //  checks if the "-a" argument has been invoked
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-a") == 0){
            dircheck = 0;
            break;
        }
    }
    //  opens and searches all of the files in the chosen directories
    if(dircheck == 0){
        for(int i = 1; i < argc; i++){
        if(stat(argv[i], &stat_buffer) != 0){
            continue; 
        }
            if(S_ISDIR(stat_buffer.st_mode)){
                list_alldirectory(argv[i], hashtable); 
            } 
        }
    //  opens and searches only the regular files in the chosen directories     
    } else if(dircheck == 1){
        for(int i = 0; i < argc; i++){
        if(stat(argv[i], &stat_buffer) != 0){
            continue;
        }
            if(S_ISDIR(stat_buffer.st_mode)){
                list_directory(argv[i], hashtable);
            }
        } 
    }
    //  gets flags from the command line
    while((opt = getopt(argc, argv, "aAf:h:lq")) != -1){
        switch(opt){
            case 'a':
                result_all();
                break;
            case 'A':
                exit(EXIT_SUCCESS);
                break;
            case 'f':
                find_filename(hashtable, optarg);
                break;
            case 'h':
                find_hash(hashtable, optarg);
                break;
            case 'l':
                list_duplicates(hashtable);
                printf("\n");
                break;
            case 'q':
                hasdulps();
                break;
            case -1:
                break;
            default:
                usage();
                break;
        }
    }
    if(argc == 2 && dircheck ==1){
        result();
    }
}
