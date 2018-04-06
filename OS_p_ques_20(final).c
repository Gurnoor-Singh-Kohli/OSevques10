#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
int avail_resources ;
struct process {
	int requiredResources ;
	int pev_allocated;
	int need;


}proc[20];
void inputResource_details(int b,int c);
void analyseResource_details(int e,int f);
void  analyseResource_safetyCheck_details(int d);

void main()
{	int a,i,b;
	write(1,"\nEnter number of processes                  :",46);
	scanf("%d",&a);
	write(1,"\nEnter number of resources                 :",46);
	scanf("%d",&b);
	avail_resources=b;
	write(1,"For each process please define the following :\n",48);
	for(i=0;i<a;i++)
	{
		inputResource_details(i,b);
	}
	analyseResource_details(a,b);

}

void inputResource_details(int b,int c)
{	int x,y;
	printf("Number Required Resource Reuirement of process %d : ",b+1);
	scanf("%d",&x);

	if(x>c)
	{
		write(1,"\nRequired Resource Reuirement cannot be greater than resources!!! \n FATAL ERROR!! - \n Enter again  :\n\n",107);
		scanf("%d",&x);

	}
	printf("Number of Pre allocated resources of process %d : ",b+1);
	scanf("%d",&y);
	if(y>x)
	{
		write(1,"No need to allocate more than requirement -> making allocation = requirement\n\n",76);
	  	y=x;
	}

	proc[b].requiredResources=x;
	proc[b].pev_allocated=y;
	proc[b].need=x-y;
	avail_resources=avail_resources-y;
	printf("\nNmber of total remaining available resources : %d",avail_resources);
	printf("\n***PROCESS %d CONFIGURED***\n\n",b+1);
}

void  analyseResource_safetyCheck_details(int d)
{
	int S_seq[d];
	int f[d];
	int count = 0,i,count2=0;
	for(i=0;i<d;i++){
		f[i]=0;
	}
	while(count<d)
	{
		bool flag = false;
		for (i = 0; i < d; i++)
        {
        	if (f[i] == 0)
        	{

        		if (proc[i].need > avail_resources)
        			break;
        		else
					{
						avail_resources=avail_resources+proc[i].pev_allocated;
						proc[i].pev_allocated=0;
						f[i]=1;
						S_seq[count++] = i;
						flag=true;
					}
			}
			else
			count2++;
		}
		if(count2==d)
		break;
		if (flag == false)
        {
            write(1,"\n\n ---* SYSTEM IS NOT IN SAFE STATE !! *--- \n\n",50);
        }
	} // end of while
  write(1,"\n\n ---* SYSTEM IS IN SAFE STATE !! *--- \n\n",46);
  printf("\nSequence of completion of processes : ");
  for(i=0;i<d;i++)
  {
  	printf("%d -> ",S_seq[i]+1);
  }
}

void analyseResource_details(int e,int f)
{
	int x=0,i;
	for(i=0;i<e;i++)
	{
		x=x+proc[i].requiredResources;
	}
	if(x<e+f)
	{
		 analyseResource_safetyCheck_details(e);
	}
	else
	{
		printf("\n\n ---* SYSTEM IS IN UNSAFE STATE DUE TO FAILURE OF CONSTRAINTS !! *--- \n\n");
	}
}
