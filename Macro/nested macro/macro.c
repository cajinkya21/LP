#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//----------------------------------------------------- Initialisation of Data Structures ------------------------------------------------//

typedef struct apt {
	char *formal[10][2];
}apt;

int count = 0;

typedef struct mnt {
	char name[10];
	int pp;
	int kp;
	int mdtp;
	struct apt *aptp;
	struct mnt *next;
}mnt;

int main () {

//---------------------------------------------------------- Data Variables --------------------------------------------------------//

	int i, pc = 0, kc = 0, temp = 100, n, l, l1, l2, j, flag = 0, flag1 = 0, mec, nest = 0;
	char fs[10] = "xyz", *pm, *pm1;
	char c, fs1[10];
	c = 'a';
	char line[100], line1[100];
	mnt *p, *q, *q1;
	mnt *head = NULL;
	FILE *fsp, *mdt, *fnl, *mdt1;
	fsp = fopen ("srcprog.txt", "r");
	mdt = fopen ("mdt.txt", "w");
	fnl = fopen ("final.txt", "w");
	printf ("\n");

	while (strcmp (fs, "start") != 0) {
		fscanf (fsp, "%s", fs);
		if (strcmp ("macro", fs) == 0) {	//	Here macro definition is found
			count++;
			p = (mnt *)malloc(sizeof (mnt));
			p -> next = NULL;
			if (head == NULL) {
				head = p;
			}
			q = head;
			while (q -> next != NULL) {
				q = q -> next;
			}
			if (count > 1)
				q -> next = p;

//------------------------------------- Calculating macro name, no of positional and keyword parameters ------------------------------//

			fscanf (fsp, "%s", p -> name);
			while (c != '\n') {
				c = fgetc (fsp);
				if (c == 38)
					pc++;
				else if (c == 61)
					kc++;
			}
			p -> kp = kc;
			n = pc;
			p -> pp = pc - kc;
			p -> mdtp = temp;
			printf ("Macro Definition found with \tpp = %d,\t\tkp = %d,\t\tMDT pointer = %d\n\n", p -> pp, p -> kp, temp);
			p -> aptp = (apt *)malloc(sizeof (apt));
			fclose (fsp);
			fsp = fopen ("srcprog.txt", "r");
			fscanf (fsp, "%s", fs);
			while (strcmp (fs, p -> name) != 0)
				fscanf (fsp, "%s", fs);
			for (i = 0; i < n; i++) {
				fscanf (fsp, "%s", fs);
				l = strlen (fs);
				pm = malloc (sizeof (l + 1));
				strcpy (pm, fs);
				p -> aptp -> formal [i][0] = pm;
			}

//----------------------------------------------------- Making Entries in MDT -------------------------------------------------//

			fgets (line, 100, fsp);
			while (strcmp (fs, "mend") != 0) {
				fgets (line, 100, fsp);
				sscanf (line, "\t%s", fs);
				fprintf(mdt, "%d", temp);
				fputs (line, mdt);
				temp++;
			}
			fclose (mdt);
			mdt = fopen ("mdt.txt", "a");
		}
		pc = 0;
		kc = 0;
		c = 'a';
	}

//----------------------------------------------------- Writing to output file -------------------------------------------------//

	fprintf (fnl, "\t%s", fs);
	fscanf (fsp, "%s", fs);
	fprintf (fnl, "\t%s\n", fs);
	fgets (line, 100, fsp);

	while (strcmp (fs, "end") != 0) {
		fgets (line, 100, fsp);
		if (line[0] == '\t')
			sscanf (line, "\t%s", fs);
		else
			sscanf (line, "%s\t%s", fs1, fs);
		q = head;
		while ((strcmp (q -> name, fs) != 0) && q -> next != NULL) {
			q = q -> next;
		}

		if (strcmp (q -> name, fs) == 0) {		//	Here macro call is found
			printf ("Macro call found with name '%s'\n\n", fs);
			fclose (fsp);
			fsp = fopen ("srcprog.txt", "r");
			fscanf (fsp, "%s", fs1);
			while (strcmp (fs1, "start") != 0) {	// Go upto 'start' in source program
				fscanf (fsp, "%s", fs1);
			}
			fscanf (fsp, "%s", fs1);
			while (strcmp (fs1, fs) != 0) {		// Go upto macro call in source program
				fscanf (fsp, "%s", fs1);
			}

//----------------------------------------------------- Making Entries in APDT -------------------------------------------------//

			for (i = 0; i < q -> pp; i++) {	
				fscanf (fsp, "%s", fs);
				l = strlen (fs);
				pm1 = malloc (sizeof (l + 1));
				strcpy (pm1, fs);
				q -> aptp -> formal [i][1] = pm1;
			}
			mdt = fopen ("mdt.txt", "r");
			fscanf (mdt, "%d", &i);
			fscanf (mdt, "%s", fs);
			while (i != q -> mdtp) {
				fscanf (mdt, "%d", &i);
				fscanf (mdt, "%s", fs);
			}
			l = 0;
			while (strcmp (fs, "mend") != 0) {	//	counting no of lines in MDT for a macro
				fscanf (mdt, "%s", fs);
				c = fgetc (mdt);
				if (c == '\n')
					l++;
			}
			fclose (mdt);
			mdt = fopen ("mdt.txt", "r");
			fscanf (mdt, "%d", &i);
			fscanf (mdt, "%s", fs);
			while (i != q -> mdtp) {
				fscanf (mdt, "%d", &i);
				fscanf (mdt, "%s", fs);
			}
			l--;

//----------------------------------------------------- Actual expanding the macro -------------------------------------------------//

			c = fgetc (mdt);
			fputc ('\t', fnl);
			while (strcmp (fs, "mend") != 0) {
				for (i = 0; i < (q -> pp + q -> kp); i++) {
					if (strcmp (fs, q -> aptp -> formal[i][0]) == 0) {	// formal parameter found in MDT
						flag = 1;
						fprintf (fnl, "%s", q -> aptp -> formal[i][1]);		//  Raplace it with actual parameter
						if (l == 0)
							break;
						//fputc (c, fnl);
						fprintf (fnl, "%c", c);
						if (c == '\n')
							fputc ('\t', fnl);
					}
				}
				if (flag == 0) {
					fprintf (fnl, "%s", fs);
					fputc (c, fnl);
					if (c == '\n')
						fputc ('\t', fnl);
				}
				flag = 0;
				fscanf (mdt, "%s", fs);
				q1 = head;
				while ((strcmp (q1 -> name, fs) != 0) && q1 -> next != NULL) {
					q1 = q1 -> next;
				}

				if (strcmp (q1 -> name, fs) == 0) {		//	Here nested macro call is found
					nest = 1;
					printf ("\tNested macro call found with name '%s'\n\n", fs);
					for (j = 0; j < q1 -> pp; j++) {
						fscanf (mdt, "%s", fs);
						for (i = 0; i < (q1 -> pp + q1 -> kp); i++) { 	// placing actual parameters of parent macro
							if (strcmp (fs, q -> aptp -> formal[i][0]) == 0) {
								strcpy (fs, q -> aptp -> formal[i][1]);
								l2 = strlen (fs);
								pm1 = malloc (sizeof (l2 + 1));
								strcpy (pm1, fs);
								q1 -> aptp -> formal [i][1] = pm1;
								break;
							}
						}
					}
					fclose (mdt);
					mdt = fopen ("mdt.txt", "r");
					fscanf (mdt, "%d", &i);
					fscanf (mdt, "%s", fs);
					while (i != q1 -> mdtp) {
						fscanf (mdt, "%d", &i);
						fscanf (mdt, "%s", fs);
					}
					l1 = 0;
					while (strcmp (fs, "mend") != 0) {	//	counting no of lines in MDT for the nested macro
						fscanf (mdt, "%s", fs);
						c = fgetc (mdt);
						if (c == '\n')
							l1++;
					}
					fclose (mdt);
					mdt = fopen ("mdt.txt", "r");
					fscanf (mdt, "%d", &i);
					fscanf (mdt, "%s", fs);
					while (i != q1 -> mdtp) {
						fscanf (mdt, "%d", &i);
						fscanf (mdt, "%s", fs);
					}
					l1--;

					c = fgetc (mdt);
					//fputc ('\t', fnl);
					while (strcmp (fs, "mend") != 0) {
						for (i = 0; i < (q1 -> pp + q1 -> kp); i++) {
							if (strcmp (fs, q1 -> aptp -> formal[i][0]) == 0) {
								flag1 = 1;
								fprintf (fnl, "%s", q -> aptp -> formal[i][1]);
								if (l1 == 0)
									break;
								fputc (c, fnl);
								if (c == '\n')
									fputc ('\t', fnl);
							}
						}
						if (flag1 == 0) {
							fprintf (fnl, "%s", fs);
							fputc (c, fnl);
							if (c == '\n')
								fputc ('\t', fnl);
						}
						flag1 = 0;
						fscanf (mdt, "%s", fs);
						c = fgetc (mdt);
						if (c == '\n') {
							l1--;
							fscanf (mdt, "%d", &j);
						}					
					}
					mec++;
					l--;
					fprintf (fnl, "\n\t");

				}						// nested macro expansion ends here

				if (nest == 1) {
					fclose (mdt);
					mdt = fopen ("mdt.txt", "r");
					fscanf (mdt, "%d", &i);
					fscanf (mdt, "%s", fs);
					while (i != mec) {			//  Resuming with the expansion of parent macro
						fscanf (mdt, "%d", &i);
						fscanf (mdt, "%s", fs);
					}
					nest = 0;
				}
				c = fgetc (mdt);
				if (c == '\n') {
					l--;
					fscanf (mdt, "%d", &j);		//  skip the numbering in the MDT
					mec = j;
				}
			}
		}
		else {
			fputs (line, fnl);
		}
	}
	fclose (mdt);
	fclose (fsp);
	fclose (fnl);
	return 0;
}
