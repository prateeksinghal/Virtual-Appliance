#define SIZE 200
void install_prefork(char path[],char maxclient[])
{
	char string[SIZE],path_temp[SIZE],main_path[SIZE],str[SIZE];
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
		if(strstr(string,"<IfModule mpm_prefork_module>")!=NULL)
		{
			fprintf(Temp,"%s",string);
			while(fgets(string,SIZE,httpd_conf),i--);
			fprintf(temp,"%s","StartServers          16\n");
			fprintf(temp,"%s","MinSpareServers       5\n");
			fprintf(temp,"%s","MaxSpareServers      16\n");
			strcpy(str,"MaxClients          ");
			strcat(str,maxclient);
			fprintf(temp,"%s\n",str);
			fprintf(temp,"%s","MaxRequestsPerChild   0\n");
		}
		else fprintf(Temp,"%s",string);
	}
	fclose(httpd_conf);
        fclose(Temp);
        remove(main_path);
        rename(path_temp,main_path);
}
