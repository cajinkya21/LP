#include<stdio.h>
#include<string.h>
typedef struct mot{
	char name[100][100];
	int length;
	int opcode[100];



}mot;
typedef struct sot{
	char sym[100][100];
	int length[100];
	int add[100];
	char type[100][100];

}sot;
typedef struct pot{
	char psu[100][100];
	int length[100];
	int operand[100];

}pot;
typedef struct inter{
	int lc;
	int loc[100];
	int operand[100];
	char operand1[100][100];
}inter;
//a=mnemonics count,count=symbols count,i=overall length
int main(){
	mot mot;
	pot pot;
	sot sot;
	inter inter;
	FILE *fp;
	int i=0,j,d,count=0,z=0,count_dup=0,u=0,a=0,x=0,y=0,inter_count=0;
	char buff[100],word[100][100],sym[100][100];
	fp=fopen("ss.txt","r");
	while(!feof(fp)){
	fscanf(fp,"%s",buff);
		strcpy(word[i],buff);
		i++;



	}
	//grouping of symbols and mnemonics
	for(j=0;j<(i-1);){
		if(strcmp(word[j],"mov")==0  || strcmp(word[j],"add")==0 || strcmp(word[j],"sub")==0 || strcmp(word[j],"mult")==0 || strcmp(word[j],"load")==0 || strcmp(word[j],"store")==0 || strcmp(word[j],"read")==0 || strcmp(word[j],"write")==0 || strcmp(word[j],"jmp")==0 || strcmp(word[j],"jz")==0 || strcmp(word[j],"stop")==0 || strcmp(word[j],"halt")==0){
			strcpy(mot.name[a],word[j]);
			
			j++;
			a++;
			
		
		}
		else{
			if(strcmp(word[j],"ax")==0  || strcmp(word[j],"db")==0 || strcmp(word[j],"dw")==0 || strcmp(word	[j],"const")==0 ){
				j++;				
			}
			else{
				
				strcpy(sot.sym[u],word[j]);
				count++;
				//printf("%d",count);
				u++;
				j++;	
			}

		}
		
	}
	
	//removing duplicate from mot
	int k;
	for(j=0;j<a;j++){
		for(d=j+1;d<a;){
			if(strcmp(mot.name[j],mot.name[d])==0){
				for(k=d;k<a;k++){
					strcpy(mot.name[k],mot.name[k+1]);
					

				}
				a--;
				
				
			}
			else{

				d++;
			}

			
		

		}
			
	}
	
	//removing duplicate from sot
	
	for(j=0;j<count;j++){
		for(d=j+1;d<count;){
			if(strcmp(sot.sym[j],sot.sym[d])==0){
				for(k=d;k<count;k++){
					strcpy(sot.sym[k],sot.sym[k+1]);
					

				}
				count--;
				
				
			}
			else{

				d++;
			}

			
		

		}
			
	}
	//giving length to symbols AND finding length of halt
	int s;
	for(k=0;k<i-1;k++){
		if(strcmp(word[k],"halt")==0 || strcmp(word[k],"stop")==0){
			s=k;
		}
	}
	
	for (j=s+1;j<i-1;){
		if(strcmp(sot.sym[z],word[j])==0){
				j++;
				if(strcmp(word[j],"db")==0){
					sot.length[z]=1;
					strcpy(sot.type[z],"VAR");
					strcpy(pot.psu[z],"db");  //insert data into pot
					
				}
				if(strcmp(word[j],"dw")==0){
					sot.length[z]=2;
					strcpy(sot.type[z],"VAR");
					strcpy(pot.psu[z],"dw");
					
				}
				if(strcmp(word[j],"const")==0){
					sot.length[z]=1;
					strcpy(sot.type[z],"CONST");
					strcpy(pot.psu[z],"CONST");
					
					
				}
				if(strcmp(word[j],"end")==0){
					
					strcpy(pot.psu[z],"CONST");
					
					
				}
				if(strcmp(word[j],"endp")==0){
					strcpy(pot.psu[z],"CONST");
					
					
				}
				
				z++;
				j++;
				 
		}
		
		
		else{
			j++;
		}
	
	}

	int p =z;
	
	//removing duplicate from pot
	
	for(j=0;j<p;j++){
		for(d=j+1;d<p;){
			if(strcmp(pot.psu[j],pot.psu[d])==0){
				for(k=d;k<p;k++){
					strcpy(pot.psu[k],pot.psu[k+1]);
					

				}
				p--;
				
				
			}
			else{

				d++;
			}

			
		

		}
			
	}
	

	for(j=0;j<p;j++){
		printf("%s\n",pot.psu[j]);
		if(strcmp(pot.psu[j],"db")==0){
			pot.length[j]=1;
			pot.operand[j]=2; //insert data into pot
					
		}
		if(strcmp(pot.psu[j],"dw")==0){
			pot.length[j]=2;
			pot.operand[j]=2; //insert data into pot
					
		}
		if(strcmp(pot.psu[j],"const")==0){
			pot.length[j]=1;
			pot.operand[j]=2; //insert data into pot
					
		}
		if(strcmp(pot.psu[j],"end")==0){
			pot.length[j]=1;
			pot.operand[j]=0; //insert data into pot
					
		}
		if(strcmp(pot.psu[j],"endp")==0){
			pot.length[j]=1;
			pot.operand[j]=0; //insert data into pot
					
	}	
	}
	//giving opcodes to mot from user

	printf("\nEnter opcodes for:\n");
	for(j=0;j<a;j++){
		printf("%s\t",mot.name[j]);
		scanf("%d",&mot.opcode[j]);
		

	}
	
	//creating intermediate file here x for mot,y for sot,loc array,inter_count to count length of inter_file

	inter.lc=0;
	for(j=0;j<i-1;j++){
		for(x=0;x<a;x++){
			if(strcmp(word[j],mot.name[x])==0){
				inter.lc=inter.lc+1;
				inter.loc[j]=inter.lc; //stre lc	
				inter.operand[j]=mot.opcode[x];	
			}
		}
		for(y=0;y<count;y++){
			 if(strcmp(word[j],sot.sym[y])==0){
				inter.lc=inter.lc+sot.length[y];
				inter.loc[j]=inter.lc;
				strcpy(inter.operand1[j],sot.sym[y]);					
			}
		}
		if(strcmp(word[j],"ax")==0){
			inter.lc=inter.lc+0;
			inter.loc[j]=inter.lc;
			inter.operand[j]=16;					
		}
		
		
		
	}
	
	//printing intermediate file
	printf("\nINTERMEDIATE FILE PASS 1:\n");
	
	for(j=0;j<i-1;j++){
		for(x=0;x<a;x++){
			if(strcmp(word[j],mot.name[x])==0){
				printf("\n%d\t%d\n",inter.loc[j],inter.operand[j]);
			}
		}
		for(y=0;y<count;y++){
			 if(strcmp(word[j],sot.sym[y])==0){
				printf("\n%d\t%s\n",inter.loc[j],inter.operand1[j]);					
			}
		}
		if(strcmp(word[j],"ax")==0){
			printf("\n%d\t%d\n",inter.loc[j],inter.operand[j]);
							
		}
		if(inter.loc[j]==0){
			continue;
		}
		
		
		
	}
	
	//coping address of symbol in sot
	for(j=s+1;j<i-1;j++){
		for(y=0;y<count;y++){
			 if(strcmp(inter.operand1[j],sot.sym[y])==0){
				sot.add[y]=inter.loc[j];
				inter.operand[j]=sot.add[y];						
			}
		}
	}
	for(j=0;j<i-1;j++){
		for(y=0;y<count;y++){
			 if(strcmp(inter.operand1[j],sot.sym[y])==0){
				inter.operand[j]=sot.add[y];						
			}
		}
	}
	
	printf("\nMOT\n");
	printf("MNEMONIC\tOPCODE\n");
	for(j=0;j<a;j++){
		
		printf("%s\t\t",mot.name[j]);
		printf("%d\n",mot.opcode[j]);
		

	}
	printf("\nSOT PASS 1\n\n");
	printf("NAME\t\tTYPE\t\tADDRESS\n\n");
	for(j=0;j<a;j++){
		
		printf("%s\t\t%s\t\t%s\n",sot.sym[j],"ID","-");
	}	
	
	printf("\nOUTPUT FILE:\n\n");
	for(j=0;j<i-1;j++){
		if(inter.loc[j]==0){
			continue;
		}
		else{
		printf("\n%d\t%d\n",inter.loc[j],inter.operand[j]);
		}
	}
	
	printf("\nSOT PASS 2\n\n");
	printf("NAME\t\tTYPE\t\tADDRESS\n\n");
	for(j=0;j<a;j++){
		
		printf("%s\t\t%s\t\t%d\n",sot.sym[j],sot.type[j],sot.add[j]);
	}

	printf("\nPOT \n\n");
	printf("PSU\t\tOPERAND\t\tLENGTH\n\n");
	for(j=0;j<p;j++){
		printf("%s\t\t%d\t\t%d\n",pot.psu[j],pot.operand[j],pot.length[j]);
	}	
		
return 0;
}

