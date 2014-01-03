void nginx()
{
	char path[1000],cmd[1000],pathi[1000],temp[1000];
	FILE *fp;
	int x,num,t,conn,time,ch,i,div,port,j;
	printf("Enter the path where you want to download nginx : ");
	scanf("%s",path);
	//getchar();
	//system("su -");
	sprintf(cmd,"mkdir %s/nginx",path);
	system(cmd);
	sprintf(cmd,"chmod 777 %s/nginx",path);
	system(cmd);
	sprintf(cmd,"cd %s/nginx && wget nginx.org/download/nginx-1.2.6.tar.gz",path);
	system(cmd);
	sprintf(cmd,"cd %s/nginx && tar -xvf nginx-1.2.6.tar.gz",path);
	system(cmd);
	printf("Enter the path where you want to install nginx : ");
	scanf("%s",pathi);
	sprintf(cmd,"cd %s/nginx/nginx-1.2.6 && ./configure --prefix=%s/nginx_install --without-http_rewrite_module",path,pathi);
	system(cmd);
	sprintf(cmd,"cd %s/nginx/nginx-1.2.6 && make",path);
	system(cmd);
	sprintf(cmd,"cd %s/nginx/nginx-1.2.6 && make install",path);
	system(cmd);
	sprintf(cmd,"cd %s && chmod 777 -R nginx_install",pathi);
	system(cmd);	

	/* Fail2ban */

	printf("\n\n Nginx Installed Successfully !!!!!\n\n");
	printf("Now Start Configuring ........\n\n");
	while(1)
	{
		printf("Press <1> for DEFAULT Configuration\n");
		printf("Press <2> for ADVANCED Configuration\n\n");
		scanf("%d",&ch);
		if(ch==2)
		{
			printf("Enter the number of processor cores in your system : ");
			scanf("%d",&num);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/worker_processes.*/worker_processes  %d;/' nginx.conf",pathi,num);
			system(cmd);
			printf("\n\nEnter on how many cores you want to divide the request load (in factors of %d): ",num);
			scanf("%d",&div);
			char bit[num];
			char tot[1000]="";
			for(i=1;i<=div;i++)
			{
				if(div==1)
				{
					for(j=0;j<num;j++)
						bit[j]='1';
					bit[num]='\0';
				}
				else
				{
					for(j=0;j<num;j++)
						bit[j]='0';
					for(j=i-1;j<num;j+=div)
						bit[j]='1';
					bit[num]='\0';
				}
				strcat(tot," ");
				strcat(tot,bit);
				
			}
			sprintf(cmd,"cd %s/nginx_install/conf &&  sed -i '/worker_processes/ a\\worker_cpu_affinity %s' nginx.conf",pathi,tot);
			system(cmd);
			printf("\n\nEnter the number of worker connections you want : ");
			scanf("%d",&conn);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/worker_connections.*/worker_connections  %d;/' nginx.conf",pathi,conn);
			system(cmd);
			printf("\n\nEnter value for \"keep alive time-out\" : ");
			scanf("%d",&time);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/ keepalive_timeout.*/keepalive_timeout  %d;/' nginx.conf",pathi,time);
			system(cmd);
			printf("\n\nEnter port to be listened by your Server : ");
			scanf("%d",&port);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/     listen.*/     listen  %d;/' nginx.conf",pathi,port);
			system(cmd);
			printf("\n\nNginx Configured !!!\n\n");
			break;
		}
		else if(ch==1)
		{
			printf("Enter the number of processor cores in your system : ");
			scanf("%d",&num);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/worker_processes.*/worker_processes  %d;/' nginx.conf",pathi,num);
			system(cmd);
			printf("\n\nEnter the number concurrent requests expected : ");
			scanf("%d",&x);
			sprintf(cmd,"cd %s/nginx_install/conf && sed -n -e 's/ keepalive_timeout  \\([0-9]*\\).*/\\1/p' nginx.conf > 1",pathi);
			system(cmd);
			strcpy(temp,pathi);
			strcat(temp,"/nginx_install/conf/1");
			fp=fopen(temp,"r");
			fscanf(fp,"%d",&time);
			/*fclose(fp);
			  sprintf(cmd,"cd %s/nginx_install/conf && sudo rm 1",pathi);
			  system(cmd);*/
			conn=(2*x*time)/num;
			if(conn%1024 != 0)
			{
				t=conn/1024;
				conn=(t+1)*1024;
			}
			else if(conn<1024)
				conn=1024;
			sprintf(cmd,"cd %s/nginx_install/conf && sed -i 's/worker_connections.*/worker_connections  %d;/' nginx.conf",pathi,conn);
			system(cmd);
			sprintf(cmd,"cd %s/nginx_install/conf && rm 1",pathi);
			system(cmd);
			printf("\n\nNginx Configured !!!\n\n");
			break;
		}
		else 
			printf("\n\nYou Entered Wrong Choice !!!! Try Again...\n\n");
	}
}
