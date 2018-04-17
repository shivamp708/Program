#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int size,max,min;
float avg;
int *fun1(void *a[])
{
	int sum=0;
	for(int i=1;i<size;i++)
	{
		sum+=atoi(a[i]);	
	}
	avg=(float)sum/(size-1);
}
int fun2(void *a[])
{
	max=atoi(a[1]);
	for(int i=2;i<size;i++)
	{
		if(max<atoi(a[i]))
		{
			max=atoi(a[i]);		
		}	
	}	
}
int fun3(void *a[])
{
	min=atoi(a[1]);
	for(int i=2;i<size;i++)
	{
		if(min>atoi(a[i]))
		{
			min=atoi(a[i]);		
		}	
	}
}
int main(int arg,char *args[])
{	
	pthread_t p1,p2,p3;
	size=arg;	
	pthread_create(&p1,NULL,fun1,args);
	pthread_join(p1,NULL);
	pthread_create(&p2,NULL,fun2,args);
	pthread_join(p1,NULL);
	pthread_create(&p3,NULL,fun3,args);
	pthread_join(p1,NULL);
	printf("Average value is :%f",avg);
	printf("\nmaximum value  is :%d",max);
	printf("\nminimum value is :%d\n",min);
}
