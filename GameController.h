#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <QtGui>
#include "Planet.h"
#include "Player.h"

class GameController : public QObject
{
  Q_OBJECT;
  
 public:
  GameController();
  ~GameController();

 private:
  void populateMap();

  public slots:
    void onStartGame();
  void onEndGame();
  void onAddHumanPlayer(QString, QColor);

 signals:
  void triggerPlanetLocate(Planet*, int, int);

 private:
  QVector<Player*> players;

};

#endif