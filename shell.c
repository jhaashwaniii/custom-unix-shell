#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h>
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 
#include <fcntl.h>
#define MAXLENGTH 100
#include "userinput.c"
#include "signals.c"
#include "userdefinedcommands.c"
#include "collonCommands.c"
#include "pipes.c"
#include "redirection.c"


int execBuiltInCommand(char** args) 
{  
	pid_t pid = fork(); 
	 if (pid == 0) { 
		
        if (execvp(args[0], args) < 0) { 
            printf("illegal command or argument\n"); 
			exit(0);
        } 
	} else { 
		wait(NULL); 
		return 1; 
	} 
} 
int executeInput(char *data,char** commandArgs,char** pipeArgs )
{
		    removeSpace(data,commandArgs);
     if(handleUserDefinedCommands(data,commandArgs)){
          return 1;
      }
      else{
		int a= execBuiltInCommand(commandArgs);
        return 0;
     }
	return 1;
}
int handleUserDefinedCommands(char *data,char **commandArgs)
{
    int commandNumber=0;
    char *userCommands[10];
    userCommands[0]="checkcpupercentage";
    userCommands[1]="checkresidentmemory";
    userCommands[2]="listFiles";
    userCommands[3]="sortFile";
    userCommands[4]="kill";
    userCommands[5]="executeCommands";
    userCommands[6]="exit";
    for (int i = 0; i <7; i++) { 
		if (strcmp(commandArgs[0],userCommands[i]) == 0) { 
			commandNumber= i + 1; 
			break; 
		} 
	} 
    switch(commandNumber){
        case 1 :
           return checkcpupercentage(commandArgs);
        case 2 :
            return checkresidentmemory(data,commandArgs);
        case 3:
		    return listFiles(commandArgs);
		case 4 :
             return sortFile(commandArgs); 
	    case 5 :
		    return handleKill(commandArgs);
		case 6 :
		     return executeAllFileCommands(commandArgs); 
		case 7 :
		      return handleExit();
        default:
              break;
    }
    return 0;
}
int main(int argc,char *argv[]){
	while(1){
		 char inputString[100];
   char *commandArgs[MAXLENGTH]; 
   char *pipeArgs[100];
		signal(SIGINT, handle_sigint); 
		signal(SIGTERM,handle_sigterm);
      int userGivenInput=receiveUserInput(inputString);
      if(userGivenInput){
		  char *command1Args[MAXLENGTH]; 
		  char *command2Args[MAXLENGTH]; 
		  int collon=inputHasCollon(inputString,commandArgs);
		  if(collon){
			int d=handleCollonCommands(inputString,command1Args,command2Args);
			
		  }
	     else{
			 int pipe=inputHasPipe(inputString,commandArgs);
			 if(pipe){
				 int d=handlePipeCommands(inputString,command1Args,command2Args);
			 }
			 else{
				int d=inputHasRedirection(inputString,commandArgs);
				if(d==1)
				{
					int a=handleSingleRedirection(inputString,commandArgs);
					continue;
				}
				if(d==2)
				{
					int b=handleDoubleRedirection(inputString,commandArgs);
				}
                else{
                int a= executeInput(inputString,commandArgs,pipeArgs);
				continue;
				}
			 }
	  }
	 
      }
      else{
         continue;
      }
   }
    return 0;
}