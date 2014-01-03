void worker_change_threads(char path[],char threadchild[])
{
	char cpath[200],tpath[200],input[300];
	strcpy(cpath,path);
	strcpy(tpath,path);
	strcat(cpath,"/httpd-2.2.23/server/mpm/worker/worker.c");
	strcat(tpath,"/httpd-2.2.23/server/mpm/worker/temp");
	FILE *worker=fopen(cpath,"r");
	FILE *temp=fopen(tpath,"w");
	//printf("%s %s",cpath,tpath);
	while(fgets(input,300,worker)!=NULL)
	{
		if(strstr(input,"#define DEFAULT_THREAD_LIMIT 64")!=NULL)
		{
			fprintf(temp,"%s","#define DEFAULT_THREAD_LIMIT ");
			fprintf(temp,"%s\n",threadchild);
		}
		else fprintf(temp,"%s",input);
	}
	fclose(temp);
        fclose(worker);
        remove(cpath);
        rename(tpath,cpath);
}

void worker_change_startservers(char path[],char startservers[])
{
	char cpath[200],tpath[200],input[300];
	strcpy(cpath,path);
	strcpy(tpath,path);
	strcat(cpath,"/httpd-2.2.23/server/mpm/worker/worker.c");
	strcat(tpath,"/httpd-2.2.23/server/mpm/worker/temp");
	FILE *worker=fopen(cpath,"r");
	FILE *temp=fopen(tpath,"w");
	while(fgets(input,300,worker)!=NULL)
	{
		if(strstr(input,"#define DEFAULT_SERVER_LIMIT 16")!=NULL)
		{
			fprintf(temp,"%s","#define DEFAULT_SERVER_LIMIT ");
			fprintf(temp,"%s\n",startservers);
		}
		else fprintf(temp,"%s",input);
	}
	fclose(temp);
        fclose(worker);
        remove(cpath);
        rename(tpath,cpath);
}

void conf_worker(char path[],char startservers[],char minthreads[],char maxthreads[],char maxclients[],char maxreq[],char threadchild[])
{
	char string[200],path_temp[200],main_path[200],str[200];
        strncpy(path_temp,path,SIZE);
        strncpy(main_path,path,SIZE);
        int i=4;
        if(path[strlen(path)-1]=='/')
        {
                strcat(main_path,"conf/httpd.conf");
                strcat(path_temp,"conf/Temp.conf");
        }
        else
        {
                strcat(main_path,"/conf/httpd.conf");
                strcat(path_temp,"/conf/Temp.conf");
        }
        FILE *httpd_mpm_conf=fopen(main_path,"r");
        FILE *temp=fopen(path_temp,"w");
        while(fgets(string,SIZE,httpd_mpm_conf)!=NULL)
        {
                if(strstr(string,"#Include conf/extra/httpd-mpm.conf")!=NULL)
                {
                        strncpy(string,&string[1],strlen(string));
                }
                fprintf(temp,"%s",string);
        }
        fclose(httpd_mpm_conf);
        fclose(temp);
        remove(main_path);
        rename(path_temp,main_path);
        strcpy(main_path,path);
        strcpy(path_temp,path);	
	if(path[strlen(path)-1]=='/')
        {
                strcat(main_path,"conf/extra/httpd-mpm.conf");
                strcat(path_temp,"conf/extra/Temp.conf");
        }
        else
        {
                strcat(main_path,"/conf/extra/httpd-mpm.conf");
                strcat(path_temp,"/conf/extra/Temp.conf");
        }
        FILE *httpd_conf=fopen(main_path,"r");
        FILE *Temp=fopen(path_temp,"w");
        while(fgets(string,SIZE,httpd_conf)!=NULL)
        {
                if(strstr(string,"<IfModule mpm_worker_module>")!=NULL)
                {
                        fprintf(Temp,"%s",string);
                      	fgets(string,200,httpd_conf);
                        fprintf(temp,"%s","StartServers          ");
			fprintf(temp,"%s\n",startservers);
                      	fgets(string,200,httpd_conf);
                        fprintf(temp,"%s","MinSpareThreads       ");
			fprintf(temp,"%s\n",minthreads);
                      	fgets(string,200,httpd_conf);
                        fprintf(temp,"%s","MaxSpareThreads      ");
			fprintf(temp,"%s\n",maxthreads);
                      	fgets(string,200,httpd_conf);
                        strcpy(str,"MaxClients          ");
                        strcat(str,maxclients);
                        fprintf(temp,"%s\n",str);
                      	fgets(string,200,httpd_conf);
                        fprintf(temp,"%s","ThreadsPerChild   ");
			fprintf(temp,"%s\n",threadchild);
                      	fgets(string,200,httpd_conf);
                        fprintf(temp,"%s","MaxRequestsPerChild   ");
			fprintf(temp,"%s\n",maxreq);
                }
                else fprintf(Temp,"%s",string);
        }
        fclose(httpd_conf);
        fclose(Temp);
        remove(main_path);
        rename(path_temp,main_path);
}
