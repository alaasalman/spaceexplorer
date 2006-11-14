#ifndef PLANET_H_
#define PLANET_H_

#include <QtGui>
#include "Player.h"

class Player;

class Planet : public QWidget
{
  Q_OBJECT;
  
 public:
  Planet();
  ~Planet();
  void paintEvent(QPaintEvent*);
  QString getName();
  Player* getOwner();
  int getShips();
  int getProduction();
  double getKillPercent();
  void setName(QString);
  void setOwner(Player*);
  void setShips(int);
  void setProduction(int);
  void setKillPercent(double);
  void blink();

 private:
  void mousePressEvent(QMouseEvent*);

  private slots:
  void fireTimer();

 signals:
  void selectPlanet(Planet*);
  
  
 private:
  QPixmap* pixie;
  QString name;
  Player* owner;
  int ships;
  int production;
  double killpercent;
  bool drawColor;
  QTimer timer;
  
    
};

#endif
