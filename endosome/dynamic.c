#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define kmax 50
#define T    7000
#define smax 10000
#define Timage 100 

/**** THIS VERSION ACHIEVED THE 03.11.08 
      SEEMS TO WORK ("QUALITATIVELY") 
      TO COMPUTE THE DISTRIBUTION WITH LOG BINING     
****/

/**** IT SHOULD BE 1) TESTED (compared with previous results)
      AND 2) IMPROVED .********/ 

double n[kmax+1];
double p[kmax+1];
double H[kmax];
double Nt[T];
double Ntt[T];
double phit[T];
double phitt[T];
double sc[T];

double No;
void import(void);
void    initial(void);
double  K(double s1, double s2);
double  A(double s, int t);
  double A1[kmax+1];
double  kd(double s);
double  vin(double s);
double  vins(double s, int t);
double  vout(double s);
double  Kf(double s1, double s2);
double  dz;
double  p_extra(double s);
double  extrapole_bound(void);

void   increment(void);
void   evolution(void);
void   save(int m);
void   save_glob(void);
double theta(int m, int n);
double Delta(double m, double  n);

double dt=0.01; 
double smin=10;
int t=0;
int end=0;
char data[100];
FILE *file;
int t0;
int step=T/Timage;


/**************** MAIN PART *****************************************************/

main()
{
   import();	
   dz=log(smax+1)/kmax;
   initial();

    for(t=0;t<T;t++)
     {
int k;
double z,s,z0,s0,sm,sp,zm,zp;
for(k=0;k<kmax+1;k++)
{

       z=dz*((double)k+0.5);
// z0=dz*((double)2);
s=exp(z)-1.0;
// s0=exp(z0);
	sm=exp(zm)-1.0;
       	sp=exp(zp)-1.0;
	zm=dz*((double)(k-1)-0.5);
       	zp=dz*((double)(k+1)+0.5);
{ 
//  double  vin(s)= (5)*theta(t,0);

A1[k]=(double)(0)*theta(t,0)*((exp(-(s)/(1)))/((pow(1,2))));

// A[k]=(double)(1.1299)*(exp(-pow(((s-10)/10),2)))/(pow(10,1));
//      A[k]=(double) (1.0)*theta(t,0)*((exp(-(s+1.0-exp(dz))/(3.0)))/((pow(3.0,2))));
 
}
}
        increment();
        evolution();
         t0=(int)((double)t/step);
        if(t==step*t0) save(t0);
        if(end==1) t=T+1;
       }
   save_glob();
}
void import(void)
{
int k;
float r,c;

   file=fopen("n20056.dat","r");
   for(k=0;k<kmax+1;k++){
        fscanf(file,"%f %f",&r,&c);
        n[k]=c;
   }
}


void initial(void)
{
  int k;
  double z,s,c,r;
//  	file=fopen("n20079.dat","r");
  for(k=0;k<kmax+1;k++)
{
z=dz*((double)k+0.5);
       s=exp(z)-1.0;
// fscanf(file,"6.10%f 6.10%f \n",&r,&c);
      p[k]= 1*exp(-s);
//  4*(pow(s,-0.9))*exp(-s/150);
        
       
// 0.1*exp(-s);
// 4*(pow(s,-0.9))*exp(-s/130);
// 0.0*exp(-s);
   }
}

double p_extra(double s)
{ int i;
  double a1,out,sp,sm,z,zp,zm;
  
  z=log(s+1.0);
  i=(int)(z/dz-0.5);

  zm=dz*((double)i+0.5);
  zp=dz*((double)(i+1)+0.5);
  sm=exp(zm)-1.0;
  sp=exp(zp)-1.0;

  if(i!=z/dz-0.5)
  a1=((log(p[i+1])-log(p[i]))/((log(sp)-log(sm))))*(log(s)-log(sm));
  else    a1=0.0;
  if((p[i]==0.0)||(p[i+1]==0.0)) a1=0.0;

  out=p[i]*exp(a1);
  return out;
}

double extrapole_bound(void)
{ int i;
  double a1,out,s2,s1,z,z1,z2,s;
  
  z=dz*((double)kmax+0.5);
  z1=dz*((double)kmax-1.0+0.5);
  z2=dz*((double)kmax-2.0+0.5);

  s1=exp(z1)-1.0;
  s2=exp(z2)-1.0;
  s=exp(z)-1.0;

  if((p[kmax-2]!=0.0)&&(p[kmax-1]!=0.0))
        a1=((log(p[kmax-1])-log(p[kmax-2]))/(s1-s2))*(s-s1);
  else a1=0.0;
  out=p[kmax-1]*exp(a1);
  return out;
}

void increment(void)
{
  int k,l,i;
  double fus1,fus2,srce,deg,s,s1,z1,z,ds1,
         fis1,fis2,grow,shrink,sp,sm,zp,zm,Nsup,phisup,ds;

   for(k=0;k<kmax;k++){
       z=dz*((double)k+0.5);
       s=exp(z)-1.0;

       fus1=0;
       fus2=0;
       fis1=0;
       fis2=0;
       grow=0;
       shrink=0;

       for(l=0;l<kmax;l++){
            z1=dz*((double)l+0.5);
            s1=exp(z1)-1.0;
            ds1=exp(z1)*dz;
            fus1+=p[k]*p[l]*K(s1,s)*ds1;}

       for(l=0;l<kmax;l++){
            z1=dz*((double)l+0.5);
            s1=exp(z1)-1.0;
            ds1=exp(z1)*dz;
            if(s1<s/2) fus2+=p[l]*p_extra(s-s1)*K(s1,s-s1)*ds1;}

       for(l=0;l<kmax;l++){
            z1=dz*((double)l+0.5);
            s1=exp(z1)-1.0;
            ds1=exp(z1)*dz;
            if(s1<s/2) fis1+=p[k]*Kf(s1,s-s1)*ds1;}

       for(l=0;l<kmax;l++){
            z1=dz*((double)l+0.5);
            s1=exp(z1)-1.0;
            ds1=exp(z1)*dz;
            if(s+s1<smax) fis2+=p_extra(s+s1)*Kf(s,s1)*ds1;}

       zm=dz*((double)(k-1)+0.5);
       zp=dz*((double)(k+1)+0.5);
       sm=exp(zm)-1.0;
       sp=exp(zp)-1.0;

       shrink=(vout(s)*p[k]-vout(sp)*p[k+1])/(dz*(s+1.0));

       if(k!=0) grow=(vins(sm,t)*p[k-1]-vins(s,t)*p[k])/(dz*(s+1.0));
       else     grow=-vins(s,t)*p[k]/(dz*(s+1.0));//grow=0.0/(dz*(s+1.0));

       srce=A(s,t);
       deg=kd(s)*p[k];

       H[k]=srce-fus1+fus2-fis1+fis2-deg+shrink+grow;
       //if(k==85) printf("%f %6.20f %6.20f %6.20f\n",s, fus1, fus2, deg);
       }
}

void evolution(void)
{
  int k;
  double max,rel,phi,z,s,ds,N,Nout,Jout,Jin,phio,cum,st;

   max=0;phi=0;N=0;Nout=0;Jout=0;Jin=0;No=0;phio=0;cum=0;

   for(k=0;k<kmax;k++){

        p[k]+=dt*H[k];

        rel=H[k]/p[k];
        max+=sqrt(rel*rel);
        if(p[k]*p[k]>100000) {printf("problem!!"); break;};
    }

    p[kmax]=extrapole_bound();

    for(k=0;k<kmax;k++){
         z=dz*((double)k+0.5);
         s=exp(z)-1.0;
         ds=exp(z)*dz;
         phi+=p[k]*s*ds;
         N+=p[k]*ds;
         if(s>smin) {No+=p[k]*ds;phio+=p[k]*s*ds;}
         Nout+=kd(s)*p[k]*ds;
         Jout+=kd(s)*s*p[k]*ds-vout(s)*p[k]*ds;
         Jin+=A(s,t)*s*ds+vins(s,t)*p[k]*ds;

    }
    for(k=0;k<kmax;k++){
         z=dz*((double)k+0.5);
         s=exp(z)-1.0;
         ds=exp(z)*dz;
         cum+=p[k]*ds;
         if(cum/N>0.95) {st=s;k=kmax;}
    }
    Nt[t]=N;phit[t]=phi;Ntt[t]=No;phitt[t]=phio;sc[t]=st;
    if(max<0.000001) {printf("end \n"); end=1.0;};
    printf("%d  %f phi %f N %f Nout %f Jout %f Jin %f\n",t,max,phi,N,Nout,Jout,Jin);
}

void save(int m){ 

 int k,l;
 double z,s,s1,z1;

          if(m>999)     sprintf(data,"n3%d.dat",m);
  else{   if(m>99)      sprintf(data,"n30%d.dat",m);
  else{   if(m>9)       sprintf(data,"n300%d.dat",m);
  else                   sprintf(data,"n3000%d.dat",m);}}
 
  file=fopen(data,"w");
  for(k=0;k<kmax+1;k++){
       z=dz*((double)k+0.5);
       s=exp(z)-1.0;
       fprintf(file,"%6.10f %6.10f \n",s,p[k]);}
  fclose(file);

}

void save_glob(void)
{
  int k;
  double a,b;

  file=fopen("N3.dat","w");
  for(k=0;k<t;k++){
       fprintf(file,"%f %6.10f \n",(double)k,Nt[k]);}
  fclose(file);

   file=fopen("N3o.dat","w");
  for(k=0;k<t;k++){
       fprintf(file,"%f %6.10f \n",(double)k,Ntt[k]);}
  fclose(file);

  file=fopen("phi3.dat","w");
  for(k=0;k<t;k++){
       fprintf(file,"%f %6.10f \n",(double)k,phit[k]);}
  fclose(file);

  file=fopen("phi3o.dat","w");
  for(k=0;k<t;k++){
       fprintf(file,"%f %6.10f \n",(double)k,phitt[k]);}
  fclose(file);

  file=fopen("sc.dat","w");
  for(k=0;k<t;k++){
       fprintf(file,"%f %6.10f \n",(double)k,sc[k]);}
  fclose(file);
}

double  K(double s1, double s2)
{ double out;
  out=(0.6)*(pow(((s1*s2)),-0.4));
// (exp(-s2/6)+exp(-s1/6));
// (pow(((s1*s2)),-0.5)); 
 return out;
}
double  A(double s, int t)
{ double out,tr;
   tr=(double)t;
   out=6.0*theta(t,0)*exp(-(s)/5);
 return out;
}

double  kd(double s)
{ double out;
   out=0.04;
// (pow(s,2.0))*(1/(s+200));
// *s;
// *(s/(s+1));
 return out;
}
double  vins(double s, int t)
{ double out,tr;
 tr=(double)t;
 out=(0.0)*theta(t,0);
 return out;
}
double  vout(double s)
{ double out;
   out=-0.0*((pow(s,2.0))/(s+180));
 return out;
}
double  Kf(double s1, double s2)
{double out;
out=(0.1)*(exp(-s2/2)+exp(-s1/2));
 return out;
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

