#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
struct processes{

	char process_name[20];
	int  process_id;
	int  arival_time;
	int  burst_time;
	int  process_class;
	int  ta_t;
	int  w_t;
	int  c_t;
};

int global_time;

int main(){
	char buffer [100];
	int n;
	write(1,"Number of processes to be created               : ",50);
	scanf("%d",&n);
	struct processes processes[n];
	struct processes queue1[n];
	struct processes queue2[n];
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
		write(1,"Enter process type (sys/user-0/1)       : ",42);
		read(0,processes[count].process_class,2);
		processes[count].process_id=count;

		write(1,"Want to enter more incoming processes ? ",40);
		scanf("%s",&c);
		if(c == 'y'){
			count+=1;
		}
		else{
			break;
		}

	
	}while(1); //end of do-while loop!

	printf("\n********PROCESS SCHEDULING  IN PROCESS******** ");
	printf("\n********SYSTEM  PROCESS ARE IN QUEUE 1******** ");
	printf("\n********USER    PROCESS ARE IN QUEUE 2******** ");
	int q1_count=0;
	int q2_count=0;
	for(int i=0;i<n;i++){
		if(processes[i].process_class == 0){
				queue1[i]=processes[i]
				write(1,"/nProcess with process id %d is added to queue1! ",49);
				q1_count++;
			}//end of if
		else if(processes[i].process_class == 1){
				queue2[i]=processes[i];
				write(1,"/nProcess with process id %d is added to queue2! ",49);
				q2_count++;
			}//end of else
	}//end of assignment loop 
	
	
	write(1,"/nEnter starting time  : ",25);
	scanf("%d",&global_time);
	struct processes temp;
	while(1){
		//Queue1 in Process
			for(int i=0;i<=q1_count;i++){
				while(queue1[i].burst_time != 0)
				{
					for(int j = i+1 ; j <= q1_count ; j++)
					{
						if(queue1[j].burst_time < queue1[i].burst_time )
						{
							temp=queue1[j];
							queue1[j]=queue1[i];
							queue1[i]=temp;
						}
					}
					global_time ++;
					queue1[i].burst_time --;
					if(queue[i].burst_time == 0){
						queue1[i].c_t = global_time;
					}
				}


			}//end of queue1 execution 
			write(1,"\nQUEUE1 EXECUTED !! ",21);
	

	}//process execution ended !!


}//end of main!
