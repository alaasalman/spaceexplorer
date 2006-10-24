#ifndef SPACE_MAP_H
#define SPACE_MAP_H

#include <QtGui>
#include "Planet.h"


class SpaceMap :public QTableWidget
{
  Q_OBJECT;

 public:
  SpaceMap(QWidget*);
  ~SpaceMap();
  void paintEvent(QPaintEvent*);
  void placePlanet(Planet*, int, int);
  void mouseMoveEvent(QMouseEvent*);
  
  public slots:
    void onSpacePressed(int,int);
  void onSpaceEntered(int,int);
  
 signals:
  void overPlanet(Planet*);
  
  

};

#endif
