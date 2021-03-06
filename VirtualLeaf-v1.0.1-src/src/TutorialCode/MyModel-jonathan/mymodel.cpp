/*
 *
 *  This file is part of the Virtual Leaf.
 *
 *  The Virtual Leaf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The Virtual Leaf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the Virtual Leaf.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright 2010 Roeland Merks.
 *
 */

#include <QObject>
#include <QtGui>
#include <fstream>

#include "simplugin.h"

#include "parameter.h"

#include "wallbase.h"
#include "cellbase.h"
#include "mymodel.h"
#include "mesh.h"
#include "cell.h"
#include "vector.h"

#include "node.h"

#include "flux_function.h"
#include "far_mem_5.h"
 
#include "math.h"
#include "pi.h"
#include "random.h"





#define X  1

#define Y 1

# define V 1

#define Z 1e+3

#define Threshold 0.24

#define src 0.5

#define src2 1e-10

#define grate 12


FILE *file;

char data[1000];


static const std::string _module_id("$Id: mymodel.cpp,v 6bcb69712a0e 2010/11/24 17:02:13 roeland $");

QString Mymodel::ModelID(void) {
    // specify the name of your model here
    return QString( "my model" );
}

// return the number of chemicals your model uses
int Mymodel::NChem(void) { return 2; }

// To be executed after cell division
void Mymodel::OnDivide(ParentInfo *parent_info, CellBase *daughter1, CellBase *daughter2) {
    // rules to be executed after cell division go here
    // (e.g., cell differentiation rules)
    
    
    double A=daughter1->Chemical(0)+daughter2->Chemical(0);
    double P=daughter1->Chemical(1)+daughter2->Chemical(1);
    
    daughter1->SetChemical(0, A/4);
    daughter2->SetChemical(0, A/4);
    
    daughter1->SetChemical(1,P/4);
    daughter2->SetChemical(1, P/4);
/**
    QList<WallBase *> walls;
    foreach(WallBase *w, walls) {
        w->setTransporter(daughter1, 1, 0.);
    }
    **/
    /**
     if (!daughter1->AtBoundaryP()&& !daughter2->AtBoundaryP())
     {daughter1->SetTransporters(1,0);
     daughter2->SetTransporters(1,0);
     }
     else  if (daughter1->AtBoundaryP()&& daughter2->AtBoundaryP())
     {
     daughter1->SetTransporters(1,0);
     daughter2->SetTransporters(1,0);
     }
     **/
    
    
    /**if (daughter1->Index()==19)
     {
     daughter1->SetCellType(1);
     daughter2->SetCellType(1);
     }
     else if (daughter2->Index()==19)
     {
     daughter1->SetCellType(1);
     daughter2->SetCellType(1);
     }**/
    /**if (parent_info->Area()>20)
     {
     daughter1->SetCellType(1);
     }**/
    
    
    if (daughter1->CellType()==1)
    {
        daughter1->SetCellType(1);
        daughter2->SetCellType(1);
    }
    else if (daughter2->CellType()==1 )
    {
        daughter2->SetCellType(1);
        daughter1->SetCellType(1);
    }
    /**
     if (daughter1->CellType()==3)
     {
     if(!daughter1->AtBoundaryP()) {daughter1->SetCellType(2);}
     else {daughter1->SetCellType(3);}
     }
     
     
     else if (daughter2->CellType()==3)
     {
     if(!daughter2->AtBoundaryP()) {daughter2->SetCellType(2);}
     else {daughter2->SetCellType(3);}
     }
     **/
    /**    if (daughter1->CellType()==3 || daughter2->CellType()==3 )
     {
     if(daughter1->AtBoundaryP() && daughter2->AtBoundaryP()){
     daughter1->SetCellType(3);
     daughter2->SetCellType(3);
     }
     else if (daughter1->AtBoundaryP() && !daughter2->AtBoundaryP()) {daughter1->SetCellType(3);daughter2->SetCellType(2);}
     else if (!daughter1->AtBoundaryP() && daughter2->AtBoundaryP()) {daughter1->SetCellType(2);daughter2->SetCellType(3);}
     else if (!daughter1->AtBoundaryP() && !daughter2->AtBoundaryP()) {daughter1->SetCellType(2);daughter2->SetCellType(2);}
     }
     **/
    
    /** else if (daughter2->CellType()==3 )
     {
     if(daughter1->AtBoundaryP() && daughter2->AtBoundaryP()){
     daughter2->SetCellType(3);
     daughter1->SetCellType(3);
     }
     else if (daughter2->AtBoundaryP() && !daughter1->AtBoundaryP()) {daughter2->SetCellType(3);daughter1->SetCellType(2);}
     else if (!daughter2->AtBoundaryP() && daughter1->AtBoundaryP()) {daughter2->SetCellType(2);daughter1->SetCellType(3);}
     else if (!daughter2->AtBoundaryP() && !daughter1->AtBoundaryP()) {daughter2->SetCellType(2);daughter1->SetCellType(2);}
     }
     **/
    
    //if (daughter1->Chemical(1)>=500 && daughter2->Chemical(1)>=500 ) {daughter1->SetCellType(2); daughter2->SetCellType(2);}
    //if (daughter2->Chemical(1)>=500 ) {daughter2->SetCellType(2);}
    
    /**if (daughter1->CellType()==1 || daughter2->CellType()==1 )
     {
     if (qrand()%2)
     {
     daughter1->SetNOD(5);
     //daughter2->SetNOD(5);
     }
     else {
     daughter2->SetNOD(5);
     //daughter2->SetNOD(5);
     }
     }
     
     **/
    
    if (daughter1->CellType()==3 || daughter2->CellType()==3) {
        
        // if both cells are at the tissue perimeter, choose at random
        if (daughter1->AtBoundaryP() && daughter2->AtBoundaryP()) {
            
            if (qrand()%2){
                daughter1->SetCellType(3);
                daughter2->SetCellType(2);
            } else
            {
                daughter1->SetCellType(2);
                daughter2->SetCellType(3);
            }
        } else {
            // otherwise choose the one that is still at the perimeter
            if (daughter1->AtBoundaryP()) {
                daughter1->SetCellType(3);
                daughter2->SetCellType(2);
            } else {
                daughter1->SetCellType(2);
                daughter2->SetCellType(3);
            }
        }
    }
    
    
    if (daughter1->Stiffness()==X && daughter2->Stiffness()!=0)
    {
        daughter1->SetStiffness(X);
        daughter2->SetStiffness(X);
    }
    else if (daughter1->Stiffness()!=0 && daughter2->Stiffness()==X)
    {
        daughter1->SetStiffness(X);
        daughter2->SetStiffness(X);
    }
    
    if (daughter1->Stiffness()==Y)
    {
        daughter1->SetStiffness(Y);
        daughter2->SetStiffness(Y);
    }
    else if (daughter2->Stiffness()==Y)
    {
        daughter1->SetStiffness(Y);
        daughter2->SetStiffness(Y);
    }
    
    
    if (daughter1->Stiffness()==V)
    {
        daughter1->SetStiffness(V);
        daughter2->SetStiffness(V);
    }
    else if (daughter2->Stiffness()==V)
    {
        daughter1->SetStiffness(V);
        daughter2->SetStiffness(V);
    }
    
    
    if (daughter1->Stiffness()==Z && daughter2->Stiffness()==0)
    {
        daughter1->SetStiffness(Z);
        daughter2->SetStiffness(Z);
    }
    else if (daughter1->Stiffness()==0 && daughter2->Stiffness()==Z)
    {
        daughter1->SetStiffness(Z);
        daughter2->SetStiffness(Z);
    }
    
    if (daughter1->Stiffness()==X||daughter2->Stiffness()==0){
        daughter1->SetStiffness(X);
        daughter2->SetStiffness(X);
    }
    
    else if (daughter1->Stiffness()==0||daughter2->Stiffness()==X){
        daughter1->SetStiffness(X);
        daughter2->SetStiffness(X);
    }
    
    //if (daughter1->AtBoundaryP() && daughter1->Stiffness()!=Z) {daughter1->SetCellType(2);daughter2->SetCellType(0);}
    //else if (daughter2->AtBoundaryP() && daughter2->Stiffness()!=Z) {daughter2->SetCellType(2);daughter1->SetCellType(0);}
    
    /***else {
     daughter1->SetStiffness(0.00001);
     daughter2->SetStiffness(0.00001);
     }***/
    
    /***if (daughter1->CellType()==1&&daughter2->CellType()=!1)
     {
     daughter1->SetCellType(1);
     daughter2->SetCellType(1);
     }
     else if (daughter1->Stiffness()==0&&daughter2->CellType()==1)
     {
     daughter1->SetCellType(1);
     daughter2->SetCellType(1);
     }
     
     else {
     daughter1->SetCellType(1);
     daughter2->SetCellType(1);
     }***/
    
    
    
}

void Mymodel::SetCellColor(CellBase *c, QColor *color) {
    // add cell coloring rules here
   double colour=(c->Chemical(0))/(c->Area());
    // double green=c->CellType()==3;
    //  double red=c->CellType()==1;
    //  double green=(c->Chemical(0))/(1.+(c->Chemical(0)));
    
    //  double blue=1*(c->Chemical(0))/(1.+(c->Chemical(0)));
    
    //double yellow=c->CellType()==5;
    //double a=1.0;
    // colour = c->Chemical(0) / (1.0 + c->Chemical(0));
    //float blue = (colour < 0.0) ? 0.0 : (colour > 1.0) ? 1.0 : colour;
    
    //  color->setRgbF(0,1.,0);
    
    //color->setRgbF(0,0.8, 0);
    
    
    if(par->k2==1)
        
    {color->setHsvF((colour/(1+colour)), 1,1);}
    else if(par->k1==1) {
        
        color->setNamedColor("lightgreen");
        if(c->Stiffness()==Z){color->setNamedColor("darkgrey");}
        if(c->CellType()==1){color->setNamedColor("darkgreen");}
    //    else {color->setHsvF((colour/(1+colour)), 1,1); }
     //    if(c->CellType()==4){color->setNamedColor("blue");}
//      if(c->CellType()==3){color->setNamedColor("pink");}
    }
    
}

void Mymodel::CellHouseKeeping(CellBase *c) {
    // add cell behavioral rules here
    double orientation = Pi*RANDOM();
    Vector axis(sin(orientation), cos(orientation),0.);
    
    
    Vector long_axis;
    Vector shrtaxis;
    double width;
    double shortwidth;
   c->Length(&long_axis, &width);
 //  c->CalcLength(&shrtaxis, &shortwidth);
    
    //Vector short_axis=long_axis.Perp2D();
    
  /**  double long_length=((long_axis).SqrNorm());
      double short_length=((shrtaxis).SqrNorm());
    
    if(long_length>short_length){c->SetCellType(4);}**/
    
    
    
    //  Vector vec_flux = -ReduceCellAndWalls<Vector>( PINdir );
    
    //
    
    //printf("Hello\n");
    
    //if (CellBase::NCells()==4)      // I ADDED THIS IN THE LAST MODEIFICATION : CHECK IT !!!!!
    // first cell expands unconditionally
    //par->lambda_length=10000;
    //else
    
    //if (c->CellType()==0) {
    //        par->lambda_length=100;
    //    }
    
    //if (c->CellType()==1) {
    //        par->lambda_length=200;
    //    }
    
    //if (c->AtBoundaryP()) {
    ////par->lambda_length=200;
    //    }
    
    //else {
    
    //c->SetCellType(0);        }
    
    
    
    
    //par->outlinewidth=2;
    par->yielding_threshold=20;
    //  par->lambda_length=1000;
  //  par->rel_perimeter_stiffness=24;
  //  par->cell_expansion_rate=1;
   // par->source=0.24;
    //par->rel_cell_div_threshold=2;
    //par->energy_threshold=1000;
    //par->morphogen_div_threshold=0;
    //par->morphogen_expansion_threshold=0;
    //par->collapse_node_threshold=0;
    //par->auxin_dependant_growth=false;
    //par->mc_cell_stepsize=0.2;
    //  par->cell_div_expansion_rate=2;
    
    par->kr=0.0015;
 //  par->D[0]=0;
    par->rho0=12;
 //   par->mu=1;
    par->nu=1;
    par->i1=1;
    
    //if (c->CellType()==3) {par->D[0]=2;}
    //else {par->D[0]=0.13;}

    //    par->c0=3;
    
    //  par->rd_dt=1;
    
  //  par->outlinewidth=2;
    //    par->maxt=1e+20;
 
    //   par->cell_outline_color="black";
    
    //par->initval[1]=100;
    //par->initval[0]=1e-2;
    //par->transport=.1;
    //par->ka=1;
    
    //par->km=1e+4;
    //par->k2=0;
    
    //par->maxt=1e+20;
    //par->ode_accuracy=1e-3;
    
    //if (c->AtBoundaryP() && c->Stiffness()==Z) {par->rel_perimeter_stiffness=2;}
    //else if (c->AtBoundaryP() && c->Stiffness()!=Z){par->rel_perimeter_stiffness=2;}
    //c->SetTargetArea(1);
    //par->stiffness=1000;
    
    //c->SetStiffness(1000);
    //c->stiff;
    
    //c->par->lambda_length=1000;
    //par->rel_perimeter_stiffness=40;
    
    
    
    //c->EnlargeTargetArea(par->cell_expansion_rate);
    
    
    
    /***if (c->AtBoundaryP())
     {
     
     c->EnlargeTargetArea(1*par->cell_expansion_rate);
     if (c->Area()>2*c->BaseArea()) {
     c->Divide();                      // divide shortest principle axis after area(t+delta)=2*area(t)
     }
     }****/
    
    //else
    {
        
        //c->EnlargeTargetArea(1*par->cell_expansion_rate);  *** DEFAULT FORM USE IT !!**
        
        //c->EnlargeTargetArea(1*par->cell_expansion_rate);
        
        
        //c->EnlargeTargetArea(c->Chemical(0))*par->cell_expansion_rate);
        
        //c->EnlargeTargetArea(par->cell_expansion_rate);
        
        
        //c->Area()==c->Chemical(0)*c->Area();
        
        
        /*** if(c->Chemical(0)>50.0)
         //if(c->CellType()==1)
         {
         if (c->Area()>2*c->BaseArea())
         {
         //c->DivideOverAxis(Vector(0,1,0));
         c->Divide();
         //c->DivideOverAxis(axis);                      // divide shortest principle axis after area(t+delta)=2*area(t)
         //c->SetLambdaLength(20);
         //c->SetStiffness(200);
         
         //c->DivideOverAxis(Vector(0,1,0));   // divide along the given axis after area(t+delta)=2*area(t)
         
         //    c->DivideOverAxis(axis);         // divide along random axis after area(t+delta)=2*area(t)
         }
         }***/
        //if (c->AtBoundaryP())
        /***{
         if (c->Area()>2*c->BaseArea()) {
         
         c->Divide();
         //c->DivideOverAxis(axis);
         
         }
         }***/
        
        //else
        {
            //if (c->CellType()==2) {c->SetBaseArea(0);}
            
            
            if ( c->CellType()==1  )
                //if(c->Stiffness()!=Z)
            {
              //  c->SetTargetArea(c->TargetArea()+par->cell_expansion_rate);
                c->EnlargeTargetArea(1*par->cell_expansion_rate);
                
                if (c->Area()>2*c->BaseArea())
                {
                    //c->DivideOverAxis(Vector(1,0,0));
                    c->Divide();
                }
            }
            
            
            /**
             if ( c->AtBoundaryP() && c->Stiffness()!=Z  )
             //if(c->Stiffness()!=Z)
             {
             c->EnlargeTargetArea(1*par->cell_expansion_rate);
             
             if (c->Area()>2*c->BaseArea())
             {
             //c->DivideOverAxis(Vector(1,0,0));
             c->Divide();
             }
             }
             **/
            
            
            
            
            
            if((c->Chemical(0)/(c->Area()))<par->source && c->Stiffness()!=Z &&  c->CellType()!=1   )
                //if( c->Stiffness()!=Z && c->CellType()!=1)
            {
                //c->EnlargeTargetArea(c->Chemical(0)/(1+c->Chemical(0))*0.5*par->cell_expansion_rate);
               
                c->EnlargeTargetArea(1*par->cell_expansion_rate);
           //     c->SetTargetArea(c->TargetArea()+par->cell_expansion_rate);
                if(c->Area()>2*c->BaseArea())
                {c->Divide();}
                //c->DivideOverAxis(axis);
                
            }
            
            
            if ((c->Chemical(0)/(c->Area()))>par->source && c->Stiffness()!=Z && c->CellType()!=1 )
                
            {
                //  c->EnlargeTargetArea(3*par->cell_expansion_rate);
                c->EnlargeTargetArea(par->c0);
               // c->SetTargetArea(c->TargetArea()+par->kaux1*par->cell_expansion_rate);
                if(c->Area()>2*c->BaseArea())
                {c->Divide();}
                //c->DivideOverAxis(axis);
                
            }
            
            /**
             if ( c->Stiffness()!=Z && c->CellType()!=1 && c->CellType()!=2 )
             {
             c->EnlargeTargetArea(2*par->cell_expansion_rate);
             if(c->Area()>2*c->BaseArea())
             {c->Divide();}
             //c->DivideOverAxis(axis);
             
             }
             **/
            
            if ( c->Stiffness()==Z)
            {
                c->EnlargeTargetArea(1*par->cell_expansion_rate);
            //    c->SetTargetArea(c->TargetArea()+par->cell_expansion_rate);
                if(c->Area()>2*c->BaseArea())
                {c->Divide();}
                //c->DivideOverAxis(axis);
                
            }
            
        }
        
        //else
        //{
        //if (c->Area()>4*c->BaseArea()) {
        
        //c->Divide();
        
        //}
        //}
        
    }
    
    
    /**if (c->Chemical(0)/(c->Area())>0.1)
     {
     if (!c->AtBoundaryP())
     {c->SetCellType(1);}
     }
     **/
    // if(c->CellType()!=1&&c->Chemical(0)>Threshold)
    {
        //if(c->AtBoundaryP())
        //{c->SetStiffness(Y);}
        //if (c->CellType()==1)
        //c->SetStiffness(Y);
        //c->SetCellType(1);//dchem[0]=1;
    }
    //else {c->SetStiffness(Y);}
    
    //if (c->CellType()==1) {c->SetStiffness(Y); }
    //if (c->CellType()==2) {c->SetStiffness(U); }
    
    
    
    
    if(c->Index()==4||c->Index()==1||c->Index()==6||c->Index()==2) {c->SetStiffness(Z);}
    //if(c->Index()==5||c->Index()==1||c->Index()==6||c->Index()==2) {c->SetStiffness(Z);} //for y-division-1-step3.xml
    //else {c->SetStiffness(1e-5);}
    
    //else if (c->Index()!=4||c->Index()!=1||c->Index()!=6||c->Index()!=2||c->Index()!=19) {c->SetStiffness(0.00001);}
    
    //if  (c->Index()==0||c->Index()==3||c->Index()==5||c->Index()==7||c->Index()==8||c->Index()==9||c->Index()==10||c->Index()==11||c->Index()==12||c->Index()==13||c->Index()==14||c->Index()==15||c->Index()==16||c->Index()==17||c->Index()==18||c->Index()==19) //This is if you want Stiffness in all cells except base & source cells
    //if  (c->Index()==0||c->Index()==3||c->Index()==9||c->Index()==10||c->Index()==11||c->Index()==16||c->Index()==17||c->Index()==19)
    
    if  (c->Index()==0||c->Index()==3||c->Index()==10||c->Index()==16||c->Index()==17||c->Index()==9||c->Index()==18||c->Index()==15||c->Index()==7||c->Index()==13||c->Index()==8||c->Index()==14||c->Index()==5||c->Index()==12||c->Index()==19||c->Index()==11)
        
        //if  (c->Index()==3||c->Index()==7||c->Index()==0||c->Index()==4||c->Index()==11||c->Index()==10||c->Index()==9||c->Index()==8) //for y-division-1-step3.xml
    {
        //if (c->Chemical(0)<Threshold){c->SetStiffness(Y);}
        
        c->SetStiffness(X);
        //if (c->Chemical(0)>=Threshold){c->SetStiffness(Y);}
        //else if (c->Chemical(0)<Threshold) {c->SetStiffness(X);}
        
    }
    
    //if (c->Index()==11 ) {c->SetStiffness(Y);}
    
    //if  (c->Index()==3||c->Index()==9||c->Index()==18||c->Index()==15||c->Index()==7||c->Index()==13||c->Index()==8||c->Index()==14||c->Index()==5||c->Index()==12||c->Index()==10)
    
    //if (c->AtBoundaryP() && c->Stiffness()!=Z)
    {
        //c->SetCellType(2);
    }
    
    //    if (c->BoundaryPolP()&&c->Stiffness()!=Z&&c->CellType()!=1)
    
    //if (c->AtBoundaryP()&&c->Index()!=4&&c->Index()!=1&&c->Index()!=6&&c->Index()!=2)  //This if you want Stiffness only in Boundary cells (except base and source cells)
    {
        //   c->SetStiffness(V);
    }
    //else {c->SetCellType(0);}
    
    double D=c->CalcArea();
    double L=c->CalcLength();
    
    //if (c->Index()==7||c->Index()==70||c->Index()==105||c->Index()==100||c->Index()==75||c->Index()==51||c->Index()==54||c->Index()==26||c->Index()==82||c->Index()==13)
    
    //if (c->Index()==7||c->Index()==13||c->Index()==8)
    //   if (c->Index()==7||c->Index()==13||c->Index()==28||c->Index()==27||c->Index()==15)
    {
        //c->SetCellType(2);
        //c->MarkDead();
        //c->SetTargetArea(D);
        //c-> BaseArea()=0;
        //c->SetTargetArea(0);
        //c->SetTargetLength(L);
    }
    Node *node;
    //if (node->Index()==21){node->DeadP();}
    //if (!c->AtBoundaryP())
    //{c->SetTransporters(1,1);}
    //else if (c->AtBoundaryP())
    {
        //c->SetTransporters(1,1);
        //c->SetChemical(1,2);
        
    }
    
    
}


void Mymodel::CelltoCellTransport(Wall *w, double *dchem_c1, double *dchem_c2) {
    // add biochemical transport rules here
    /**
     {
     if (w->C1()->BoundaryPolP() && w->C1()->Stiffness()!=Z ){w->C1()->SetStiffness(100);}
     else if (w->C2()->BoundaryPolP() && w->C2()->Stiffness()!=Z){w->C2()->SetStiffness(100);}
     
     else if (!w->C2()->BoundaryPolP() && !w->C1()->BoundaryPolP()){w->C1()->SetStiffness(1); w->C2()->SetStiffness(1);}
     }
     **/
    
    //for (int c=0;c<NChem();c++)
    
    /** This was "only-auxin" part
     if(w->C1()->BoundaryPolP()||w->C2()->BoundaryPolP()) return ;
     
     
     //if(w->C1()->BoundaryPolP()||w->C2()->BoundaryPolP()||w->Index()==33||w->Index()==75||w->Index()==50||w->Index()==76||w->Index()==95||w->Index()==21||w->Index()==77) return ;
     //||w->Index()==50||w->Index()==53||w->Index()==21||w->Index()==19||w->Index()==33||w->Index()==24||w->Index()==23) return ;
     //if(w->C1()->Index()==50||w->C2()->Index()==50||w->C1()->Index()==53||w->C2()->Index()==53||w->C1()->Index()==21||w->C2()->Index()==21||w->C1()->Index()==19||w->C2()->Index()==19||w->C1()->Index()==33||w->C2()->Index()==33) return ;
     
     
     //if(w->Index()==33||w->Index()==75||w->Index()==50||w->Index()==76||w->Index()==95||w->Index()==21||w->Index()==77) return ;
     
     // No flux boundaries for all chemicals, except activator: boundary is sink
     
     double phi=pow(w->Length(),1) * (par->D[0])*(w->C2()->Chemical(0)-w->C1()->Chemical(0));
     dchem_c1[0]+=phi;
     dchem_c2[0]-=phi;
     **/
    
    
    /** if (w->C1()->BoundaryPolP() || w->C2()->BoundaryPolP()) {
     
     if (w->C1()->BoundaryPolP()) {
     dchem_c2[0] -=  w->Length() * ( par->D[0] ) * ( w->C2()->Chemical(0) );
     } else {
     dchem_c1[0] -=  w->Length() * ( par->D[0] ) * ( w->C1()->Chemical(0) );
     }
     // return;
     } **/
    
    //return;
    
    /**
     // directed transport
     // efflux from cell 1 to cell 2
     double trans12 = ( par->transport * w->Transporters1(1) *
     w->C1()->Chemical(0) / (par->ka + w->C1()->Chemical(0)) );
     
     // efflux from cell 2 to cell 1
     double trans21 = ( par->transport * w->Transporters2(1) *
     w->C2()->Chemical(0) / (par->ka + w->C2()->Chemical(0)) );
     
     dchem_c1[0] += trans21 - trans12;
     dchem_c2[0] += trans12 - trans21;
     
     **/
    
    //if (w->Index()==17 || w->Index()==20|| w->Index()==18) {w->Kill();}
    //if (w->Index()==20) {w->SetLength(0);}
    
    
 
    
    for (int c=0;c<NChem();c++)
    {
      if(w->C1()->BoundaryPolP()||w->C2()->BoundaryPolP()) return ;
      
        
  /**
      if(w->C1()->BoundaryPolP()||w->C2()->BoundaryPolP())
        {
            if (w->C1()->BoundaryPolP()){
                dchem_c1[0]=-10*w->C1()->Chemical(0);
            }
            else { dchem_c2[0]=-10*w->C2()->Chemical(0);}
            if (w->C1()->BoundaryPolP() && w->C2()->BoundaryPolP()){dchem_c1[0]=-10*w->C1()->Chemical(0);dchem_c2[0]=-10*w->C2()->Chemical(0);}
            return;
        }
        **/
        
  /**
            if(w->C1()->BoundaryPolP() )
            {
                if( w->C1()->CellType()==3)
                {dchem_c1[0]=0;}
                else {return;}
                
            }
             else if ( w->C2()->BoundaryPolP())
             {
                 if(w->C2()->CellType()==3)
                 {dchem_c2[0]=0;}
                 else {return;}
             }
        **/
        
    /**    if (w->C1()->CellType()==3 || w->C2()->CellType()==3 )
        {
            if (w->C1()->CellType()==3 ){
                dchem_c1[0]=0;
            }
            else { dchem_c2[0]=0;}
            if (w->C1()->CellType()==3  && w->C2()->CellType()==3 ){dchem_c1[0]=0;dchem_c2[0]=0;}
            return;
        }
        **/
        
      
        
     
        
        
        
        // No flux boundaries for all chemicals, except activator: boundary is sink
        
        //double delta_pin =  w->Transporters2(1)-w->Transporters1(1);
        /**
         if (w->Transporters2(1)-w->Transporters1(1)>=0) {delta_pin=w->Transporters2(1)-w->Transporters1(1);}
         else if (w->Transporters2(1)-w->Transporters1(1)<0) {delta_pin=-(w->Transporters2(1)-w->Transporters1(1));}
         **/
        
 /**
// BETTER VERSION : 9/9/15
  
  double phi=w->Length() * (par->D[0])*(w->C2()->Chemical(0)/(w->C2()->Area())-w->C1()->Chemical(0)/(w->C1()->Area()));
        
        if (w->C1()->Stiffness()!=Z && w->C2()->Stiffness()!=Z && !w->C1()->BoundaryPolP() && !w->C2()->BoundaryPolP())
        {
            
            dchem_c1[0]+=phi;
            dchem_c2[0]-=phi;
        }
        
        if (w->C1()->Stiffness()==Z || w->C2()->Stiffness()==Z )
        {
            if (w->C1()->Stiffness()==Z && w->C2()->Stiffness()!=Z){
                dchem_c1[0]=0;
                
                dchem_c2[0]+=-phi;
            }
            else if (w->C1()->Stiffness()!=Z && w->C2()->Stiffness()==Z){
                dchem_c1[0]+=-phi;
                dchem_c2[0]=0;
            }
            
            //  return;
        }
        if (w->C1()->Stiffness()==Z && w->C2()->Stiffness()==Z ){dchem_c1[0]=0;dchem_c2[0]=0;}
**/
        
        //-----DIFFUSION-----
 
       
  
        
        if (w->C1()->Stiffness()==Z || w->C2()->Stiffness()==Z )
        {
            if (w->C1()->Stiffness()==Z || w->C2()->Stiffness()==Z )
            {
                if (w->C1()->Stiffness()==Z){
                    dchem_c1[0]=0;
                }
                else { dchem_c2[0]=0;}
                if (w->C1()->Stiffness()==Z && w->C2()->Stiffness()==Z ){dchem_c1[0]=0;dchem_c2[0]=0;}
                return;
            }
            
            if (w->C1()->Stiffness()==Z && w->C2()->Stiffness()==Z ){dchem_c1[0]=0;dchem_c2[0]=0;}
            return;
        }
        
        double phi=pow(w->Length(),1) * (par->D[0])*(w->C2()->Chemical(0)/(w->C2()->Area())-w->C1()->Chemical(0)/(w->C1()->Area()));
        dchem_c1[0]+=phi;
        dchem_c2[0]-=phi;
    
       // else
       
        /** if (w->C1()->BoundaryPolP() || w->C2()->BoundaryPolP()) {
         
         if (w->C1()->BoundaryPolP()) {
         dchem_c2[0] -=  w->Length() * ( par->D[0] ) * ( w->C2()->Chemical(0) );
         } else {
         dchem_c1[0] -=  w->Length() * ( par->D[0] ) * ( w->C1()->Chemical(0) );
         }
         // return;
         } **/
        
        //return;
        
    }
    
    //w->setTransporters1(1,1);
    //w->setTransporters2(1,1);
    //if (w->C1()->Index()==10)
    //{w->C1()->SetChemical(0,1);}
    // directed transport
    // efflux from cell 1 to cell 2
    
 /**
    double trans12 =  par->transport * w->Transporters1(1) *
                      (w->C1()->Chemical(0)/w->C1()->Area());
    // (par->ka + w->C1()->Chemical(0)) );
    
    // efflux from cell 2 to cell 1
    double trans21 =  par->transport * w->Transporters2(1) *
                      (w->C2()->Chemical(0)/w->C2()->Area());
    /// (par->ka + w->C2()->Chemical(0)) );
    
    if (w->C1()->Stiffness()==Z || w->C2()->Stiffness()==Z  )
    {
        
        if (w->C1()->Stiffness()==Z && w->C2()->Stiffness()!=Z){
            
            //if(w->C2()->Stiffness()==Z ) {dchem_c1[0]=0;dchem_c2[0]=0;}
            //else
            {dchem_c2[0]+=-par->km * w->Transporters2(1)*(w->C2()->Chemical(0)/w->C2()->Area()) ; }
        }
        else  if (w->C1()->Stiffness()!=Z && w->C2()->Stiffness()==Z)
        {dchem_c1[0]+=-par->km * w->Transporters1(1)*(w->C1()->Chemical(0)/w->C1()->Area()) ;}
    //   return;
        
       
    }
    
   if (w->C1()->Stiffness()!=Z  && w->C2()->Stiffness()!=Z){
    
    dchem_c1[0] += trans21 - trans12;
    dchem_c2[0] += trans12 - trans21;
    }
    **/
    
    //   if (w->C1()->Chemical(0)<=w->C2()->Chemical(0)) {w->setTransporters1(1,0);}
    //  else if (w->C2()->Chemical(0)<=w->C1()->Chemical(0)) {w->setTransporters2(1,0);}
   /** if (w->Transporters1(1)<=0) {w->setTransporters1(1,0);}
    
    else if  (w->Transporters2(1)<=0) {w->setTransporters2(1,0);}**/
    return;
    
}


void Mymodel::WallDynamics(Wall *w, double *dw1, double *dw2) {
    // add biochemical networks for reactions occuring at walls here
   dw1[0] = 0.; dw2[0] = 0.;
 /**
    if (w->C2()->BoundaryPolP()) {
     {
            dw1[0]=dw2[0]=dw1[1]=dw2[1];
            return;
        }
    }
    
   else  if (w->C1()->BoundaryPolP()) {
        {
            dw1[0]=dw2[0]=dw1[1]=dw2[1];
            return;
        }
    }

   else {
    dw1[1]=1*PINflux(w->C1(), w->C2(), w);
    dw2[1]=1*PINflux(w->C2(), w->C1(), w);
   }
    **/
}


void Mymodel::CellDynamics(CellBase *c, double *dchem) {
    // add biochemical networks for intracellular reactions here
    
    double A=c->Chemical(0);
    int B=c->CellType();
    
    
    
    
    
    //int t= Mesh::getTime();
    
    /***if(c->AtBoundaryP()&&c->Stiffness()==1e-5)
     {
     c->SetStiffness(1000);
     }***/
    
    //if(c->Stiffness()==500)
    //if(c->Index()==19)
    
    
    //if (c->Stiffness()==X) {c->SetCellType(1);}
    //else if(c->Stiffness()==1e+5) {c->SetCellType(0);}
    //else {c->SetCellType(0);}
    
    
    
    //else {c->SetCellType(0);}
    
    double kd=0.0;
    //  double src=2;
    
    //double num_div= NumberOfDivisions();
    
    if ( c->Index()==11 || c->Index()==16||c->Index()==19||c->Index()==0 ) {dchem[0]=par->ka-kd*A;}
    
 //if (  c->Index()==13) {dchem[0]=src2;}

    /** if (c->CellType()==3)
 
    {
        //if(c->NumberOfDivisions()<=6)
        {dchem[0]=-src2*A; c->SetStiffness(X);}
    }
**/  //last used
    
    
    
    // if (  c->AtBoundaryP() && c->Stiffness()!=Z) {dchem[0]=src-kd*A;}
    
    //if (c->Stiffness()==Y) {c->SetCellType(1);}
    //{dchem[0] = src*((c->Area())/(c->BaseArea()))-kd*A; }
    
    //if (c->Index()==11 ) {dchem[0] = src-kd*A; }
    //else {dchem[0]=0;}
    
    //if(c->Stiffness()==Y){c->SetCellType(1);} //use this in general
    if(dchem[0]==par->ka-kd*A){c->SetCellType(1);}
//    if(dchem[0]==-src2*A ){c->SetCellType(3);}
    
    
    
    if (c->CellType()==1)
        //if (c->CellType()==1)
    {
        //if(c->NumberOfDivisions()<=6)
        {dchem[0]=par->ka-kd*A; c->SetStiffness(X);}
    }
    
 
    
    
    {
        //static ofstream pf("/home/jonathan/tutorial1_data/pin_flux.dat");
        //    pf << time << endl;
        //file =fopen("/home/jonathan/Desktop/VirtualLeaf-v1.0.1.2-src/src/TutorialCode/Tutorial1B/pin.dat", "w");
        //fprintf(file, "%f\n", A);
        //fclose(file);
        
        
    }


 //  dchem[1]=-SumFluxFromWalls(c, Mymodel::PINflux)+par->pin_prod*c->Chemical(0);  //latest Used
    
}


double Mymodel::PINflux(CellBase *this_cell, CellBase *adjacent_cell, Wall *w)
{
    double adj_auxin = adjacent_cell->Chemical(0);
    double this_auxin = this_cell->Chemical(0);
    double receptor_level=this_auxin*par->r/(par->r+this_auxin);
    //adj_auxin*par->r/(par->r+adj_auxin);
    
    double pin_atwall;
    double pin_difference=0;
    double delta;
    
    double pin_flux;
    double phi;
    
    
 
    double delta_auxin=0;

    
   // delta_auxin=this_cell->Chemical(0)-adjacent_cell->Chemical(0);
/**
   if (this_cell->CellType()==1)
   {
     //  if(adjacent_cell->CellType()!=1)
       if(this_cell->Chemical(0)-adjacent_cell->Chemical(0)<1e-2)
       {
           delta_auxin=1e-2;
           
       }
           
       else {delta_auxin=this_cell->Chemical(0)-adjacent_cell->Chemical(0);}
      // else {delta_auxin=1e-5; }
   }
   else {
       
       if(this_cell->Chemical(0)-adjacent_cell->Chemical(0)<1e-2)
       {
            delta_auxin=1e-2;
           
       }
       else { delta_auxin=this_cell->Chemical(0)-adjacent_cell->Chemical(0);}
           
       
       
   }
    **/
  
    
//    double sum_auxin=this_cell->Chemical(0)/(this_cell->Area())+adjacent_cell->Chemical(0)/(adjacent_cell->Area());
    
    //if (this_cell->Chemical(0)<0 && adjacent_cell->Chemical(0)>0 )
    
    //if (this_cell->Chemical(0)>adjacent_cell->Chemical(0) )
    {
        //delta_auxin=1;
        //adjacent_cell->Chemical(0)-0;
    }
    //else if (this_cell->Chemical(0)<adjacent_cell->Chemical(0) ) {delta_auxin=0;}
    /**
     else if (adjacent_cell->Chemical(0)<0 && this_cell->Chemical(0)>0 )
     {
     delta_auxin=1;
     //this_cell->Chemical(0)-0;
     }
     **/
    /**
     else if (adjacent_cell->Chemical(0)>0 && this_cell->Chemical(0)>0 )
     {
     delta_auxin=(this_cell->Chemical(0))/(adjacent_cell->Chemical(0));
     }**/
    
    
    
    if (w->C1()==this_cell) pin_atwall=w->Transporters1(1);
    
  if(this_cell->Chemical(0)-adjacent_cell->Chemical(0)>=1e-2)
  {
       delta_auxin=this_cell->Chemical(0)-adjacent_cell->Chemical(0);
      
  }
  else {delta_auxin=1e-2;}
    
    
        //  delta_auxin=this_cell->Chemical(0)-adjacent_cell->Chemical(0);
          
    if (this_cell->Stiffness()==Z) {
        pin_flux=0;
    }
    else{
        
        if(adjacent_cell->Stiffness()==Z)
        {
            pin_flux=pin_flux=(par->Pi_tot)*((delta_auxin))*(this_cell->Chemical(1));
        }
        
        else {    //use

     //   if (this_cell->Chemical(0)/(this_cell->Area())>=adjacent_cell->Chemical(0)/(adjacent_cell->Area()))  //use
    //    if(delta_auxin>1e-10)
        {
            pin_flux=(par->Pi_tot)*((delta_auxin))*(this_cell->Chemical(1));
            
        }
        //  else if (this_cell->Chemical(0)/(this_cell->Area())<adjacent_cell->Chemical(0)/(adjacent_cell->Area())) //use
    /**    else if(delta_auxin<=1e-10)
        {
            
                pin_flux=-par->km*w->Transporters1(1);
            
         }
            **/
    
      
        
    }
        
  }

    
 

    return pin_flux;

}


/**
 double sum=0.;
 for (list<Wall *>::const_iterator w=walls.begin();
 w!=walls.end();
 w++) {
 sum += (*w)->getTransporter(this, ch);
 
 }
 return sum;**/

Q_EXPORT_PLUGIN2(mymodel, Mymodel)



