#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include"nginx.h"
#include"prefork_install.h"
#include"worker_install.h"
#include"prefork.h"
#include"worker.h"

int main()
{
	char ch1,ch2,path[1000],num[5],command[100];
	printf("Web Server Configuration\n");
	printf("------------------------\n\n");
	printf("Installation Menu\n");
	printf("1. Typical (Recommended)\n");
	printf("2. Customize\n");
	printf("Chose a installation type [1/2]: ");
	scanf("%c",&ch1);
	if(ch1=='1')
	{
		getchar();
		printf("Please provide information about Web Technology of your Website.\n\n");
		printf("Is your Website using any of the following Technologies ??? \n");
		printf("1. PHP\n");
		printf("2. RUBY\n");
		printf("3. Python\n\n");
		printf("Enter Y if <yes> otherwise N for <no> : ");
		scanf("%c",&ch1);
		getchar();
		printf("\nPlease Provide Information about Data in your Website.\n\n");
		printf("Does your Website contain Videos,HQ-Audios,etc ??? \n");
		printf("Enter Y if <yes> otherwise N for <no> : ");
		scanf("%c",&ch2);
		getchar();
		printf("\nEnter the estimate of Maximum number of Clients expected at a time : ");
		scanf("%s",num);
		if(ch1=='Y' && ch2=='N')
		{
			nginx();
		}
		else if(ch1=='N' && ch2=='Y')
		{
			nginx();
		}
		else if(ch1=='N' && ch2=='N')
		{
			printf("\n\nApache Web Server is suitable for your Website !!!\n\n");
			printf("Enter the path where you want to install Apache : \n");
			scanf("%s",path);
			system("chmod 777 install-apache.sh");
			strcpy(command,"./install-apache.sh ");
			strcat(command,path);
			if(atoi(num)<= 256)
			{
				strcat(command," prefork");
				system(command);
				install_prefork(path,num);		
			}
			else
			{
				strcat(command," worker");
				system(command);
				install_worker(path,num);			
			}
		}
		else if(ch1=='Y' && ch2=='Y')
		{
			getchar();
			nginx();
		}
	}
	else
	{
		printf("Welcome to customize installation ...\n");
		getchar();
		printf("Chose a Web Server you want install [NGINX(N) or APACHE(A)] ...");
		scanf("%c",&ch1);
		if(ch1=='A')
		{
			printf("Provide a complete path where you want to install apache ...");
			scanf("%s",path);
			getchar();
			printf("Chose a module you want to install [Worker(W) or Prefork(P)] ... ");
			scanf("%c",&ch1);
			if(ch1=='P')
			{
				strcpy(command,"./download-apache.sh ");
				strcat(command,path);
				system("chmod 777 download-apache.sh");
				system(command);
				strcat(command," prefork");
				char startservers[8],minservers[8],maxservers[8],maxclients[8],maxreq[8];
				printf("Please enter the configuration details: \n");
				printf("Start Servers: ");
				scanf("%s",startservers);
				printf("Minimum Spare Servers: ");
				scanf("%s",minservers);
				printf("Maximum Spare Servers: ");
				scanf("%s",maxservers);
				printf("Maximum Clients: ");
				scanf("%s",maxclients);
				if(atoi(maxclients)>256)
				{
					prefork_change_maxclients(path,maxclients);
				}
				printf("Maximum Request Per Child:  ");
				scanf("%s",maxreq);
				strcpy(command,"./conf-apache.sh ");
				strcat(command,path);
				strcat(command," prefork");
				system(command);
				conf_prefork(path,startservers,minservers,maxservers,maxclients,maxreq);
			}
			else if(ch1=='W')
			{
				system("chmod 777 download-apache.sh");
				strcpy(command,"./download-apache.sh ");
				strcat(command,path);
				system(command);
				strcat(command,"worker");
				char startservers[8],minthreads[8],maxthreads[8],maxclients[8],maxreq[8],threadchild[8];
				printf("Please enter the configuration details: \n");
				printf("Start Servers (DEFAULT MAXIMUM VALUE 16): ");
				scanf("%s",startservers);
				if(atoi(startservers)>16)
				{
					worker_change_startservers(path,startservers);
				}
				printf("Minimum Spare Threads: ");
				scanf("%s",minthreads);
				printf("Maximum Spare Threads: ");
				scanf("%s",maxthreads);
				printf("Threads Per Child: ");
				scanf("%s",threadchild);
				if(atoi(threadchild)>64)
				{
					worker_change_threads(path,threadchild);
				}
				printf("Maximum Request Per Child:  ");
				scanf("%s",maxreq);
				printf("Maximum Clients (Should be an intger multiple of MaxRequestPerChild): ");
				scanf("%s",maxclients);
				strcpy(command,"./conf-apache.sh ");
				strcat(command,path);
				//strcat(command,"/httpd-2.2.23");
				strcat(command," worker");
				system("chmod 777 conf-apache.sh");
				system(command);
				conf_worker(path,startservers,minthreads,maxthreads,maxclients,maxreq,threadchild);
			}
		} 
		else if(ch1=='N')
		{
			getchar();
			nginx();
		}
	}
	return 0;
}
