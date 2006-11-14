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

void GameController::onSetSelectPlanet(Planet* planet)
{
  Fleet* fleet = NULL;
  planet->blink();
  /* on first selection and since last assumes that the vector is not empty */
  if(fleets.isEmpty())
    {
      fleet = new Fleet();
      fleets.append(fleet);
    }
  
  fleet = fleets.last();
  
  if(fleet->getSource() == NULL) /* selecting source */
    {
      fleet->setSource(planet);
      fleet->setKillPercent(planet->getKillPercent());
      fleet->setOwner(players[currentPlayer]);
    }
  else /* selecting destination */
    {
      fleet->setDestination(planet);
      fleet = new Fleet();
      fleets.append(fleet);
    }

}


void GameController::populateMap()
{
  for(int i=0; i<planets; i++)
    {
      Planet* p = new Planet();
      p->setName(QString("L%1").arg(i));
      
      connect(p, SIGNAL(selectPlanet(Planet*)), this, SLOT(onSetSelectPlanet(Planet*)));
      
      emit triggerPlanetLocate(p, i, i);
    }

  for(int j=0; j<players.size(); j++)
    {
      Planet* p = new Planet();
      p->setName("FOO");
      p->setOwner(players[j]);
      players[j]->addToPlanets(p);
      
      connect(p, SIGNAL(selectPlanet(Planet*)), this, SLOT(onSetSelectPlanet(Planet*)));
      
      emit triggerPlanetLocate(p, 0, j+1);
      
    }

}
