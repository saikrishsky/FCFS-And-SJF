#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_t a;
void *FCFS(void* s)
{
	float a[20],b[20],wt[20],tat[20],avgt,t[20];
	int n,i,p[20],count=0,tot=0;
printf("Enter no of processes\n");
 scanf("%d",&n);
for(i=0;i<n;i++)
{
p[i]=i+1;
}
for(i=0;i<n;i++)
{printf("Enter arrival time for p[%d]\n",i+1);
scanf("%f",&a[i]);
printf("Enter burst time for p[%d]\n",i+1);
scanf("%f",&b[i]);
}
for(i=0;i<n-1;i++)
{
if(a[i+1]<a[i])
{
float k;
k=a[i];
a[i]=a[i+1];
a[i+1]=k;
float j;
j=b[i];
b[i]=b[i+1];
b[i+1]=j;
int s;
s=p[i];
p[i]=p[i+1];
p[i+1]=s;
}
}
t[0]=a[0]+b[0];
tat[0]=t[0]-a[0];
avgt=tat[0];
for(i=1;i<n;i++)
{
tot=tot+b[i];
t[i]=t[i-1]+b[i];
tat[i]=t[i]-a[i];
avgt=avgt+tat[i];
count++;
}
printf("Process\tarrival time\tburst time\tcompletion time\tturn around time\n");
for(i=0;i<n;i++)
{
printf("p[%d]\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",p[i],a[i],b[i],t[i],tat[i]);
}
printf("The average turn around time in FCFS is:");
printf("%.2f\n",avgt/n);
}
void *SJF(void* imp)
{
	float *ip;
	ip = (float*) imp;
	float inp=*ip;
	float a[20],b[20],wt[20],tat[20],t[20];
	int p[20],n,i,tot=0,count=0;
float avgt=0;
printf("enter no of processes\n");
 scanf("%d",&n);
for(i=0;i<n;i++)
{
p[i]=i+1;
}
for(i=0;i<n;i++)
{printf("Enter arrival time for p[%d]\n",i+1);
scanf("%f",&a[i]);
printf("Enter burst time for p[%d]\n",i+1);
scanf("%f",&b[i]);
}
int y=0;
while(y<n-1)
{for(i=0;i<n-1;i++)
{
if(b[i+1]<b[i])
{float temp=b[i];
b[i]=b[i+1];
b[i+1]=temp;
int p1=p[i];
p[i]=p[i+1];
p[i+1]=p1;
float a1=a[i];
a[i]=a[i+1];
a[i+1]=a1;
}
}
y++;
}
if(a[0]<=inp)
{
t[0]=b[0]+inp-a[0];
wt[0]=t[0]-b[0];
tat[0]=wt[0]+b[0];}
else{
t[0]=b[0];
wt[0]=t[0]-b[0];
tat[0]=wt[0]+b[0];
}
avgt=tat[0];
for(i=1;i<n;i++)
{
if(a[i]<inp)
{
t[i]=t[i-1]+b[i]+inp-a[i];
wt[i]=t[i]-b[i];
}
else{
t[i]=t[i-1]+b[i];
wt[i]=t[i]-b[i];}
tat[i]=wt[i]+b[i];
avgt=avgt+tat[i];
count++;
}
printf("Process\tburst time\tcompletion time\t\twaiting time\tturn around time\n");
for(i=0;i<n;i++)
{
printf("p[%d]\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",p[i],b[i],t[i],wt[i],tat[i]);
}
printf("The average turn around time in SJF is:");
printf("%.2f\n",avgt/n);

}
int main()
{
	int ch;
	printf("Enter 1)FCFS 2)SJF 3)SJF with idle time: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			pthread_create(&a,NULL,&FCFS,NULL);
			pthread_join(a,NULL);
			break;
		case 2:
			{float ip=0;
			pthread_create(&a,NULL,&SJF,(void*) &ip);
			pthread_join(a,NULL);
			break;}
		case 3:
			float inp;
			printf("Enter idle time of system:");scanf("%d",&inp);
			pthread_create(&a,NULL,&SJF,(void*) &inp);
			pthread_join(a,NULL);
			break;
		default:
			printf("Wrong Entry");
	}
}
