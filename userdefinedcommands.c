int handleUserDefinedCommands(char *data,char **commandArgs);
int get_nprocs_conf(void);
int checkresidentmemory(char* data,char** commadArgs){
    char* processId=commadArgs[1];
	
	char *arg[7];
	arg[0]="ps";
	arg[1]="--no-headers";
	arg[2]="--pid";
	arg[3]=processId;
	arg[4]="-o";
	arg[5]="rssize";
	arg[6]=NULL;
	int pid=fork();
	
	if(pid<0)
	{
		printf("fork failed");
	}
	else if(pid==0)
	{
		printf("i am child");
		execvp("ps",arg);
	}
	else
	{
		wait(NULL);
	}
    return 1;
}
int sortFile(char** commadArgs)
{
    int pid=fork();
	if(pid<0)
	{
		printf("fork failed");
	}
	else if(pid==0)
	{
		printf("i am child");
		execlp("sort","sort",commadArgs[1],NULL);
	}
	else
	{
		wait(NULL);
	}
	return 1;
}
int listFiles(char** commadArgs)
{
	int fd[2];
	if(pipe(fd)==-1){
		printf("pipe failed");
	}
    int pid=fork();
     if(pid==0)
	{      close(STDOUT_FILENO);
		int fd=open("files.txt",O_CREAT | O_WRONLY | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP);
		execlp("ls","ls",NULL);
	}
	else{
		wait(NULL);
	return 1;
	}
}
int checkcpupercentage(char *argv[]){
	int totalCPUNumber=get_nprocs_conf(); 
	char firstPath[100]="/proc/";
	char *temp=firstPath;
	
	while(*temp!='\0')
		temp++;
	strncpy(temp,argv[1],sizeof(argv[1]));
	
	while(*temp!='\0')
		temp++;
	strncpy(temp,"/stat",6);
	
	FILE* fp;
	
	fp=fopen(firstPath,"r");
	if(fp==NULL)
		printf("error");
	
	int spaces=13;
	int c=fgetc(fp);
	
	while(spaces)
	{
		int c=fgetc(fp);
		//printf(" %c\n",c);
		if(c==' ')
			spaces--;
	}
	float user1=0,system1=0;
	
	while((c=fgetc(fp))!=' ')
		user1=user1*10+(c-'0');
	
	while((c=fgetc(fp))!=' ')
		system1=system1*10+( c-'0');
	
	fp=fopen("/proc/stat","r");
	if(fp==NULL)
		printf("error");

	while((c=fgetc(fp))!=' ');
	float total1=0;
	
	while(c!='\n')
	{
		int cur=0;
		while((c=fgetc(fp))!=' ' && c!='\n')
			cur=cur*10+(c-'0');
		total1+=cur;
	}
	
	while(sleep(1)); ///delay for 1 sec an then calcualting again
	
	fp=fopen(firstPath,"r");
	if(fp==NULL)
		printf("error");
	
	 spaces=13;
	 c=fgetc(fp);
	
	while(spaces)
	{
		int c=fgetc(fp);
		//printf(" %c\n",c);
		if(c==' ')
			spaces--;
	}
	float user2=0,system2=0;
	
	while((c=fgetc(fp))!=' ')
		user2=user2*10+(c-'0');
	
	while((c=fgetc(fp))!=' ')
		system2=system2*10+( c-'0');
	
	fp=fopen("/proc/stat","r");
	if(fp==NULL)
		printf("error");

	while((c=fgetc(fp))!=' ');
	float total2=0;
	
	while(c!='\n')
	{
		int cur=0;
		while((c=fgetc(fp))!=' ' && c!='\n')
			cur=cur*10+(c-'0');
		total2+=cur;
	}
	
	float user=((user2-user1)*100*totalCPUNumber)/(total2-total1);
	float system=((system2-system1)*100*totalCPUNumber)/(total2-total1);
	printf("user mode cpu percentage: %f\n",user);
	printf("system mode cpu percentage: %f\n",system);
	return 1;
	}
int executeAllFileCommands(char** commadArgs){
	FILE *f = fopen(commadArgs[1],"r");
    char ptr[1024];
    char *token;

    while (fgets(ptr, 1024, f) != NULL)
    {
        token = strtok(ptr, ",");    
        while(token)
        { 
			char *commandFileArgs[MAXLENGTH];
			removeSpace(token,commandFileArgs);
			int b=handleUserDefinedCommands(token,commandFileArgs);
            token = strtok(NULL, ",");
        }
    }
    fclose(f);
    return 1;
}
