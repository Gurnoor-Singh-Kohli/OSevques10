# OSevques10
OS_CA@LPU
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
struct processes{

	char process_name[20];
	int arival_time[5];
	int burst_time[5];
	
	
}processes[4];

int main(){
	char buffer [100];
	

	write(1,"Press y to enter a new process!\nPress n to quit! ",50);
	char c;
	int count=0;
	scanf("%s",&c);
	if(c == 'y');
	do{
		write(1,"Enter name of the process               : ",42);
		read(0,processes[count].process_name,15);
		write(1,"Enter arival time of the process        : ",42);
		read(0,processes[count].arival_time,5);
		write(1,"Enter burst  time of the process        : ",42);
		read(0,processes[count].burst_time,5);
		
		write(1,"Want to enter more incoming processes ? ",40);
		scanf("%s",&c);
		if(c == 'y'){
			count+=1;
		}
		else{
			break;
		}

	
	}while(1); //end of do-while loop!




}//end of main!
