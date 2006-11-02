#include "GameController.h"
#include <iostream>
GameController::GameController()
  :QObject()
{
  currentPlayer = 0;
}

GameController::~GameController()
{
}

void GameController::onStartGame()
{
  this->populateMap();
  
  emit displayControl(QString("<font color=%1>%2</font>:Select source planet").arg(players[currentPlayer]->getColor().name()).arg(players[currentPlayer]->getName()));

}

void GameController::onEndGame()
{


}

void GameController::onAddHumanPlayer(QString humanName, QColor humanColor)
{
  players.append(new Player(humanName, humanColor, false));

}

void GameController::onChangeTurnsNum(int newTurns)
{
  this->turns = newTurns;
}

void GameController::onChangeNeutralPlanetsNum(int planetsNum)
{
  this->planets = planetsNum;
}

void GameController::onChangeTurn()
{
  if(currentPlayer < players.size() - 1)
    currentPlayer++;
  else
    currentPlayer = 0;

  emit displayControl(QString("<font color=%1>%2</font>:Select source planet").arg(players[currentPlayer]->getColor().name()).arg(players[currentPlayer]->getName()));
}

void GameController::onAddComputerPlayer(QString compName, QColor compColor)
{
  players.append(new Player(compName, compColor, true));
}

void GameController::populateMap()
{
  for(int i=0; i<planets; i++)
    {
      Planet* p = new Planet();
      p->setName(QString("L%1").arg(i));
      emit triggerPlanetLocate(p, i, i);
    }

  for(int j=0; j<players.size(); j++)
    {
      Planet* p = new Planet();
      p->setName("FOO");
      p->setOwner(players[j]);
      players[j]->addToPlanets(p);
      emit triggerPlanetLocate(p, 0, j+1);
      
    }

}
