/*
 *
 *  $Id: cell.h,v 15d600891648 2010/06/24 13:22:58 michael $
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

#ifndef _CELL_H_
#define _CELL_H_

#include <list>
#include <vector>
#include <iostream>
#include <QString>
#include "vector.h"
#include "parameter.h"
#include "wall.h"
#include "warning.h"
#include "cellbase.h"
#include "cell.h"
#include "node.h"
#include "nodeitem.h"

#include <QGraphicsScene>
#include <qcolor.h>
#include <QObject>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <QMouseEvent>

//class Mytestx;

class Cell : public CellBase 
{

  Q_OBJECT
    friend class Mesh;
  friend class FigureEditor;

 public:
  Cell(double x, double y, double z = 0.);
  Cell(void);
  Cell(const Cell &src);
  Cell operator=(const Cell &src);
  bool Cmp(Cell*) const;
  bool Eq(Cell*) const;

  inline bool IndexEquals(int i) { return i == index; }

  static void SetMagnification(const double &magn) {
    factor=magn;
  }
  static Vector Offset(void) {
    Vector offs;
    offs.x=offset[0];
    offs.y=offset[1];
    return offs;
  }

  static void Translate(const double &tx,const double &ty) {
    offset[0]+=tx;
    offset[1]+=ty;
  }

  inline static double Factor(void) {
    return factor;
  }
  static void setOffset(double ox, double oy) {
    offset[0]=ox;
    offset[1]=oy;
  }
  static double Magnification(void) {
    return factor;
  }

  static double Scale(const double scale) {
    factor*=scale;
    return factor;
  }

  void DivideOverAxis(Vector axis); // divide cell over axis

  // divide over the line (if line and cell intersect)
  bool DivideOverGivenLine(const Vector v1, const Vector v2, bool wall_fixed = false, NodeSet *node_set = 0);

  void Divide(void) { // Divide cell over short axis

    Vector long_axis;
      Vector shrtaxis;
    Length(&long_axis);
    Shortaxis(&shrtaxis);
    DivideOverAxis(long_axis.Perp2D());
    //  DivideOverAxis(long_axis);
  }

  //void CheckForGFDrivenDivision(void);
  inline int NNodes(void) const { return nodes.size(); }

  void Move(Vector T);
  void Move(double dx, double dy, double dz=0) {
    Move( Vector (dx, dy, dz) );
  }

  double Displace(double dx, double dy, double dh);
  void Displace(void);
  double Energy(void) const;
  bool SelfIntersect(void);
  bool MoveSelfIntersectsP(Node *nid, Vector new_pos);
  bool IntersectsWithLineP(const Vector v1, const Vector v2);
    
   

  void XMLAdd(xmlNodePtr cells_node) const;

  void ConstructWalls(void);
  void Flux(double *flux, double *D);

  void OnClick(QMouseEvent *e);
  inline Mesh& getMesh(void) const { return *m; }
  double MeanArea(void);

  void Apoptose(void); // Cell kills itself
  list<Wall *>::iterator RemoveWall( Wall *w );
  void AddWall( Wall *w );

  void Draw(QGraphicsScene *c, QString tooltip = QString::Null());

  // Draw a text in the cell's center
  void DrawText(QGraphicsScene *c, const QString &text) const;
  void DrawIndex(QGraphicsScene *c) const;
  void DrawCenter(QGraphicsScene *c) const;
  void DrawNodes(QGraphicsScene *c) const;

  void DrawAxis(QGraphicsScene *c) const;
  void DrawStrain(QGraphicsScene *c) ;
  void DrawFluxes(QGraphicsScene *c, double arrowsize = 1.);
  void DrawWalls(QGraphicsScene *c) const;
  void DrawValence(QGraphicsScene *c) const;
  void EmitValues(double t);
    
    template<class Op1, class Op2> void LoopNodes2(Op1 f, Op2 &g) {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        {
            for (list<Node *>::const_iterator i=nodes.begin();
                 i!=nodes.end();
                 i++) {
                f(**i,g);
            }
        }
        
    }

    

    template< class Op> double LoopNodeForcexx(Op f)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        list<Node *>::iterator n;
        {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
           
            
            sum=f(**n);
        }
        return sum;
        
        
    }
    
    
    template< class Op> double LoopForcexx(Op f)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=fabs(f(**n));
        }
        return sum;
        
        
    }
    
    template< class Op> double LoopForceyy(Op f)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=fabs(f(**n));
        }
        return sum;
        
        
    }
    
    template< class Op1, class Op2> double LoopNodesxxcentx(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
        Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**n)*((g(**n)-(centroid.x)));
          //  sum+=f(**n)*(centroid.x-g(**n));
        }
        return sum;
        
        
    }
    

    template< class Op1, class Op2> double LoopNodesxxcentxplus1(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**i_plus_1)*((g(**i_plus_1))-(centroid.x));
         //   sum+=f(**i_plus_1)*(centroid.x-g(**i_plus_1));
        }
        return sum;
        
        
    }

    template< class Op1, class Op2> double LoopNodesxxcentxplus1crossx(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**n)*((g(**i_plus_1))-(centroid.x));
          //  sum+=f(**n)*(centroid.x-g(**i_plus_1));
        }
        return sum;
        
        
    }
    
    template< class Op1, class Op2> double LoopNodesxxcentxplus1crossf(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**i_plus_1)*((g(**n))-(centroid.x));
          //    sum+=f(**i_plus_1)*(centroid.x-g(**n));
        }
        return sum;
        
        
    }


    
    template< class Op1, class Op2> double LoopNodesxxcenty(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**n)*((g(**n))-(centroid.y));
         //   sum+=f(**n)*(centroid.y-g(**n));
        }
        return sum;
        
        
    }
    
    
    template< class Op1, class Op2> double LoopNodesxxcentyplus1(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**i_plus_1)*((g(**i_plus_1))-(centroid.y));
          //  sum+=f(**i_plus_1)*(centroid.y-g(**i_plus_1));
        }
        return sum;
        
        
    }


    template< class Op1, class Op2> double LoopNodesxxcentyplus1crossy(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**n)*((g(**i_plus_1))-(centroid.y));
         //   sum+=f(**n)*(centroid.y-g(**i_plus_1));
        }
        return sum;
        
        
    }
    
    
    template< class Op1, class Op2> double LoopNodesxxcentyplus1crossf(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        Vector node;
        
        for (list<Node *>::iterator n=nodes.begin();n!=nodes.end();n++) {
            //  Node *n=*i;
            Vector centroid = this->Centroid();
            list<Node *>::const_iterator i_plus_1=n; i_plus_1++;
            if (i_plus_1==nodes.end())
                i_plus_1=nodes.begin();
            
            sum+=f(**i_plus_1)*((g(**n))-(centroid.y));
          //   sum+=f(**i_plus_1)*(centroid.y-g(**n));
        }
        return sum;
        
        
    }
    

    
    template< class Op1, class Op2> double LoopNodesyy(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        
        for (list<Node *>::const_iterator i=nodes.begin();
             i!=nodes.end();
             i++) {
            Vector centroid = this->Centroid();
             sum+=f(**i)*((g(**i))-(centroid.x));
          //  sum+=f(**i)*(centroid.x-g(**i));
        }
        return sum;
        
        
    }

    template< class Op1, class Op2> double LoopNodesxy(Op1 f, Op2 g)
    {
        //for (vector<Cell *>::const_iterator w=cells.begin();
        //   w!=cells.end();
        // w++)
        double sum=0;
        
        for (list<Node *>::const_iterator i=nodes.begin();
             i!=nodes.end();
             i++) {
             sum+=f(**i)*g(**i);
        }
        return sum;
        
        
    }


 signals:
  void ChemMonValue(double t, double *x);

 protected:
  void XMLAddCore(xmlNodePtr xmlcell) const;
  int XMLRead(xmlNode *cur);
  void DivideWalls(ItList new_node_locations, const Vector from, const Vector to, bool wall_fixed = false, NodeSet *node_set = 0);

 private:

  static QPen *cell_outline_pen;
  static double offset[3];
  static double factor;
  Mesh *m;
  void ConstructConnections(void);
  void SetWallLengths(void);
};


// Boundarypolygon is a special cell; will not increase ncells
//  and will not be part of Mesh::cells
class BoundaryPolygon : public Cell {

 public:
 BoundaryPolygon(void) : Cell() {
    NCells()--;
    index=-1;
  }

 BoundaryPolygon(double x,double y,double z=0) : Cell (x,y,z) {
    NCells()--;
    index=-1;
  }

  BoundaryPolygon &operator=(Cell &src) {
    Cell::operator=(src);
    index=-1;
    return *this;
  }
  virtual void Draw(QGraphicsScene *c, QString tooltip = QString::Null());

  virtual void XMLAdd(xmlNodePtr parent_node) const;

  virtual bool BoundaryPolP(void) const { return true; } 
};

#endif

/* finis */
