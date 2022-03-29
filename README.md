# 2002-Project2
Code for CITS2002 Systems Programming Project 2 at UWA.
The goal of this project was to write a command-line utility program in C that locates and reports duplicate files in a chosen directory.
## Complile the program via make
```
make
```
## How to use (single directory)
```
./duplicates [options] directory
```

## How to use (multiple directories)
```
./duplications [options] directory1 directory2
```
## Command-line options
```
-a ~ shows and prints results for all files in the directory
-A ~ produces no output at all, terminating with EXIT_SUCCESS
-f filename ~ finds and lists all relative paths of the filename entered
-h hash ~ finds and lists all relative paths of the hash entered
l ~ prints the relative paths of files that are duplicates
-q ~ duplicates executes quietly with either EXIT_SUCCESS if there are no duplicates and EXIT_FAILURE if there are duplicates
example ~ ./duplicates -a directory\n
```
