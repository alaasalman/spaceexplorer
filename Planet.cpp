#include "Planet.h"
#include <iostream>

Planet::Planet()
  :QWidget()
{
  
  pixie = new QPixmap("pics/planet1");
  
  this->name = ""; 
  this->owner = "";
  this->ships = 0;
  this->killpercent = 0.0;
  this->production = 0;
}

void Planet::paintEvent(QPaintEvent* event)
{
  
  QPainter p(this);
  
  p.drawPixmap(0,0, *pixie);

   
}

QString Planet::getName()
{
  return this->name;
}


QString Planet::getOwner()
{
  return this->owner;
}

int Planet::getShips()
{
  return this->ships;
}

int Planet::getProduction()
{
  return this->production;
}

double Planet::getKillPercent()
{
  return this->killpercent;
}

void Planet::setName(QString newName)
{
  this->name = newName;
}

void Planet::setOwner(QString newOwner)
{
  this->owner = newOwner;
}

void Planet::setShips(int newShips)
{
  this->ships = newShips;
}

void Planet::setProduction(int newProduction)
{
  this->production = newProduction;
}

void Planet::setKillPercent(double newKillPercent)
{
  this->killpercent = newKillPercent;
}

Planet::~Planet()
{
  delete pixie;
}
