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
	int count=0;
	
	while(count < n)
	{
		write(1,"\nEnter name of the process               : ",44);
		read(0,processes[count].process_name,15);
		write(1,"Enter arival time of the process        : ",42);
		scanf("%d",&processes[count].arival_time);

    	write(1,"Enter burst  time of the process        : ",42);
		scanf("%d",&processes[count].burst_time);
	
		write(1,"Enter process type (sys/user-0/1)       : ",42);
		scanf("%d",&processes[count].process_class);
	
		processes[count].process_id=count;
		count++;
	
	} //end of do-while loop!

	printf("\n********PROCESS SCHEDULING  IN PROCESS******** ");
	printf("\n********SYSTEM  PROCESSES ARE IN QUEUE 1******** ");
	printf("\n********USER    PROCESSES ARE IN QUEUE 2******** ");
	int q1_count=0;
	int q2_count=0;
	int i;
	for(i=0;i<n;i++){
		if(processes[i].process_class == 0){
				queue1[q1_count]=processes[i];
				q1_count++;
			}//end of if
		else if(processes[i].process_class == 1){
				queue2[q2_count]=processes[i];
				q2_count++;
			}//end of else
	}//end of assignment loop 
	
	
	write(1,"\nEnter starting time  :  ",26);
	scanf("%d",&global_time);
	fflush(stdin);
	
	int time_quant=2;
	int bz=0;
	int rt[n];
	int flag ;
	int k=0;
	int j;
	int z;
	struct processes temp;
	int comp= 0, t = 0, minm=queue1[0].burst_time;
	int shortest = 0, finish_time;
	int flag1 = 0;
	while(1){
		
		for (i = 0; i < q1_count;i++){// Copy the burst time into rt[]
			rt[i] = queue1[i].burst_time;
		}
       				
       	while(comp != q1_count){
	       		for (j = 0; j < q1_count; j++) {
	            	if ((queue1[j].arival_time <= global_time) && (rt[j] <= minm) && rt[j] > 0) {
	                	minm = rt[j];
	                	shortest = j;
	                	flag1=1;
					}
	       		}
	       		
	       			
	 		if(flag1==0) {
	            global_time++;
	            continue;
	        }
			
			// Reduce remaining time by one
	        rt[shortest]--;
			// Update minimum
	        minm = rt[shortest];
	        if(minm == 0)
	            minm = INT_MAX;
			 
			if (rt[shortest] == 0) {
	 			// Increment complete
	            comp++;
	 
	            // Find finish time of current
	            // process
	            queue1[shortest].c_t = global_time;
	            finish_time = global_time + 1;
	 			queue1[shortest].c_t = global_time+1;
			}
				
	           
	        global_time ++ ;		
		}
		
		printf("\n\nQueue1 executed !!");
		int a;
		for(a=0; a< q1_count ; a++)
		{
			printf("\nCompletion time of proc. %s = %d ",queue1[a].process_name,queue1[a].c_t);
		}
			//Queue2 in process 
		        for(j=0;bz != q2_count;){
					if(queue2[j].burst_time <= time_quant && queue2[j].burst_time >0 ){
						global_time+=queue2[j].burst_time; 
      					queue2[j].burst_time=0; 
     					flag=1; 
					}
					else if(queue2[j].burst_time>0) 
    				{ 
     					queue2[j].burst_time-=time_quant; 
      					global_time+=time_quant; 
   					}
					   
					if(queue2[j].burst_time==0 && flag==1) 
				    { 
				    	bz++; 
					  	queue2[j].c_t = global_time+1; 
				      	flag=0; 
				    }  
					if(j==q2_count -1) 
      					j=0; 
					else if(queue2[j+1].arival_time<=global_time) 
      					j++; 
					else 
      					j=0; 

			}//end of queue2 execution 
	        printf("\n\nQueue2 executed !!");
			for(a=0; a< q2_count ; a++)
				{
					printf("\nCompletion time of proc. %s = %d ",queue2[a].process_name,queue2[a].c_t);
				}
 
			break;
	}//process execution ended !!
	
	int avg_tat1=0;
	int avg_tat2=0;
	int avg_wt1=0;
	int avg_wt2=0;

	printf("\n\t\t\t********SCHEDULING COMPLETED********");
	printf("\n\t\t\t********RESULTS INTERFACE********");

	for(i=0;i<q1_count;i++){
		queue1[i].ta_t=queue1[i].c_t - queue1[i].arival_time;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].ta_t=queue2[i].c_t - queue2[i].arival_time;
	
	}
	
	for(i=0;i<q2_count;i++){
		queue2[i].w_t=queue2[i].ta_t - queue2[i].burst_time;
	
	}
	
	for(i=0;i<q1_count;i++){
		queue1[i].w_t=queue1[i].ta_t - queue1[i].burst_time;
	
	}
	
	printf("\n\nPROCESS NAME |\t TURN AROUND TIME |\t WAITING TIME \n");
	for(i=0;i<q1_count;i++){
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].process_name,queue1[i].ta_t,queue1[i].w_t);
	}
	printf("\n---------------------------------***-----------------------------------\n");
	for(j=0;j<q2_count;j++){
	printf(" %s             |\t\t%d         |\t\t%d \n ",queue2[j].process_name,queue2[j].ta_t,queue2[j].w_t);
	}
	
	printf("\n\t\t********AVERAGE T.A.T & AVERAGE WAITING TIME********");
	
	for(i=0;i<q1_count;i++){
	
		avg_tat1=avg_tat1+queue1[i].ta_t;
	}
	avg_tat1= (avg_tat1 / q1_count);
	for(i=0;i<q2_count;i++){
	
		avg_tat2=avg_tat2+queue2[i].ta_t;
	}
	avg_tat2= (avg_tat2 / q2_count);
	for(i=0;i<q2_count;i++){
	
		avg_wt2=avg_wt2+queue2[i].w_t;
	}
	avg_wt2= (avg_wt2 / q2_count);
	for(i=0;i<q1_count;i++){
	
		avg_wt1=avg_wt1+queue1[i].w_t;
	}
	avg_wt1= (avg_wt1 / q1_count);
	
	printf("\n\nPROCESS NAME |\t AVERAGE TURN AROUND TIME |\t AVERAGE WAITING TIME \n");
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].process_name,avg_tat1,avg_wt1);
	printf(" %s             |\t\t%d         |\t\t%d \n",queue1[i].process_name,avg_tat2,avg_wt2);
	printf("\n---------------------------------***-----------------------------------\n");
	
	
	
	
}//end of main!
