#include "Fleet.h"

Fleet::Fleet()
{
  this->source = NULL;
  this->destination = NULL;
  this->numships = 0;
  this->killpercent = 0.0;
  this->owner = NULL;
}

Fleet::~Fleet()
{
}


Planet* Fleet::getSource()
{
  return this->source;
}

Planet* Fleet::getDestination()
{
  return this->destination;
}

int Fleet::getNumShips()
{
  return this->numships;
}

double Fleet::getKillPercent()
{
  return this->killpercent;
}

Player* Fleet::getOwner()
{
  return this->owner;
}

void Fleet::setSource(Planet* newSource)
{
  this->source = newSource;
}
void Fleet::setDestination(Planet* newDestination)
{
  this->destination = newDestination;
}

void Fleet::setNumShips(int newNumShips)
{
  this->numships = newNumShips;
}

void Fleet::setOwner(Player* newOwner)
{
  this->owner = newOwner;
}

void Fleet::setKillPercent(double newKillPercent)
{
  this->killpercent = newKillPercent;
}
