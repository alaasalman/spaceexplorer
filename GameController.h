#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <QtGui>
#include "Planet.h"
#include "Player.h"
#include "Fleet.h"

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
  void onAddComputerPlayer(QString, QColor);
  void onChangeTurnsNum(int);
  void onChangeNeutralPlanetsNum(int);
  void onChangeTurn();
  void onSetSelectPlanet(Planet*);
  void onSetFleetShipNumber(int);
  void onDisplayFleets();
  

 signals:
  void triggerPlanetLocate(Planet*, int, int);
  void displayControl(QString);
  void displayInfo(QString);
  void displayShipNumber();

 private:
  QVector<Fleet*> fleets;
  QVector<Player*> players;
  int currentPlayer;
  int turns;
  int planets;

};

#endif
