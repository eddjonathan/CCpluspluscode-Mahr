/*
 *
 *  This file is part of the Virtual Leaf.
 *
 *  VirtualLeaf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  VirtualLeaf is distributed in the hope that it will be useful,
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

#include <string>
#include <sstream>
#include "canvas.h"
#ifdef QTGRAPHICS
#include <qstring.h>
#include <QGraphicsSimpleTextItem>
#endif
#include "node.h" 
#include "cell.h"
#include "mesh.h"
#include "random.h"
#include "parameter.h"
#include "sqr.h"
#include "pi.h"
#include "warning.h"


#include "matrix.h"
#include "qcanvasarrow.h"
#include "nodeitem.h"

static const std::string _module_id("$Id: node.cpp,v 15d600891648 2010/06/24 13:22:58 michael $");

extern Parameter par;

int Node::nnodes=0;
double Node::target_length=1;

ostream &Edge::print(ostream &os) const {
  return os << "{ " << first->Index() << ", " << second->Index() << " }";
}

ostream &Neighbor::print(ostream &os) const {

  os << " {" << cell->Index() << " " << nb1->Index() << " " << nb2->Index() << "}";
  return os;
}

ostream &operator<<(ostream &os, const Neighbor &n) {
  n.print(os);
  return os;
}


Node::Node(void) : Vector()
{
  index=(nnodes++);
  node_set =0;
  fixed=false;
  boundary=false;
  sam=false;
  dead=false;
}

Node::Node(int ind) : Vector()
{
  node_set =0;
  index=ind;
  fixed=false;
  boundary=false;
  sam=false;
  dead=false;
}

Node::Node(const Vector &src) : Vector(src)
{
  node_set = 0;
  index=(nnodes++);
  fixed=false;
  boundary=false;
  sam=false;
  dead = false;
}

Node::Node(double x,double y, double z) : Vector (x,y,z)
{
  node_set = 0;
  index=(nnodes++);
  fixed=false;
  boundary=false;
  sam=false;
  dead = false;
}

Node::Node(const Node &src) : Vector(src)
{
  node_set=0;
  owners=src.owners;
  m=src.m;
  index=src.index;
  fixed = src.fixed;
  boundary = src.boundary;
  sam=src.sam;
  dead = src.dead;
}


Cell &Node::getCell(const Neighbor &i)
{
  return *i.getCell(); // use accessor!
}


ostream &Node::print(ostream &os) const {

    Matrix rotmat;    // INCLUSION of ROTATION MATRIX ****
    rotmat.Rot2D(90);
    
 
    
    double loc_area_plus_norm=0;
    double loc_area_minus_norm=0;
   
    double diff_node2=0;


  //  list<Neighbor>::const_iterator i = owners.begin();  //Use this in combination with "i->cell->Index() to get cell index
    
    
  if (!dead)
    os << "Node ";
  else
    os << "DEAD NODE ";

  os  << index << "[ {" << x << ", " << y << ", " << z << "}: {";

  os << "Neighbors = { ";

  for (list<Neighbor>::const_iterator i =  owners.begin(); i!=owners.end(); i++) {
      
      
      Vector loc_area_plus = rotmat*(*i->nb2-*this);
      Vector loc_area_minus = rotmat*(*i->nb1-*this);
      
      loc_area_plus_norm=loc_area_plus.Norm();
      loc_area_minus_norm=loc_area_minus.Norm();
      
       diff_node2+= -(i->cell->Area()-i->cell->target_area)*(loc_area_plus_norm-loc_area_minus_norm);
      
 /**     loc_area_plus_x= (rotmat*((i->nb1)->x-x)).Norm();
      loc_area_plus_y= (rotmat*((i->nb1)->y-y)).Norm();
      
      loc_area_minus_x= (rotmat*((i->nb2)->x-x)).Norm();
      loc_area_minus_y= (rotmat*((i->nb2)->y-y)).Norm();**/
      
     //   diff_node2+= -(i->cell->Area()-i->cell->target_area)*(loc_area_plus-loc_area_minus);
      //  loc_area_plus.Norm();
   //   loc_area_minus= (rotmat*(*(*nminus)-*(*i))).Norm();
  
 // os << " {" << i->cell->Index() << " " << i->nb1->Index() << " " << i->nb2->Index() << "} ";
  }
    os << " {" << this->Index() << " " << diff_node2<< "} ";
  os << " } " << endl;

  return os;
}


#ifdef QTGRAPHICS
void Node::DrawIndex(QGraphicsScene *c) const {
    
    Matrix rotmat;    // INCLUSION of ROTATION MATRIX ****
    rotmat.Rot2D(90);
    
    
 //   QVector<qreal> diff_vector_x;
 //   QVector<qreal> diff_vector_y;
 //   double diff_node2_x=0;
  //  double diff_node2_y=0;
    
    
    Vector long_axis;
    double width;
    
    double loc_area_plus_norm=0;
    double loc_area_minus_norm=0;
    double length_plus_norm =0;
    double length_minus_norm =0;
    double diff_node2_norm=0;
    
    Vector diff_node2;
 
    
    for (list<Neighbor>::const_iterator i =  owners.begin(); i!=owners.end(); i++)
    {
        Vector loc_area_plus = rotmat*(*i->nb2-*this);
        Vector loc_area_minus = rotmat*(*i->nb1-*this);
        
        Vector length_plus = (*i->nb2-*this);
        Vector length_minus = (*i->nb1-*this);
        
        length_plus_norm = length_plus.Norm();
        length_minus_norm = length_minus.Norm();
       // i->cell->Length(&long_axis, &width);
        
        loc_area_plus_norm=loc_area_plus.Norm();
        loc_area_minus_norm=loc_area_minus.Norm();
        
           diff_node2_norm+= -(i->cell->Area()-i->cell->target_area)*(loc_area_plus_norm-loc_area_minus_norm);
        
       
      //if(i->cell->Stiffness()==2e+3)
        if ((find_if (owners.begin(), owners.end(),
                      bind2nd(mem_fun_ref(&Neighbor::CellStiffnessEquals),1e+3))) != owners.end())
      {diff_node2=0;}
        else
            //if(i->cell->Stiffness()!=2e+3)
        {        diff_node2+= -(i->cell->Area()-i->cell->target_area)*(loc_area_plus-loc_area_minus)+
                              par.lambda_length*((length_plus)/(length_plus_norm)+ (length_minus)/(length_minus_norm))/2;
       }

    }
    list<Node *>::const_iterator nb;
    list<Node *>::const_iterator i=nodes.begin();


  //return DrawOwners(c);
  stringstream text;
  text << index;
    Vector from;
    Vector to;
   // Node &n=getNode();
/**    list<Neighbor>::const_iterator j =  owners.begin();
    if (j!=owners.end())
    {
        
        for (j=0; j<jmax; j++) {
            
        }
    }
    if (j==owners.end())
    {
        j==owners.begin();
    }**/
    
    
  
 if (!this->BoundaryP()){
  from = *this-par.kr*diff_node2;
  to = *this+par.kr*diff_node2;
    }
    
 else if (this->BoundaryP())
    {
         from = *this;
        to = *this;
    }
    
   //     Node &no(*(*j));
   
     QGraphicsArrowItem *arrow = new QGraphicsArrowItem(0,c);
 // if (j->getCell()->CellType()==1)
    if ((find_if (owners.begin(), owners.end(),
                                     bind2nd(mem_fun_ref(&Neighbor::CellTypeEquals),1))) != owners.end())
    {
   // if (*this->x-to.x)
        arrow->setPen( QPen(QColor(par.arrowcolor),par.eps));
    
    }
  else { arrow->setPen( QPen(QColor(par.textcolor),par.eps));}
    arrow->setZValue(2);
    
//     QGraphicsSimpleTextItem *number = new QGraphicsSimpleTextItem ( QString (text.str().c_str()), 0, c );
//  QGraphicsSimpleTextItem *number = new QGraphicsSimpleTextItem ( QString("%1(%2)").arg((this)->Index()).arg(diff_node2), 0, c );
  //  Vector offs=Cell::Offset();
    
    
    arrow->setLine( ( (from.x)),
                   ( (from.y) ),
                   ( (to.x) ),
                   ( (to.y) ) );
    arrow->setZValue(10);
    arrow->show();
/**
 number->setFont( QFont( "Helvetica", par.nodenumsize, QFont::Bold) );
  number->setPen( QPen (par.textcolor) );
  number->setZValue(20);
  number->show();
  Vector offs=Cell::Offset();
  number -> setPos(
		   ((offs.x+x)*Cell::Factor()),
		   ((offs.y+y)*Cell::Factor()) );**/
    
    
    

}

void Node::DrawOwners(QGraphicsScene *c) const {

  stringstream text;
  text << owners.size();

  QGraphicsSimpleTextItem *number = new QGraphicsSimpleTextItem ( QString (text.str().c_str()), 0, c );
  number->setFont( QFont( "Helvetica", par.nodenumsize, QFont::Bold) );
  number->setPen( QPen(par.textcolor) );
  number->setZValue(20);
  number->show();
  Vector offs=Cell::Offset();

  number ->setPos(((offs.x+x)*Cell::Factor()),
		  ((offs.y+y)*Cell::Factor()) );
}


QVector<qreal> Node::NeighbourAngles(void)
{
  QVector<qreal> angles;
  for (list<Neighbor>::iterator i=owners.begin(); i!=owners.end(); i++) {
    Vector v1 = (*this - *i->nb1).Normalised();
    Vector v2 = (*this - *i->nb2).Normalised();	

    double angle = v1.SignedAngle(v2);
    if (angle<0) {
      //cerr << "Changing sign of angle " << angle << endl;
      angle = angle + 2*Pi;
    }
    angles.push_back(angle);

    //cerr << "Cell " << i->cell->Index() << ": " <<  v1 << " and " << v2 
    //     << ": angle = " << angles.back() << ", " << v1.Angle(v2) << endl;

  }

  double sum=0.;
  for (QVector<qreal>::iterator i=angles.begin(); i!=angles.end(); i++) {
    sum+=*i;
  }
  //cerr << "Angle sum = " << sum << endl;
  // Check if the summed angle is different from 2 Pi 
  if (fabs(sum-(2*Pi))>0.0001) {

    MyWarning::warning("sum = %f",sum);
  }
  return angles;
}

#endif

ostream &operator<<(ostream &os, const Node &n) {
  n.print(os);
  return os;
}

/* finis */
