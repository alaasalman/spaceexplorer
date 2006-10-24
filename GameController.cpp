#include "GameController.h"

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
  players.append(new Player(humanName, humanColor));

}

void GameController::populateMap()
{
  for(int i=0; i<6; i++)
    {
      Planet* p = new Planet();
      p->setName(QString("L%1").arg(i));
      emit triggerPlanetLocate(p, i, i);
    }

  for(int i=0; i<players.size(); i++)
    {
      Planet* p = new Planet();
      p->setName("FOO");
      p->setOwner(players[i]->getName());
      emit triggerPlanetLocate(p, 0, i+1);
    }

}
