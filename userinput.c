int receiveUserInput(char* data){
     printf("myshell>");
     fgets(data, MAXLENGTH, stdin); 
	 if(*data=='\n'){
		 return 0;
	 }
     if(strlen(data)!=0){
         return 1;
     }
     else
          return 0;
}
int inputHasCollon(char *input,char **args){
	int size=strlen(input);
	char delim[] = ";";

	for(int i=0;i<size;i++)
	{
		if(input[i]==';')
		{
			return 1;
		}
	}
	return 0;
}
int inputHasPipe(char *input,char **args){
	int size=strlen(input);
	char delim[] = "|";

	for(int i=0;i<size;i++)
	{
		if(input[i]=='|')
		{
			return 1;
		}
	}
	return 0;

}
int inputHasRedirection(char *input,char **args){
	int size=strlen(input);
      int count=0;
	for(int i=0;i<size;i++)
	{
		if(input[i]=='<')
		{
			count++;
		}
		if(input[i]=='>')
		{
			count++;
		}
	}
	return count;

}
void removeSpace(char *inputString,char *args[])
{
	char *temp=inputString;
	int i=0;
	int flag=0;
	while(*temp!='\0' && *temp!='\n')
	{ 
		
		while(*temp==' ')
			temp++;
		inputString=temp;
		while(*temp!=' ' && *temp!='\n' && *temp!='\0')
			temp++;
		if(*temp =='\0' || *temp=='\n')
			flag=1;
		*temp='\0';
	
		if(temp!=inputString)	
			args[i]=inputString;
		if(flag)
			break;
		temp++;
		i++;
	}
	args[++i]=NULL;
}
