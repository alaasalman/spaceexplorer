#include "GameController.h"
#include <iostream>
GameController::GameController()
  :QObject()
{
}

GameController::~GameController()
{
}

void GameController::onStartGame()
{
  this->populateMap();

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
      p->setOwner(players[j]->getName());
      emit triggerPlanetLocate(p, 0, j+1);
      std::cout<<players[j]->getName().toStdString()<<" at "<<j+1<<std::endl;
    }

}
