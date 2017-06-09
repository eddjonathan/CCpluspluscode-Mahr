#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define bin_number 20
#define logbin     1
char  file_in[]="ldltm15.opt";
char  file_out[]="colldltm15log20th40.dat";


/****************** distribution ****************************/

double        p[bin_number];        // normalized distribution 
double         tics[bin_number+1];   // tics position
float        min,max;              // Maximum and minimum s value

float        Phi;
int          Number_vesicle;

/***************** Cumulative data storage *******************/

float s;
float *table=NULL;
int    table_size=0;
int    table_max_size=0;

/**************** FILE *************************************/

FILE   *file1;


/****************** Functions definition ******************************/

void load_cumulative(void);
void store_cum(float);
void define_bin(void);
void distribution(void);
void save(void);

/**************** MAIN PART ***********************************/

main() {
        load_cumulative();
        define_bin();
        distribution();
        save();
}

void store_cum(float s) {
	if (table_size >= table_max_size) {
            if (table_max_size==0) table_max_size=100;
            else table_max_size +=100;
	    table = (float*)realloc(table,table_max_size*sizeof(float));
	    if (table==NULL) {
	        fprintf(stderr, "Out of memory\n");
	        exit(5);
		}
	}
        table[table_size] = s;
	table_size++;
}

void load_cumulative(void)
{
char   mot[20];
float  s1, cum1;
int te,k;

   file1=fopen(file_in,"r");
 
   fscanf(file1,"%s\n",mot);
   te=fscanf(file1,"%f, %f\n",&s1,&cum1);
   te=fscanf(file1,"%f, %f\n",&s1,&cum1);
   min=s1;
   k=1;
   Phi=s1;

   while(te==2){
         te=fscanf(file1,"%f, %f\n",&s1,&cum1);
         store_cum(s1);
         k++;
         Phi+=s1;}

 fclose(file1);
 Number_vesicle=k-1;
 max=s1;
 printf("phi=%f N=%d\n",Phi,Number_vesicle);
} 

void define_bin(void)
{
float Delta;
int k;

   if(logbin==0)  
     {
      Delta=(max-min)/((float)bin_number); 
      printf("regular bin\n");
      for(k=0;k<bin_number+1;k++){tics[k]=min+k*Delta;}
     }
   if(logbin==1) 
      {
       Delta=(1.0/((float)bin_number))*log(max/min);
       printf("log bin\n");
       for(k=0;k<bin_number+1;k++){tics[k]=min*exp((Delta)*(float)k);}
      }
   printf("min=%f %f max=%f %f Delta%f\n",min,tics[0],max,tics[bin_number],Delta);

}

void distribution(void)
{
int k,i,tot;

 tot=0;
 for(k=0;k<bin_number;k++)
     {
    for(i=0;i<table_size;i++){

        if((table[i]>=tics[k])&&(table[i]<tics[k+1]))
           {p[k]=p[k]+1.0;tot++;}
     }
}
  if(tics[bin_number]<=max) {p[bin_number-1]=p[bin_number-1]+1;tot++;}
       for(k=0;k<bin_number;k++){p[k]=p[k]/(tics[k+1]-tics[k]);}
  printf("%d\n",tot);
}


void save(void)
{

int  k,l;

    file1=fopen(file_out,"w");
    for(k=0;k<bin_number;k++) fprintf(file1,"%f %f\n",tics[k],p[k]);
    fclose(file1);

}
