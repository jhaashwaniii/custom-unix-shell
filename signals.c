void handle_sigint(int sig) 
{ 
    printf("the program is interrupted, do you want to exit [Y/N]"); 
	 char ch1, ch2='Y';
    scanf("%c", &ch1);
   if(ch1==ch2)
   {
	     
     exit(0);
   }
    else{
          signal(SIGINT, handle_sigint);
		  }
   
}
void handle_sigterm()
{              printf("Got SIGTERM-Leaving");
           signal(SIGTERM,handle_sigterm);
          exit(1);
          fflush(stdout);
}
int handleExit(){
	exit(0);
	return 0;
}
int handleKill(char** commadArgs){
	 printf("Got SIGTERM-Leaving\n");
		exit(0);

}