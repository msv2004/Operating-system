#include<stdio.h>
int main()
{
	int i,n,sq=0,count=0,qt,bt[10],wt[10],tat[10],rem_bt[10],temp;
	float a_wt=0,a_tat=0;
	printf("enter the no of process=");
	scanf("%d",&n);
	printf("enter the burst time for process\n");
	for(i=0;i<n;i++)
	{
		printf("p%d=",i+1);
		scanf("%d",&bt[i]);
		rem_bt[i]=bt[i];
	}
	printf("enter the quantum time=");
	scanf("%d",&qt);
	while(1)
	{
		for(i=0,count=0;i<n;i++)
		{
			temp=qt;
			if(rem_bt[i]==0)
			{
				count++;
				continue;
			
			}
			else if(rem_bt[i]>qt)
			{
				rem_bt[i]=rem_bt[i]-qt;	
			}
			else
			{
				if(rem_bt[i]>=0)
				temp=rem_bt[i];
				rem_bt[i]=0;
			}
			sq=sq+temp;
			tat[i]=sq;
			
		}
		if(n==count)
		{
			break;
		}
	}
	printf("\nprocess    burst_time  waiting_time  turnaround_time \n ");
	for(i=0;i<n;i++)
	{
		wt[i]=tat[i]-bt[i];
		a_wt+=wt[i];
		a_tat+=tat[i];
		printf("p[%d]\t%d\t\t%d\t%d\n",i+1,bt[i],wt[i],tat[i]);
	}
	a_wt/=n;
	a_tat/=n;
	printf("\nAVERAGE WAITING TIME = %f ",a_wt);
	printf("\nAVERAGE TURN AROUND TIME =%f ",a_tat);
}
