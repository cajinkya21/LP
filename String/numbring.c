/*  c  Program to read lines from file using fgets()  */

#include<stdio.h>
#include<stdlib.h>

int main()
{
        char c = '.';
        char *str[10];
	char buf[256];
	int j = 0;
        FILE *f;
        f = fopen("trial.txt", "r");
        if(f)
        {
                int i = 1;
                while((fgets(buf, 256, f)) != NULL)
                {
			str[j] = buf;
			char *p = str[j];
			while(*p != '\n')
			{
				printf("%d)", i);
				while((*p) != c)
                        	{
					printf("%c", *p);
        	                	p++;
				}
				printf("%c \n", *p);
                        	i += 1;
				p++;
			}
			
		}
     	}
	fclose(f);
	return 0;
}          


/* INPUT:

India is my country.All Indians are my brothers and sisters.I love my country.I am proud of its rich and varied heritage.

OUTPUT:

1)India is my country.
2)All Indians are my brothers and sisters.
3)I love my country.
4)I am proud of its rich and varied heritage. */


