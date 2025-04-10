#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// TODO
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	for (int i = 0; i < N; i++) {
		if (strcmp(cmd, allowed[i])==0) {
			return 1;
		}
	}
	printf("NOT ALLOWED!\n");
	return 0;
}

int main() {

    // TODO
    // Add variables as needed

	// posix spawn setup

	pid_t pid;
	int status;
	posix_spawnattr_t attr;
	posix_spawnattr_init(&attr);

	// other setup

    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';
	
	//tokenise line into params, set params[0] as the command
	char* token = strtok(line," ");
	char* params[64]= {};
	int count = 0;
	while (token!=NULL) {
		params[count] = token;
		token = strtok(NULL, " ");
		count++;
	}
	char* cmd = params[0];
	params[count] = NULL;

	// TODO
	// Add code to spawn processes for the first 9 commands -- doing this after exit,help,cd
	if (isAllowed(cmd) == 0) {
		//not allowed, skip rest of statements/commands
	}
	// And add code to execute cd, exit, help commands
	//exit
	else if (strcmp(cmd,"exit")==0) {
		//exit program
		return 0;
	}
	//help
	else if (strcmp(cmd,"help")==0) {
		//print the help stuff
		printf("The allowed commands are:\n");
		printf("1: cp\n");
		printf("2: touch\n");
		printf("3: mkdir\n");
		printf("4: ls\n");
		printf("5: pwd\n");
		printf("6: cat\n");
		printf("7: grep\n");
		printf("8: chmod\n");
		printf("9: diff\n");
		printf("10: cd\n");
		printf("11: exit\n");
		printf("12: help\n");
	}
	//cd
	else if (strcmp(cmd,"cd") == 0) {
		// run cd using chdir
		if (params[2] != NULL) {
			printf("cd: too many arguments\n");
		}
		else if (params[1] != NULL) {
			chdir(params[1]);
		}
		else {
			printf("cd: no path given \n");
		}
	}
	else {
		if (posix_spawnp(&pid, cmd, NULL, &attr, params, environ) != 0) {
			printf("spawn failed\n");
			exit(EXIT_FAILURE);
		}
		if (waitpid(pid,&status,0) == -1) {
			printf("waitpidfailed\n");
			exit(EXIT_FAILURE);
		}


	}
	// Use the example provided in myspawn.c


    }
	posix_spawnattr_destroy(&attr);
    return 0;
}
