#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>

int DomainMegaBot(char * , char *, char *, char *);
int hostname_to_ip(char * , char *);
int whois_query(char * , char * , char **);
int Str_Split(char *str, char c, char ***arr);
char* Str_Conn(const char *s1, const char *s2);

int main(int argc , char *argv[]) {
    FILE * fp = fopen("TLD_DATA","r");
    if (fp==NULL) {
        printf("TLD database not found!\n");
        exit(1);
    }
    char *line = NULL; char Ext[10];
    size_t len = 0; ssize_t read;
    char **arr = NULL;
    char DomainExt[10]={'0'}; char NoMatchPattern[20]; char WhoisQueryServer[40];
    printf("\n\nThanks you for using DOMAINMEGABOT powered by HAR-KUUN (https://qing.su) and Emkqson (https://pa.ci). \n\nPlease note that this bot does not guarante the availability. Regisirar's rules apply.\n\n");
    printf("Please specify TLD: ");
    scanf("%s", Ext);
    while ((read = getline(&line, &len, fp)) != -1) {
        Str_Split(line, '=', &arr);
        if (strcmp(arr[0],Ext)==0) {
	    strcpy(DomainExt,arr[0]); strcpy(NoMatchPattern,arr[2]); strcpy(WhoisQueryServer,arr[1]);
            break;
        }
    }
    if (*DomainExt == '0') {
        printf("TLD not supported!\n");
        exit(2);
    }
    fclose(fp);
    char DictFile[256];
    printf("Please specify dicitionary file: ");
    scanf("%s",DictFile);
    FILE * fp_Dict = fopen(DictFile,"r");
    if (fp_Dict==NULL) {
        printf("dicitionary file not found!\n");
        exit(3);
    }
    char c; size_t n=0;
    char DomainPrefix[70] , domain[100], *data = NULL;
    FILE * fp_Result = fopen(Str_Conn(DomainExt,"_RESULTS.DAT"),"w");
    if (fp_Result==NULL) {
        printf("Failed to write results to file!\n");
        exit(4);
    }
    fprintf(fp_Result,"\nThanks you for using DomainMegaBot!\n");
    fclose(fp_Result);
    while (1) {
        n=0;
        *DomainPrefix='\0';
        while ((c = fgetc(fp_Dict)) != '\n') {
            if (c==EOF) {
                printf("Task finished!\n\n");
                fp_Result=fopen(Str_Conn(DomainExt,"_RESULTS.DAT"),"a");
                fprintf(fp_Result,"\nThanks you for using DomainMegaBot!\n");
                fclose(fp_Result);
                fclose(fp_Dict);
                exit(0);
            }
            DomainPrefix[n++] = c;
        }
        DomainPrefix[n]='\0';
        strcpy(domain,Str_Conn(Str_Conn(DomainPrefix,"."),DomainExt));
        DomainMegaBot(domain, NoMatchPattern, WhoisQueryServer, DomainExt);
    }



    return 0;
}


int DomainMegaBot(char *domain , char * NoMatchPattern, char * WhoisQueryServer, char * DomainExt) {
    char *response = NULL ; FILE * fpR;
    do {
        whois_query(WhoisQueryServer, domain, &response);
        if (response) break;
        sleep(1);
    }
    while(1);
	if (strstr(response,NoMatchPattern)!=NULL) {
		printf("%s Available for registration!\n", domain);
		fpR=fopen(Str_Conn(DomainExt,"_RESULTS.DAT"),"a");
		fprintf(fpR,"%s\n",domain);
        fclose(fpR);
	}
	else
		printf("%s Not available.\n", domain);
	return 0;
}


int whois_query(char *server , char *query , char **response) {
    char ip[32] , message[100] , buffer[1500];
    int sock , read_size , total_size = 0;
    struct sockaddr_in dest;
    sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    memset( &dest , 0 , sizeof(dest) );
    dest.sin_family = AF_INET;
    if(hostname_to_ip(server , ip)) {
        printf("Falied to resolve hostname.");
        return 1;
    }
    dest.sin_addr.s_addr = inet_addr( ip );
    dest.sin_port = htons( 43 );
    if(connect( sock , (const struct sockaddr*) &dest , sizeof(dest) ) < 0) {
        perror("Failed to reach whois server.");
    }
    sprintf(message , "%s\r\n" , query);
    if( send(sock , message , strlen(message) , 0) < 0) {
        perror("Failed to send query.");
    }
    while( (read_size = recv(sock , buffer , sizeof(buffer) , 0) ) ) {
        *response = (char*)realloc(*response , read_size + total_size);
        if(*response == NULL) {
            printf("Falied to access system memory.");
        }
        memcpy(*response + total_size , buffer , read_size);
        total_size += read_size;
    }
    fflush(stdout);
    *response = (char*)realloc(*response , total_size + 1);
    *(*response + total_size) = '\0';
    close(sock);
    return 0;
}


int hostname_to_ip(char * hostname , char* ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL) {
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 0;
}


int Str_Split(char *str, char c, char ***arr) {
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;    char *t;
    p = str;
    while (*p != '\0') {
        if (*p == c)
            count++;
        p++;
    }
    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL) {
        printf("Unable to access system memory.");
        exit(9);
    }
    p = str;
    while (*p != '\0') {
        if (*p == c) {
	    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
	    if ((*arr)[i] == NULL){
        printf("Unable to access system memory.");
        exit(9);
        }
	    token_len = 0;
	    i++;
	}
	p++;
	token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL) {
        printf("Unable to access system memory.");
        exit(9);
    }
    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0') {
        if (*p != c && *p != '\0') {
	    *t = *p;
            t++;
	}
	else {
	    *t = '\0';
	    i++;
	    t = ((*arr)[i]);
	}
	p++;
    }
    return count;
}

char* Str_Conn(const char *s1, const char *s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = (char*)malloc(len1+len2+1);
    memcpy(result, s1, len1);
    memcpy(result+len1, s2, len2+1);
    return result;
}
