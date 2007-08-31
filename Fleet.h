#ifndef FLEET_H_
#define FLEET_H_

#include "Planet.h"
#include "Player.h"

class Fleet
{
 public:
  Fleet();
  ~Fleet();
  Planet* getSource();
  Planet* getDestination();
  int getNumShips();
  double getKillPercent();
  Player* getOwner();
  void setSource(Planet*);
  void setDestination(Planet*);
  void setNumShips(int);
  void setOwner(Player*);
  void setKillPercent(double);
  int getArrivalTurn();
  void setArrivalTurn(int);


 private:
  Planet* source;
  Planet* destination;
  int numships;
  double killpercent;
  Player* owner;
  int arrivalTurn;

};

#endif
