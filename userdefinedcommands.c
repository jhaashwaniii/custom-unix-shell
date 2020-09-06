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
	
	if(pid==0)
	{
		if(execvp("ps",arg)<0)
		{
			printf("illegal command or argument\n");
			exit(0);
		}
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
	 if(pid==0)
	{
		if(execlp("sort","sort",commadArgs[1],NULL)<0)
		{
			printf("illegal command or argument\n");
			exit(0);
		}
	}
	else
	{
		wait(NULL);
	}
	return 1;
}
int listFiles(char** commadArgs)
{
    int pid=fork();
     if(pid==0)
	{      close(STDOUT_FILENO);
		int fd=open("files.txt",O_CREAT | O_WRONLY | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP);
		if(execlp("ls","ls",NULL)<0){
			printf("illegal command or argument\n");
			exit(0);
		}
	}
	else{
		wait(NULL);
	return 1;
	}
}
int checkcpupercentage(char *argv[]){
	int totalCPUNumber=get_nprocs_conf(); 
	char firstPath[150]="/proc/";
	char *temp=firstPath;
	
	while(*temp!='\0')
		temp++;
	strncpy(temp,argv[1],sizeof(argv[1]));
	
	while(*temp!='\0')
		temp++;
	strncpy(temp,"/stat",6);
	
	FILE* file;
	
	file=fopen(firstPath,"r");
	if(file==NULL)
		printf("illegal command or argument\n");
	int totalSpaces=13;
	int c=fgetc(file);
	
	while(totalSpaces)
	{
		int c=fgetc(file);
		if(c==' ')
			totalSpaces--;
	}
	float firstUser=0,system1=0;
	
	while((c=fgetc(file))!=' ')
		firstUser=firstUser*10+(c-'0');
	
	while((c=fgetc(file))!=' ')
		system1=system1*10+( c-'0');
	
	file=fopen("/proc/stat","r");
	if(file==NULL)
		printf("error");

	while((c=fgetc(file))!=' ');
	float total1=0;
	
	while(c!='\n')
	{
		int cur=0;
		while((c=fgetc(file))!=' ' && c!='\n')
			cur=cur*10+(c-'0');
		total1+=cur;
	}
	while(sleep(1)); 
	file=fopen(firstPath,"r");
	if(file==NULL)
		printf("error");
	
	 totalSpaces=13;
	 c=fgetc(file);
	
	while(totalSpaces)
	{
		int c=fgetc(file);
		if(c==' ')
			totalSpaces--;
	}
	float secondUser=0,system2=0;
	
	while((c=fgetc(file))!=' ')
		secondUser=secondUser*10+(c-'0');
	
	while((c=fgetc(file))!=' ')
		system2=system2*10+( c-'0');
	
	file=fopen("/proc/stat","r");
	if(file==NULL)
	printf("illegal command or argument\n");

	while((c=fgetc(file))!=' ');
	float total2=0;
	
	while(c!='\n')
	{
		int cur=0;
		while((c=fgetc(file))!=' ' && c!='\n')
			cur=cur*10+(c-'0');
		total2+=cur;
	}
	
	float userCPU=((secondUser-firstUser)*100*totalCPUNumber)/(total2-total1);
	float systemCPU=((system2-system1)*100*totalCPUNumber)/(total2-total1);
	printf("user mode cpu percentage: %f%c\n",userCPU,'%');
	printf("system mode cpu percentage: %f%c\n",systemCPU,'%');
	return 1;
	}
int executeAllFileCommands(char** commadArgs){
	FILE *f = fopen(commadArgs[1],"r");
	if(f==NULL){
		  printf("illegal command or argument\n");
			return 1;
	}
    char ptr[10240];
    char *token;

    while (fgets(ptr, 10240, f) != NULL)
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
