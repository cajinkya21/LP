#include<ctype.h>
#include<stdio.h>
#include<string.h>


typedef struct Employee
{
	char fname[20];
	char mname[20];
	char lname[20];
	char address[20];
	int  bdate[20];
	char sex[20];
	char sub_taken[20];
	char last_edu[20];
	char join_date[20];
	
	int id;
	int age;
	int bsal;
	
}Employee;
FILE *outfile,*infile,*fr;
Employee emp;
int main()
{

	int id;
	FILE *outfile,*infile;
	int choice1;
		int n,i,c=0;
		char fname[10];
		outfile = fopen ("hj.txt","a+");
		 
		printf("Enter number of records you want to add:\n");
		scanf("%d",&n);
		for(i=0;i<n;i++)
     		{
      			printf("enter id:");
			scanf("%d",&emp.id);
			printf("Enter first name:");
                        scanf("%s",emp.fname);        		
			printf("Enter  middle name: ");
                        scanf("%s",emp.mname);
                        printf("Enter  last name: ");
                        scanf("%s",emp.lname);
                        printf("Enter the address: ");
                        scanf("%s",emp.address);
                        printf("Enter the sex: ");
                        scanf("%s",emp.sex);
                        printf("Enter the age: ");
                        scanf("%d",&emp.age);
                        printf("Enter the basic_salary: ");
                        scanf("%d",&emp.bsal);
                        printf("Enter the joining_date: ");
                        scanf("%s",emp.join_date);
                      	printf("Enter the last_education: ");
                        scanf("%s",emp.last_edu);
                        printf("Enter the subject_taken: ");
                      	scanf("%s",emp.sub_taken);
     			fwrite (&emp, sizeof(emp), 1, outfile);
     			
		}
		fclose(outfile);
		outfile = fopen ("hj.txt","a+");
		if(outfile==NULL)
      		{
      			fprintf(stderr, "\nError opening empty file\n\n");
      			
    		}
		
		printf("id\t| Name\t| middle_name\t|  last_name\t|  Address\t| Sex\t|   Age\t| Basicsalary\t|  Joint_date\t|  Last_education\t| Subject_taken\t|\n");

		while (fread (&emp, sizeof(emp), 1, outfile)==1)
			 
			printf(" |%-10d| %-10s| %-10s| %-10s| %-10s| %-10s|   %-10d| %-10d| %-10s| %-10s| %-10s|\n",emp.id,emp.fname, emp.mname, emp.lname, emp.address ,emp.sex ,emp.age, emp.bsal,emp.join_date,emp.last_edu,emp.sub_taken);		


	        printf("enter name of employ to search: \n");
	outfile = fopen ("hj.txt","a+");
	scanf("%s",fname);
        while(fread(&emp,sizeof(emp),1,outfile)){
		if(strcmp(fname,emp.fname)==0){
       			printf("\nRECORD EXISTS AND DETAILS ARE :\n");
			printf("|%-10d| %-10s| %-10s| %-10s| %-10s| %-10s| %-10d| %-10d| %-10s| %-10s| %-10s|\n",emp.id,emp.fname, emp.mname, emp.lname, emp.address ,emp.sex ,emp.age, emp.bsal,emp.join_date,emp.last_edu,emp.sub_taken);
        
		}
	}
 	if(strcmp(fname,emp.fname)!=0){
		printf("\n RECORD DOESNOT EXISTS\n");
       		//fclose(outfile);
 	}
return(0);

}
