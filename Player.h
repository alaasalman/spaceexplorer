
#ifndef PLAYER_H_
#define PLAYER_H_

#include <QtGui>
#include "Planet.h"

class Planet;
class Player : public QObject
{
  Q_OBJECT;

 public:
  Player();
  Player(QString, QColor, bool);
  ~Player();
  QString getName();
  void setName(QString);
  QColor getColor();
  void setColor(QColor);
  bool getComputer();
  void setComputer(bool);
  void setPlanets(QList<Planet*>);
  QList<Planet*> getPlanets();
  void addToPlanets(Planet*);
  void removeFromPlanets(Planet*);

 private:
  QString name;
  QColor color;
  bool computer;
  QList<Planet*> planets;

};

#endif
