#define SIZE 200
void install_worker(char path[],char maxclient[])
{
	char string[SIZE],path_temp[SIZE],main_path[SIZE],str[SIZE];
	strncpy(path_temp,path,SIZE);
	strncpy(main_path,path,SIZE);
	int i=5;
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
	FILE *httpd_conf=fopen(main_path,"r");
	FILE *temp=fopen(path_temp,"w");
	while(fgets(string,SIZE,httpd_conf)!=NULL)
	{
		if(strstr(string,"#Include conf/extra/httpd-mpm.conf")!=NULL)
		{
			strncpy(string,&string[1],strlen(string));
		}
		fprintf(temp,"%s",string);
	}
	fclose(httpd_conf);
	fclose(temp);
	remove(main_path);
	rename(path_temp,main_path);
	strncpy(main_path,path,SIZE);
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
	httpd_conf=fopen(main_path,"r");
	temp=fopen(path_temp,"w");
	while(fgets(string,SIZE,httpd_conf)!=NULL)
	{
		if(strstr(string,"<IfModule mpm_worker_module>")!=NULL)
		{
			fprintf(temp,"%s",string);
			while(fgets(string,SIZE,httpd_conf),i--);
			fprintf(temp,"%s\n","StartServers          16");
			fprintf(temp,"%s\n","MinSpareThreads       25");
			fprintf(temp,"%s\n","MaxSpareThreads      75");
			strcpy(str,"MaxClients          ");
			strcat(str,maxclient);
			fprintf(temp,"%s\n",str);
			fprintf(temp,"%s\n","ThreadsPerChild      25");
			fprintf(temp,"%s\n","MaxRequestsPerChild   0");
		}
		else fprintf(temp,"%s",string);
	}
	fclose(httpd_conf);
        fclose(temp);
        remove(main_path);
        rename(path_temp,main_path);	

}
