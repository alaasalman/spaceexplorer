#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <QtGui>
#include "SpaceMap.h"
#include "Planet_Info.h"

class GameBoard : public QWidget
{
  Q_OBJECT;
  
 public:
  GameBoard(QWidget*);
  ~GameBoard();
  
  
 private:
  SpaceMap* spacemap;
  Planet_Info* planet_info;

  public slots:
    void onAddPlanet(Planet*, int, int);
  void onDisplayPlanet(Planet*);
    
};


#endif
