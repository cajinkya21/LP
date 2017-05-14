#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "macro.h"
typedef struct mnt{
	char name[24];
	int no_pp;
	int no_kp;
	int no_ev;
	struct mdt *mdtp;
	struct fpt *fptp;
	struct kpt *kptp;			
}mnt;

struct mdt{
	char a[100][100];
	int no;
};

typedef struct param{
	char name[24];
	char value[24];
}param;

typedef struct fpt{
	param a[24];
}fpt;

typedef struct kpt{
	param a[24];
}kpt;


void lower(char *string)
{
	int i = 0;
	while(string[i] != '\0')
	{
		string[i] = tolower(string[i]);
		i++;
	}
	string[i] = '\0';
}

int gettoken(char *temp, char token[][20], char *delim)
{
	int i = 0;
	if(*temp == '\t')
	{
		strcpy(token[0],"\0");
		i++;
	}
	char *string = strtok(temp,delim);
	while(string != NULL)
	{
		lower(string);
		strcpy(token[i],string);
		i++;
		string = strtok(NULL,delim);
	}
	return i;
}
void init_mnt(mnt *m)
{
	strcpy(m->name,"");
	m->no_pp = 0;
	m->no_kp = 0;
	m->no_ev = 0;
	m->mdtp = NULL;
	m->fptp = NULL;
	m->kptp = NULL;
}
void strsplit(char *tmp, char *name, char*value)
{
	int i = 0;
	tmp++;
	while(*tmp != '='){
		name[i++] = (*tmp);
		tmp++;
	}
	
	name[i] = '\0';
	
	tmp++;    // skipping '='
	if(strlen(tmp)>0)
	{
		i = 0;
		while((*tmp != '\0') && (*tmp != ','))
		{	value[i++] = (*tmp);
			tmp++;
		}
		value[i] = '\0';	
		
	}
	else{
		*value = '\0';
	}
	
}
void prototype(int no_token, char token[][20], mnt *m){
	char tmp[100];
	char name[50], value[50];
	int i, j, k;
	
	strcpy(m->name,token[0]);
	m->fptp = malloc(sizeof(fpt));
	m->kptp = malloc(sizeof(kpt));
	no_token--;
	i = 1;
	j = k = 0;
	while(no_token--)
	{
		if(strstr(token[i],"&") && strstr(token[i],"="))
		{
			
			strsplit(token[i],name,value);
			strcpy(m->kptp->a[k].name,name);
			strcpy(m->kptp->a[k].value,value);
			k++;
		}
		else{
			
			sscanf(token[i],"&%s",tmp);
			if(strstr(tmp,","))
				tmp[strlen(tmp)-1] = '\0';   // for replacing ',' with \0
			strcpy(m->fptp->a[j].name,tmp);
			strcpy(m->fptp->a[j].value,"\0");
			j++;
		}
		i++;
	}
	printf("\n");
	m->no_pp = j;
	m->no_kp = k;

	// debogging
			/*fpt *f;
			f = m->fptp;
			i = 0;
			printf("positional param\n");
			while(m->no_pp--)
			{
				printf("%s\t",f->a[i].name);
				i++;
			}
			printf("\n");
			printf("keyword param\n");
			i = 0;
			kpt *k1 = m->kptp;
			while(m->no_kp--)
			{
				printf("%s\t",k1->a[i].name);
				i++;
			}
			printf("\n");*/
	
}
void display(mnt *m)
{
	int i, j;
	printf("------------------------------------------------------------\n");
	printf("Macro name = %s\n",m->name);
	printf("#pp = %d\n#kp = %d\n",m->no_pp,m->no_kp);
	printf("positional_param:\n");
	printf("name\tvalue\n");
	for(i=0; i < m->no_pp; i++)
	{
		printf("%s\t",m->fptp->a[i].name);
		if(strlen(m->fptp->a[i].value) == 0)
			printf("-----\n");
		else
			printf("%s\n",m->fptp->a[i].value);
	}
	printf("keyword_param:\n");
	printf("name\tvalue\n");
	for(i=0; i < m->no_kp; i++)
	{
		printf("%s\t",m->kptp->a[i].name);
		
		if(strlen(m->kptp->a[i].value) == 0)
			printf("-----\n");
		else
			printf("%s\n",m->kptp->a[i].value);
	}
	printf("MDT :\n");
	for(i=0;i<m->mdtp->no; i++)
		fputs(m->mdtp->a[i],stdout);
	
}
// main program


int main()
{
	
	char temp[100], token[20][20], temp1[100];
	int d, no_token, i, j;
	mnt m[10];
	int mnt_cnt = 0;
	FILE *fp= fopen("macro_test","r");
	if(fp == NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}
	while(fgets(temp,108,fp)){
		if((d=strlen(temp)) == 1)
			continue;
		else
			temp[d-1] = '\t';
		
		no_token = gettoken(temp,token,"\t");
		
		if(no_token==1 && strcmp(token[0],"macro")==0){
			
			fgets(temp,108,fp);
				temp[strlen(temp) - 1] = '\t';
			
			no_token = gettoken(temp,token,"\t");
			
			
			init_mnt(&m[mnt_cnt]);
			
			prototype(no_token,token,&m[mnt_cnt]); // 1. processing the prototype statement
			
			/*Entering into model statement*/
			fgets(temp,108,fp);
			strcpy(temp1,temp);	
			temp[strlen(temp) - 1] = '\t';
			
			no_token = gettoken(temp,token,"\t");
			i = 0;
			m[mnt_cnt].mdtp = malloc(sizeof(struct mdt));
			while(no_token!=1 && strcmp(token[0],"mend")!=0)
			{
				// copy the model statement into MDT
				strcpy(m[mnt_cnt].mdtp->a[i++],temp1);
				
				fgets(temp,108,fp);
				strcpy(temp1,temp);
				temp[strlen(temp) - 1] = '\t';
				no_token = gettoken(temp,token,"\t");
			}
			m[mnt_cnt].mdtp->no = i;
			
			display(&m[mnt_cnt]);
			mnt_cnt++;
		}
		else{
			//printf("No macro header found\n");
		}
	}
	
	
	return 0;
}
