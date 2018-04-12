#include<stdio.h>
#include<pthread.h>
int x[10],y[10];  //global array
struct arg
{
	int p,size;
	int a[20];
	int b[20];
};
int fun1(void *q)
{
	struct arg *ref=q;
	for(int i=0;i<ref->p;i++)
	{
		x[i]=ref->a[i];	
	}
	//checker
	printf("Before sorting first part of array is:");
	for(int i=0;i<ref->p;i++)
	{
		printf("%d ",x[i]);
	}
	for(int i=0;i<ref->p-1;i++)
	{
		for(int j=0;j<ref->p-i-1;j++)
		{
			if(x[j]>x[j+1])
			{
				int temp;
				temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;		
			}		
		}	
	}
	pthread_exit(NULL);
}
int fun2(void *q)
{
	struct arg *ref=q;
	int j=0;	
	for(int i=ref->p;i<ref->size;i++)
	{
		y[j]=ref->a[i];
		j++;	
	}
	printf("\nBefore sorting second part of array is:");
	for(int i=0;i<(ref->size-ref->p);i++)
	{
		printf("%d ",y[i]);
	}
	for(int i=0;i<ref->p-1;i++)
	{
		for(int j=0;j<ref->p-i-1;j++)
		{
			if(y[j]>y[j+1])
			{
				int temp;
				temp=y[j];
				y[j]=y[j+1];
				y[j+1]=temp;		
			}		
		}	
	}
	pthread_exit(NULL);
}
int fun3(void *q)
{
	struct arg *ref=q;
	int i=0,j=0,k=0;
	while(i<ref->p && j<(ref->size-ref->p))
	{
		ref->b[k++]=x[i]<y[j] ? x[i++]:y[j++];
	}
	while(i<ref->p)
	{
		ref->b[k++]=x[i++];
	}
	while(j<(ref->size-ref->p))
	{
		ref->b[k++]=y[j++];
	}
	pthread_exit(NULL);
}
int main()
{
	struct arg o1;
	printf("Enter the size of array:");
	scanf("%d",&o1.size);
	printf(".......Enter the elements of array.......\n");
	for(int i=0;i<o1.size;i++)
	{
		printf("Enter element:%d==>>",i+1);
		scanf("%d",&o1.a[i]);
	}
	o1.p=(int)o1.size/2;	
	pthread_t p1,p2,p3;
	pthread_create(&p1,NULL,fun1,&o1);
	pthread_join(p1,NULL);
	printf("\nAfter sorting first part:");
	for(int i=0;i<o1.p;i++)
	{
		printf("%d ",x[i]);
	}
	pthread_create(&p2,NULL,fun2,&o1);
	pthread_join(p2,NULL);
	printf("\nAfter sorting second part:");
	for(int i=0;i<(o1.size-o1.p);i++)
	{
		printf("%d ",y[i]);
	}
	pthread_create(&p3,NULL,fun3,&o1);
	pthread_join(p3,NULL);
	printf("\nSorted array is:");
	for(int i=0;i<o1.size;i++)
	{
		printf("%d ",o1.b[i]);
	}	
}
