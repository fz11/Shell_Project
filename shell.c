//Shell project for EE3233
//Fall 2020
//Programmed by Fabricio Zuniga

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_CHAR 512

static void signalHandler(int quit) // for 'ctrl-c'
{
	printf("Shell is closing...\n");
	exit(EXIT_SUCCESS);
	
}

void printpath()
{
	char cwd[1024]; //for directory
	getcwd(cwd, sizeof(cwd)); // print current directory 
	printf("Dir: %s\n", cwd);
}


void execute_ls_l(char *tkn, char* ls2) //for ls_l
{
	pid_t ch;
	ch = fork();
			
	char* args[] = {"ls", "-l", NULL};
			
	if(ch == 0) //child process
	{			
		if(execvp(ls2, args) < 0) 
		{
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}
					
	}
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

void execute_ls(char *tkn, char* ls2 ) //for ls
{
	pid_t ch;
	
	char* args[] = {"ls", NULL};
	ch = fork();
	
	if(ch == 0) //child process
	{
		if(execvp(ls2, args) < 0)
		{		
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}
				
	}
	
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	
	else
	{
		wait(NULL);
	}
}

void execute_cat(char *tkn, char* ls2 ) //for cat
{
	pid_t ch;
	
	char* args[] = {"cat"," ", NULL};
	ch = fork();
			
	if(ch == 0) //child process
	{
		if(execvp(ls2, args) < 0)	
		{		
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}		
	}
	
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	
	else
	{
		wait(NULL);
	}
}

void execute_grep(char *tkn, char* ls2 ) //for grep
{
	pid_t ch;
	
	char* args[] = {"grep"," ", NULL};
	ch = fork();
			
	if(ch == 0) //child process
	{
		if(execvp(ls2, args) < 0)	
		{
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}		
	}
	
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	
	else
	{
		wait(NULL);
	}
}

void execute_touch(char *tkn, char* ls2 ) //for touch
{
	pid_t ch;
	
	char* args[] = {"touch"," ", NULL};
	ch = fork();
			
	if(ch == 0) //child process
	{
		if(execvp(ls2, args) < 0)	
		{		
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}		
	}
	
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	
	else
	{
		wait(NULL);
	}
}



void execute_wc(char *tkn, char* ls2 ) //for wc
{
	pid_t ch;
	int wordcount;
	wordcount = strlen(tkn);
	
	char* args[] = {"wc"," ", NULL};
	ch = fork();
			
	if(ch == 0) //child process
	{
		if(execvp(ls2, args) < 0)	
		{		
			fprintf(stderr, "execution failed\n");
			exit(EXIT_FAILURE);
		}		
	}
	
	else if(ch < 0) //parent process
	{
		fprintf(stderr,"fork failed\n");
		exit(EXIT_FAILURE);
	}
	
	else
	{
		wait(NULL);
	}
}

void processcmd(char* tkn) // takes token and determines what command it is
{
		char ns[] = "\n";
		char space[2] = " ";
		
		char ls[] = "ls\n"; //list directory
		char* ls_n = "ls";
		
		char lsdashl[] = "ls -l\n"; //list contents of directory
		char lsdashl_n[] = "ls -l";
		char lsdashl_ns[] = "ls-l";
		
		char wc[] = "wc\n"; //word count
		char wc_n[] = "wc";
		
		char touch[] = "touch\n"; // create/modify file
		char touch_n[] = "touch";
		
		char quit[] = "quit\n"; 
		char quit_n[] = "quit";
		
		char grep[] = "grep\n"; // find string in file
		char grep_n[] = "grep";
		
		char cat[] = "cat\n"; //view file content
		char cat_n[] = "cat";
		
		char ctrld[] = "‘Ctrl-D’"; //for ctrl-d
		
		
		printf("Current token: %s\n",tkn);
		
		if(strcmp(tkn, ls) == 0 || strcmp(tkn, ls_n) == 0) // ls
		{
			execute_ls(tkn, ls_n); 
		}	
		
		if(strcmp(tkn, lsdashl) == 0 || strcmp(tkn, lsdashl_n) == 0 ||  strcmp(tkn, lsdashl_ns) == 0) // ls -l
		{
			execute_ls_l(tkn, ls_n);					
		}
		
		if(strncmp(tkn, cat, 5) == 0 || strncmp(tkn, cat_n, 3) == 0) //cat
		{
			execute_cat(tkn, cat_n);
		}
		
		if(strncmp(tkn, grep, 6) == 0 || strncmp(tkn, grep_n, 4) == 0) //grep
		{
			execute_grep(tkn, grep_n);
		}
		
		if(strncmp(tkn, touch, 7) == 0 || strncmp(tkn, touch_n, 5) == 0) //touch
		{
			execute_touch(tkn, touch_n);
		}

		if(strncmp(tkn, wc, 4) == 0 || strncmp(tkn, wc_n, 2) == 0) // wc
		{
			execute_wc(tkn, wc_n);
		}
		
		
		if(strcmp(tkn, quit) == 0 || strcmp(tkn, quit_n) == 0) //quit is initiated
		{
				printf("Shell will close\n");
				exit(1);
		}
			
		if(strcmp(tkn, ns) == 0 || strcmp(tkn, space) == 0 || tkn == NULL)  //empty command
			{
				printf("No command input\n");
				printf("please input command\n");
				exit(1);
			} 
			
		if(strcmp(tkn, ctrld) == 0)  //should exit when ctrl-d is recieved
		{
			printf("Shell is closing\n");
			exit(1);
		}			

		
/*		if(strcmp(tkn,ls) !=0 || strcmp(tkn, lsdashl) != 0 || strcmp(tkn, lsdashl_n) != 0 || strcmp(tkn, lsdashl_ns) != 0 || strcmp(tkn, touch) != 0 || strcmp(tkn, touch_n) != 0 || strcmp(tkn, quit) != 0 || strcmp(tkn, quit_n) != 0 || strcmp(tkn, grep) != 0 || strcmp(tkn, grep_n) != 0 || strcmp(tkn, cat) || strcmp(tkn, cat_n) != 0 || strcmp(tkn, wc) != 0 || strcmp(tkn, wc_n) != 0)
		{
			printf("One or more commands are incorrect. Please input valid commands:\n");
			printf("ls\n");
			printf("ls -l\n");
			printf("touch {file}\n");
			printf("quit\n");
			printf("grep {string} {file}\n");
			printf("cat\n {file}");
			printf("wc {file}\n");
			
		} 		*/
		
}

char* removespaces(char *str) //removes spaces within each token
{
	static char strt1[99];
	int count = 0;
	int k, j;
	
	while(str[count] == ' ')
	{
		count++;
	}
	
	for(j = count, k = 0; str[j] != '\0'; j++, k++)
	{
		strt1[k] = str[j];
	}
	
	strt1[k] = '\0';
	
	return strt1;
}

char* buffer(char* inbuf, size_t sz) //buffer for input
{
	char* bf1;
	bf1 = inbuf;
	bf1 = (char*)malloc(sz*sizeof(char));
	if( bf1 == NULL)
	{
		fprintf(stderr, "memory alloc. failed\n");
		exit(EXIT_FAILURE);
	}
	return bf1;
}

void tokenator(char *input) //for file inputs only, sets up tokens
{  
	char *tkn;
	char semi[4] = ";\n";
	char ctrld[] = "‘Ctrl-D’";
	size_t characters = 0;
	size_t size_in = 64;

	characters = sizeof(input);	
	if(characters >= MAX_CHAR) //if max char limit has reached
	{
		fprintf(stderr, "Maximum character limit of 512 has surpassed\n");
		exit(EXIT_FAILURE);
	} 
		
	tkn = strtok(input, semi); //seperate into token by semicolon
	while(tkn != NULL)
	{
		tkn = removespaces(tkn); //removes spaces within tokens
		if(strcmp(tkn, ctrld) == 0)  //should exit when ctrl-d is recieved
		{
			printf("Shell is closing\n");
			exit(1);
		}
		
		processcmd(tkn); //execute command token	
		tkn = strtok(NULL, semi);//next token
	}
} 

void programshell (int argc, char *argv[]) //main program for shell
{

	if(argc == 1) //interactive mode
	{
	    char *instream;
	    char *tkn;
	    char semi[4] = ";\n";
	    
	    size_t size_in = 256;
	    size_t characters;
	    
	    
	
		printf("Entering Interactive Mode:\n");
		printf("Please input command(s)\n");
		while(1)
		{
			printpath();
			printf("\n>");
			instream = buffer(instream, size_in); //using buffer for input to store data 
			characters = getline(&instream, &size_in, stdin); //your input
			if(characters >= MAX_CHAR) //if max char limit has reached
			{
				fprintf(stderr, "Maximum character limit of 512 has surpassed\n");
				exit(EXIT_FAILURE);
			}
	
			tkn = strtok(instream, semi); //seperate into token by semicolon
			
			while(tkn != NULL)
			{
				tkn = removespaces(tkn); //removes spaces within tokens
				processcmd(tkn); //execute command token	
				tkn = strtok(NULL, semi);//next token
			}
		}
	}
	
	else if(argc == 2) //Batch
	{
		FILE *fileptr;
		char filestr[1500];
		size_t size = 0;
		
		printf("Batch Mode\n");
		
		fileptr = fopen(argv[1], "r"); //read file
		
		if(fileptr != NULL)
		{
			printf("file opened. begin parsing and executing\n");
			
			if(fgets(filestr, sizeof(filestr), fileptr) == NULL) //for empty file
			{
				fprintf(stderr,"This file is empty.\n");
			}
			while(fgets(filestr, sizeof(filestr), fileptr) != NULL)
			{	
				if(strlen(filestr) >= MAX_CHAR)
				{	
					printf("Max characters reached. Limit of 512 characters only.\n");					
				}
				else
				{
					printf("\n%s", filestr);
					if(strcmp(filestr, "") == 0 || strcmp(filestr, "\n") == 0 || filestr == NULL)
					{
						printf("Input has no command(s)\n");
					}
					tokenator(filestr);
				}
				
			}
			
		}
		else
		{
			perror("File could not be read.\n");
			exit(EXIT_FAILURE);
		} 	
		
			fclose(fileptr); //close file when finished
			printf("closing file\n");
			exit(1);//exit program
			
	}
	else
	{
		fprintf(stderr,"Incorrect number of arguments.\n"); //more than 2 arguments
		exit(EXIT_FAILURE);
	}

}
		
int main(int argc, char **argv[])
{
		signal(SIGINT, signalHandler); //for ctrl-c
		programshell(argc, argv);	//shell program
}
