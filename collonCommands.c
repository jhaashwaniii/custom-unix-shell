
int execBuiltInCommand(char** args);
int handleUserDefinedCommands(char *data,char **commandArgs);
int executeCollonCommands(char *input1,char *input2,char** command1Args,char** command2Args){
 pid_t pid1=fork();
 if(pid1==0){
    if(handleUserDefinedCommands(input1,command1Args)){
	    //  return 1;
		exit(0);
      }
      else{
	       if(execBuiltInCommand(command2Args)){
			   exit(0);
		   }
	  else{ printf("illegal command or argument\n");
        exit(0);}
 }
 }
 else{
 pid_t pid2=fork();
 if(pid2==0){
     if(handleUserDefinedCommands(input2,command2Args)){
		exit(0);
 }
 else{
	       if(execBuiltInCommand(command2Args)){
			   exit(0);
		   }
	  else{ printf("illegal command or argument\n");
        exit(0);}
 }
 }
    waitpid (pid1,NULL,0);
	waitpid(pid2,NULL,0);
return 0;
}
}
int handleCollonCommands(char *input,char** command1Args,char** command2Args)
{
	 char input1[100];
	int size=strlen(input);
	char delim[] = ";";
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
	removeSpace(seprateCommand[0],command1Args);
	removeSpace(seprateCommand[1],command2Args);
	int a=executeCollonCommands(seprateCommand[0],seprateCommand[1],command1Args,command2Args);
	 
	return 1;

}