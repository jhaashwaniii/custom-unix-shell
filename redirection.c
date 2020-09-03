int executeSingleRedirection(char *input1,char *input2,char** commandArgs){
	int fd;
 pid_t pid1=fork();
    if(pid1==0){
   int fd= open(input2,O_CREAT | O_WRONLY | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP );
	   dup2(fd,STDOUT_FILENO);
		execvp(commandArgs[0],commandArgs);
 }
 else{
	 waitpid(pid1,NULL,0);
 }
return 1;
}
int executeDoubleRedirection(char *input1,char *input2,char *input3,char** commandArgs){
    pid_t pid1=fork();
     int status;
	  
    if(pid1==0){
	    int fd1=open(input2,O_RDONLY );
		int fd2= open(input3,O_CREAT | O_WRONLY | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP );
	    dup2(fd1,STDIN_FILENO);
	    dup2(fd2,STDOUT_FILENO);
		execvp(commandArgs[0],commandArgs);
 }
 else{
	 waitpid(pid1,&status,0);
	  return 1;
 }
}
int handleSingleRedirection(char *input,char** commandArgs){
	char delim[] = ">";
	char *ptr = strtok(input, delim);
	int count =0;
	char *seprateCommand[2];
	while(ptr != NULL)
	{   if(count==2){
		break;
     	}
		seprateCommand[count++] = ptr;
		
		ptr = strtok(NULL, delim);
		
	}
	removeSpace(seprateCommand[0],commandArgs);
	int result=executeSingleRedirection(seprateCommand[0],seprateCommand[1],commandArgs);
	return 1;

}
int handleDoubleRedirection(char *input,char** commandArgs){
	char delim[] = "><";
	char *ptr = strtok(input, delim);
	int count =0;
	char *seprateCommand[3];
	while(ptr != NULL)
	{   if(count==3){
		break;
     	}
		seprateCommand[count++] = ptr;
		ptr = strtok(NULL, delim);
	}
	removeSpace(seprateCommand[0],commandArgs);
	int result=executeDoubleRedirection(seprateCommand[0],seprateCommand[1],seprateCommand[2],commandArgs);
	return 1;

}