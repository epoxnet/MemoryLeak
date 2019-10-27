// Shamim Sean Dehghani 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define SUCCESS       0
#define FAILURE       -1
#define BUFFER_SIZE   256

int allocate(char **buffer, size_t size)
{
	errno = 0;
	*buffer = (char*)malloc(size);

	if (*buffer == NULL || errno == ENOMEM)
	{
		printf("malloc returned [%s] errno = %d\n",
			(*buffer == NULL) ? "null" : *buffer, errno);
		return FAILURE;
	}
	return SUCCESS;
	
	//free(*buffer);

	
	
}

void deallocate(char **buffer)
{
	/*
	 * Part One: Add code here to correctly release memory
	 * allocated by malloc() in the allocate() 
	 * function.
	 */
	//realloc(*buffer, 0);
	free(*buffer);
	/*
	 *1-every block of memory that we malloc() must subsequently be free()d.
	 *2-only the memory that we malloc should be free()d.
	 *3-do not free() a block of memory more than once.
	 */
	
}

int read (char *msg, char **buffer, size_t size)
{
	printf ("%s", msg);

	errno = 0;
	if (fgets(*buffer, size - 1, stdin) != NULL)
	{
		char *pos;
		/* cleanup the \n at the end of name_buffer from fgets() */
		if ((pos = strchr(*buffer, '\n')) != NULL) *pos = '\0';
		return SUCCESS;
	}

	printf("fgets returned [%s] errno = %d\n",
		(*buffer == NULL) ? "null" : *buffer, errno);

	return FAILURE;
}

int main (int argc, char **argv)
{
	/*
	 * Part Two: add a call to deallocate().  There
	 * is one place in main() where this call should
	 * be made.
	 *
	 * Part Three: run the program trough valgrind
	 * to verify the memory leak as been addressed.
	 */

	char *buffer;

	if (allocate(&buffer, BUFFER_SIZE) == FAILURE)
	{
		return -1;
		
	}
	

	if (read("Enter some text : ", &buffer, BUFFER_SIZE) == SUCCESS)
	{
		printf ("you entered     : %s\n", buffer);

	}

	//free(&buffer);
	deallocate(&buffer);
	
}




/* 3rd Part: Valgrind 

user@user-VirtualBox:~/Desktop/SecureCoding$ gcc -g memleak.c
user@user-VirtualBox:~/Desktop/SecureCoding$ valgrind ./memleak
==3925== Memcheck, a memory error detector
==3925== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==3925== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==3925== Command: ./memleak
==3925== 
Enter some text : hello
you entered     : hello
==3925== 
==3925== HEAP SUMMARY:
==3925==     in use at exit: 0 bytes in 0 blocks
==3925==   total heap usage: 3 allocs, 3 frees, 2,304 bytes allocated
==3925== 
==3925== All heap blocks were freed -- no leaks are possible
==3925== 
==3925== For counts of detected and suppressed errors, rerun with: -v
==3925== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/


