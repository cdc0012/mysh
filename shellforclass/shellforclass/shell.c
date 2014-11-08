#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include <unistd.h>


#define MAXLINE 256
#define MYSH_EXIT "exit"
#define MYSH_VER "ver"
#define MYSH_PWD "pwd"
#define QCR_C ".c"
#define QCR_CPP ".cpp"
#define VERSION_NUMBER "0.1"
#define COPYRIGHT_NOTICE "Copyright 2014"


// Function  Declarations
int mysh_getLine(char *line, int max);
void qcr_ansi_c();
void qcr_cpp();

// Main Program
int main()
{

	// Variable declarations for main().
	char *tline;
	char token[MAXLINE];
	char * ptoken;
	char * pstr;
	int  start, count;
	char cwd[1024]; // magic number is not very safe....

	//allocate space for the input line.  This could be static....
	tline = (char*)calloc(MAXLINE, sizeof(char));

	// main loop for the shell run forever....
	while (1){
		// print prompt and get input line
		mysh_getLine(tline, MAXLINE);

		// now parse out the line...
		ptoken = strtok(tline, " ");

		if (ptoken != NULL) {
			// there's a better ways of doing this, using a CASE statement or at least as ELSE-IFs...
			// but be careful with the logic on the QCR if's...

			//Check for EXIT command
			if (strcmp(ptoken, MYSH_EXIT) == 0) exit(0);

			//Check for the CPP Quick-Compile-And-Run feature
			if ((start = strlen(ptoken) - 4) > 0) {
				pstr = &ptoken[start];
				if (strcmp(pstr, QCR_CPP) == 0) qcr_cpp();
			}

			// Check for the ANSI C Quick-Compile-And-Run feature
			if ((start = strlen(ptoken) - 2) > 0) {
				pstr = &ptoken[start];
				if (strcmp(pstr, QCR_C) == 0) qcr_ansi_c();
			}

			// Check for pwd command
			if (strcmp(ptoken, MYSH_PWD) == 0) {
				// must use a unix system call not just a call to "/bin/pwd" !! 
				// ...that would be an EXTERNAL COMMAND!
				if (getcwd(cwd, sizeof(cwd)) != NULL)
					printf("%s\n", cwd);
				else
					printf("mysh: OOPS! Error with getcwd() call.\n");
			}

			// Check for cd command
			if (strcmp(ptoken, "cd") == 0) {
				printf("DO THE cd COMMAND...\n");
			}

			// Check for version 
			if (strcmp(ptoken, MYSH_VER) == 0){

				printf("%s %s\n", VERSION_NUMBER, COPYRIGHT_NOTICE);
			}
			// Check for all the other internal commands ....


			// Else...must be an external command....RUN IT !

		}
	}

	// This probably never gets executed....
	printf("Exiting mysh...\n");
	return 0;
}

// This function prints the shell prompt and gets a line of input.
// The input line is stored at the location specified by user (char *line).
// The MAX size of the input line is also specified by the caller (max) to 
// prevent any buffer overflow problems.
// The input line is forced to be null terminated by this function.
// Return value is the number of input characters on the line (less NULL)
int mysh_getLine(char *line, int max)
{
	int i = 0;
	char ch;
	printf("mysh> ");
	while ((ch = getchar()) != EOF && ch != '\n')
	if (i<(MAXLINE - 1)) line[i++] = ch;
	line[i] = '\0';
	return i;
}

void qcr_ansi_c()
{
	printf("PERFORMING QCR for ANSI C\n");
}


void qcr_cpp()
{
	printf("PERFORMING QCR for CPP\n");
}
