 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
// #include<stdshort int .h>


#define Nmax  1000             /******* Number of discrete s value **************/
#define Tm    10            /******* The real Time  **************************/
# define Smax 1000           /******* Real Value of S *************************/
# define TRUE 1 
# define FALSE 0
const int T_step=5;        /** Time step for which Steady is to be computed *****/  

double p[Nmax+1];             /** Endosome size distribution **********************/
double cum[Nmax+1];           /** Cumulative distribution cum(s)=\int_0^s p(s)/N **/ 
double pth[Nmax+1];           /** Theoretical size distribution *******************/
float N;                      /** Number of endosome ********** N=\int p(s)ds *****/
double phi;                   /** Number of endosomes component phi=\int p(s)sds **/
double Nth;                   /** Theoretical EE number ***************************/ 
double phi_th;                /** Theoretical components number *******************/

double H[Nmax+1];             /** Distribution change rate H(s)= dn(s)/dt *********/
short int  compare(char *filename,char *filename_old,int k_max_old);

/*************** MODEL's PARAMETRIC FUNCTIONS ******************************/

float   K[Nmax+1][Nmax+1];    /** EE-EE fusion Kernel ***********************/
float K_f[Nmax+1][Nmax+1];   /** EE -> EE+EE fission Kernel ****************/
float v_in[Nmax+1];          /** Growth velocity by component absorption ***/
float v_out[Nmax+1];         /** Shrink velocity by component release ******/
float A_p[Nmax+1];           /** Endosome creation rate (source) ***********/
float k_m[Nmax+1];           /** Endosome degradation rate (sink) **********/
float a;
float b;
float c;
float d;
// double Kf;
/************** IN/OUT FLUXES OF COMPONENT through the network *************/

double Jin;                   /** in-flux by component absorption ******/
double Jp;                    /** in-flux by EE creation ***************/
double Jout;                  /** out-flux by component release ********/
double Jm;                    /** out-fux by EE degradation ************/

/************************ DESCRITIZATION SCHEME ************************************************************/
double  eps = (double) Smax/Nmax ;  

// double eps   = (double) 1;    
/** Descritization parameter Epsilon ******/    
double e = (double)1 ;
double x0 = (double) 6;
/*************** FUNCTION DECLARATION ******************************************/
void   initial(void);         /** Define the parametric functions and p(s,t=0) *******/
void   theory(void);          /** Compute the theoretical distribution ***************/
void   integrals(void);       /** Compute the contributions of H(s) = dn(s)/dt *******/
void   evolution(void);       /** Compute n(s,t+dt)=n(s,t)+dt*H(s) *******************/
void    import (void);
void import2 (void);
/***********************Compute the total fluxes ********************************/

void save(char* filename);            /** Save n(s) into a .dat file *****************/
 
double theta(int m, int n);   /** Step function **************************************/
double Delta(double m, double  n);   /** Delta function ******************************/

const float the_epsilon=0.01;


double dt=0.1; 
int t=0;
char data[1000];
FILE *file;



/**************** MAIN PART *****************************************************/

main(int argc, char **argv)
{
  
    char mybuff[40]; 
    int T= Tm;
    double Kf;	
//     const int T_step=100;
    short int condition_1=FALSE;
    double n=0;
    char filename2[40];
    char filename2_old[40];

    while(!condition_1)
    {
	printf("This is time %i \n",T);fflush(stdout);
	
	n= T/dt;
	initial();

	for(t=0;t<T;t++)
{
	   
 int k, Jp=1; 
 double s;
   	    for(k=1;k<Nmax+1;k++)
                  
              { s= (double) eps*k;
      A_p[k]= (double) exp(-(s/x0))/(pow(x0,2));
// (1.1299)*(exp(-pow(((s-x0)/x0),2)))/(pow(x0,1)); 

//  A_p[k]=(double) 1*pow(k,1-1)/pow(2,1)*exp(-pow((k/2),1));

//  A_p[k]=(double)(1.1299)*(exp(-(eps*eps*k*k)/(x0*x0)))/(x0); 
}
	    integrals();
	    evolution();
	}

if(T>Tm){ strcpy(filename2_old,filename2);} else{strcpy(filename2_old,"");}/*********  compares only after Time step ******/
	sprintf(filename2,"Fusion46_%i.dat",T);
	printf("%i %s %s\n",T,filename2_old,filename2);
	save(filename2);

	if(T>Tm) {if(compare(filename2,filename2_old,Smax))   /***** Function compare declared ****************/ 	
	{
	    condition_1=TRUE;}                                /****Boolean condition**************************/

}
	T+=T_step;
	printf("After Increasing Time  %i \n", T);
    }
}

void initial(void)
{
    int k,l;
    double s,s1,delta;

    Jp=1.0;
    phi=1;
    v_in[0]=0.0;
    p[0]=0;

    for(k=1;k<Nmax+1;k++)
    {
	    s=(double)eps*(k);
            p[k]=(double)(exp(-(s)/(x0)))/(x0*x0);
// (exp(-(s)/(x0)))/(x0*x0);

            v_in[k]= (float) (double)0.0;
            v_out[k]=(float) (0.0);
//              A_p[k]=(double)e*e*(1000)*exp(-k);
            k_m[k]= (double)((.0006)*(s*s))/(s+400) ;
// (double)(0.0007*s)*(1-exp(-(pow((s/350),2)))) ;
// ((.0006)*(s*s))/(s+400) ;
// (double)(1)*(1-exp(-(pow((s/500),4))));
for(l=1;l<Nmax+1;l++)
   {
           s1=(double)eps*l ;

     K[k][l]=(double)(1) ; /***theta(Nmax,k+l)****/
    K_f[k][l]=(double)(0.0)*(e*e)*(eps*l*Delta(k,1)+eps*k*Delta(l,1)) ;
        }
    }

    p[Nmax]=0;
    v_out[Nmax]=0;
    v_out[1]=0;
}




void integrals(void)
{
    int l,k;
    double Fus_p,Fus_m,Fis_p,Fis_m,jin,jout,scr,deg ;
    
//     e=(double)(1/eps);

    for(k=1;k<Nmax;k++)
    {
                Fus_p=0;Fus_m=0;Fis_p=0;Fis_m=0;

	        scr=A_p[k];
	        deg=p[k]*k_m[k];
	        jin= (float)((v_in[k-1])*(p[k-1]-p[k])+(p[k-1]*(v_in[k-1]-v_in[k])))/eps;
	        jout=(float)(((v_out[k])*(p[k+1]-p[k]))+((p[k])*(v_out[k+1]-v_out[k])))/eps;


    for(l=1;l<Nmax;l++)
	{
	    {
		  Fus_m+=(1.0)*eps*K[k][l]*p[k]*p[l];
    if(k>l)       Fus_p+=(0.5)*eps*K[k-l][l]*p[l]*p[k-l];
	    }
    if(k>l)       Fis_m+=(0.5)*eps*K_f[k-l][l]*p[k];
    if(k+l<Nmax)  Fis_p+=(1.0)*eps*K_f[k][l]*p[l+k];
	}

	H[k]=-Fus_m+Fus_p-Fis_m+Fis_p+jin+jout+scr-deg;
// -Fis_m+Fis_p+jin+jout+scr-deg
    }
}



void evolution(void)
{
    int k;
    double max,rel;
    double sum1,sum2;
 
    sum1=0;sum2=0;
    max=0;

    for(k=1;k<Nmax;k++){

        p[k]+=dt*H[k];

        cum[k]=cum[k-1]+p[k];
        sum1+=p[k];
        sum2+=(double)k*p[k];  

        rel=H[k]/p[k];
        if(sqrt(rel*rel)>max) max=sqrt(rel*rel);

        if(p[k]*p[k]>100000) {printf("problem!!"); break;};
    }
    N=sum1;
    phi=sum2;
//     printf("%d %f \n", t, N); 
}


void save(char* filename)
{
   
    double r; 

    int k;

    file=fopen(filename,"w");

    for(k=1;k<Nmax+1;k++)
{
	
	r=(double)eps*(k);
	fprintf(file,"%f %6.50f \n",r,p[k]);}
        fclose(file);

	


}

double Delta (double m, double  n)
{
    double d;
    if(m==n) d=1.0;else d=0.0;
    return d;
}

double theta (int m, int n)
{
    double d;
    if(m>n) d=1.0;else d=0.0;
    return d;
}

short int  compare(char* filename,char* filename_old,int k_max_old)
{
    printf("Compare\n");fflush(stdout);
    short int  result=TRUE;
    FILE *file_new;
    FILE *file_old;
 float  k_new=0;
    float k_old=0;
    float p_k_new=0;
    float p_k_old=0;
//open files
    file_new=fopen(filename,"r");
    file_old=fopen(filename_old,"r");
	
    for(int k_count=0;k_count<k_max_old;k_count++)
    {
//read line from new file
	fscanf(file_new,"%f %f",& k_new,& p_k_new);
//read line from old file
	fscanf(file_old,"%f %f",& k_old,& p_k_old);

//do the comparision
	printf("%i %6.8f %6.8f %6.8f\n",k_count,p_k_new,p_k_old,fabs((p_k_new-p_k_old)/p_k_old));
	result=result&&fabs((p_k_new-p_k_old)/p_k_old)<the_epsilon?TRUE:FALSE;
printf("result ternaery%i\n", fabs((p_k_new-p_k_old)/p_k_old)<the_epsilon?TRUE:FALSE);
	if(!result)
	{
	    k_count=k_max_old; //break the loop
	}
    }
//close files
    fclose(file_new);
    fclose(file_old);

    return result;
}

