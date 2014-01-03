void prefork_change_maxclients(char path[],char maxclients[])
{
	char cpath[200],tpath[200],input[300];
	strcpy(cpath,path);
	strcpy(tpath,path);
	strcat(cpath,"/httpd-2.2.23/server/mpm/prefork/prefork.c");
	strcat(tpath,"/httpd-2.2.23/server/mpm/prefork/temp");
	FILE *prefork=fopen(cpath,"r");
	FILE *temp=fopen(tpath,"w");
	while(fgets(input,300,prefork)!=NULL)
	{
		if(strstr(input,"#define DEFAULT_SERVER_LIMIT 256")!=NULL)
		{
			fprintf(temp,"%s","#define DEFAULT_SERVER_LIMIT ");
			fprintf(temp,"%s\n",maxclients);
		}
		else fprintf(temp,"%s",input);
	}
	fclose(temp);
        fclose(prefork);
        remove(cpath);
        rename(tpath,cpath);
}

void conf_prefork(char path[],char startservers[],char minservers[],char maxservers[],char maxclients[],char maxreq[])
{
	char cpath[200],tpath[200],str[300],string[200];
	strncpy(tpath,path,200);
        strncpy(cpath,path,200);
	if(path[strlen(path)-1]=='/')
        {
                strcat(cpath,"conf/httpd.conf");
                strcat(tpath,"conf/temp");
        }
        else
        {
                strcat(cpath,"/conf/httpd.conf");
                strcat(tpath,"/conf/temp");
        }
	FILE *httpd_mpm_conf=fopen(cpath,"r");
        FILE *temp=fopen(tpath,"w");
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
        remove(cpath);
        rename(tpath,cpath);
	strcpy(cpath,path);
        strcpy(tpath,path);
        if(path[strlen(path)-1]=='/')
        {
                strcat(cpath,"conf/extra/httpd-mpm.conf");
                strcat(tpath,"conf/extra/Temp.conf");
        }
        else
        {
                strcat(cpath,"/conf/extra/httpd-mpm.conf");
                strcat(tpath,"/conf/extra/Temp.conf");
        }
        FILE *prefork=fopen(cpath,"r");
        FILE *Temp=fopen(tpath,"w");
        while(fgets(string,SIZE,prefork)!=NULL)
        {
                if(strstr(string,"<IfModule mpm_prefork_module>")!=NULL)
                {
                        fprintf(Temp,"%s",string);
                        fgets(string,SIZE,prefork);
                        fprintf(temp,"%s","StartServers          ");
			fprintf(temp,"%s\n",startservers);
                        fgets(string,SIZE,prefork);
                        fprintf(temp,"%s","MinSpareServers       ");
			fprintf(temp,"%s\n",minservers);
                        fgets(string,SIZE,prefork);
                        fprintf(temp,"%s","MaxSpareServers      ");
			fprintf(temp,"%s\n",maxservers);
                        fgets(string,SIZE,prefork);
                        strcpy(str,"MaxClients          ");
                        strcat(str,maxclients);
                        fprintf(temp,"%s\n",str);
                        fgets(string,SIZE,prefork);
                        fprintf(temp,"%s","MaxRequestsPerChild   ");
			fprintf(temp,"%s\n",maxreq);
		}
		else fprintf(Temp,"%s",string);
        }
        fclose(prefork);
        fclose(Temp);
        remove(cpath);
        rename(tpath,cpath);
}
