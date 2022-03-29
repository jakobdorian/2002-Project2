ALL =	duplicates

C11	=	cc -std=c11 -Wall -Werror -pedantic

duplicates:	duplicates.c duplicates.h datastructs.c	datastructs.h readdirectory.c strSHA2.c
	$(C11) -o duplicates duplicates.c readdirectory.c strSHA2.c	datastructs.c

clean:
	rm -f $(ALL)

