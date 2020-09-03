int executePipeCommands(char *input1,char *input2,char** command1Args,char** command2Args){
	int fd[2];
	pipe(fd);
 pid_t pid1=fork();
 if(pid1==0){
	   dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(command1Args[0],command1Args);
   // exit(0);
 }
 else{
  pid_t pid2=fork();
 if(pid2==0){
     dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
		close(fd[1]);
		execvp(command2Args[0],command2Args);
  }
  else{
       close(fd[0]);
     	close(fd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
return 0;
}
}
}

int handlePipeCommands(char *input,char** command1Args,char** command2Args)
{
	 char input1[100];
	int size=strlen(input);
	char delim[] = "|";
	char *ptr = strtok(input, delim);
	int count =0;
	char *seprateCommand[2];
	while(ptr != NULL)
	{   if(count==2){
		break;
     	}
		seprateCommand[count++] = ptr;
		printf("command1-%s",ptr);
		ptr = strtok(NULL, delim);
	}
	removeSpace(seprateCommand[0],command1Args);
	removeSpace(seprateCommand[1],command2Args);
	int a=executePipeCommands(seprateCommand[0],seprateCommand[1],command1Args,command2Args);
	return 1;

}