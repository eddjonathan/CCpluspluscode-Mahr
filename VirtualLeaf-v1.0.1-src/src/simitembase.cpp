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
#include <QBrush>
#include "simitembase.h"

static const std::string _module_id("$Id: simitembase.cpp,v 15d600891648 2010/06/24 13:22:58 michael $");

SimItemBase::SimItemBase( void *v, QGraphicsScene *canvas )
{
  obj=v;
};

SimItemBase::~SimItemBase(void) {};

void SimItemBase::userMove(double dx, double dy){};

/* finis */
