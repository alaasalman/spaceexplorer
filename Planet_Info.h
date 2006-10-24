#ifndef PLANET_INFO_H_
#define PLANET_INFO_H_

#include <QtGui>

#include "Planet.h"

class Planet_Info : public QFrame
{
  Q_OBJECT;
  
 public:
  Planet_Info(QWidget*);
  ~Planet_Info();
  void showPlanet(Planet*);
  
 private:
  QLabel* planet_name;
  QLabel* planet_owner;
  QLabel* planet_ships;
  QLabel* planet_production;
  QLabel* planet_killpercent;
  QLabel* planet_name_text;
  QLabel* planet_owner_text;
  QLabel* planet_ships_text;
  QLabel* planet_production_text;
  QLabel* planet_killpercent_text;

  
};

#endif
