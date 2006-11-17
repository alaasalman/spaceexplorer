#include "Planet.h"
#include <iostream>


Planet::Planet()
  :QWidget()
{
  
  pixie = new QPixmap("pics/planet1");
  
  this->name = ""; 
  this->owner = NULL;
  this->ships = 0;
  this->killpercent = 0.0;
  this->production = 0;
 
  this->drawColor = true;

  timer.setInterval(500);
  connect(&timer, SIGNAL(timeout()), this, SLOT(fireTimer()));
}

void Planet::paintEvent(QPaintEvent* event)
{
  
  QPainter p(this);
  QPoint pos;
  QPen pen;

  pos.setX(4);
  pos.setY(4);
  p.drawPixmap(pos, *pixie, QRect(0, 0, pixie->height(), pixie->width()));
  
  if(this->drawColor == true && this->owner != NULL)
    {
      pen.setColor(this->owner->getColor());
    }
  else
    {
      // pen.setColor(Qt::red);
    }

  p.setPen(pen);
  p.drawRect(0, 0, 26, 26);
  
}

void Planet::mousePressEvent(QMouseEvent* event)
{
  emit selectPlanet(this);
}

void Planet::blink()
{
  if(timer.isActive())
    {
      timer.stop();
      this->drawColor = true;
      this->update();
      return;
    }
  timer.start();
}
void Planet::fireTimer()
{
  //  qDebug("TIMER");
  if(this->drawColor == true)
    {
      this->drawColor = false;
    }
  else
    {
      this->drawColor = true;
    }
  this->update();
}

QString Planet::getName()
{
  return this->name;
}

Player* Planet::getOwner()
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

void Planet::setOwner(Player* newOwner)
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
