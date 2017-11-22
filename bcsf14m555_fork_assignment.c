#include  <stdio.h>
#include  <sys/types.h>
# include <sys/shm.h>
# include <sys/ipc.h>

int t1=0,t2=0,t3=0,t4=0,t=0;

void  main(void)
{
     pid_t  pid1,pid2,wpid;
	int status;
//	int t1=0,t2=0,t3=0,t4=0,t=0;


	int *sum1,*sum2,*sum3;
	int shmid,shmid2,shmid3;
	shmid=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | SHM_R | SHM_W);
	sum1= (int *) shmat(shmid,0,0);

	shmid2=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | SHM_R | SHM_W);
	sum2= (int *) shmat(shmid2,0,0);

	shmid3=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | SHM_R | SHM_W);
	sum3= (int *) shmat(shmid3,0,0);



	pid1 = fork();
	pid2 = fork();
	
	if(pid2 == 0)
	{
		int i;
		for(i=1;i<=25;i++)
		{
			*sum1=*sum1+i;
			
		}
		
	}
	if(pid2 == 0 && pid1 > 0)
	{

		int i;
		for(i=26;i<=50;i++)
		{
			*sum2=*sum2+i;
			
		}

	}
	
	else if(pid1 == 0 && pid2 > 0)
	{
		int i;
		for(i=51;i<=75;i++)
		{
			*sum3=*sum3+i;
			
		}
		
	}
	
	else if(pid1 > 0)
	{ 
		while(wpid = wait(&status)>0);	

		int i;
		for(i=76;i<=100;i++)
		{
			t4=t4+i;
			
		}
		
		t4=t4 + *sum1 + *sum2 + *sum3;

		
		printf("Total Sum is  = %d\n",t4);		

		
	}
	
}
