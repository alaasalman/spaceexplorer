#include "GameController.h"
#include <iostream>

const QString GameController::pNames[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22"};

GameController::GameController()
  :QObject()
{
  
}

GameController::~GameController()
{
}

void GameController::onStartGame()
{  
  currentPlayer = 0;
  currentTurn = 1;
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
  this->totalTurns = newTurns;
}

void GameController::onChangeNeutralPlanetsNum(int planetsNum)
{
  this->planets = planetsNum;
}

void GameController::onChangeTurn()
{
  currentTurn++;

  /* impose production on owned planets */
  for(int i=0; i<players.size(); i++)
    {
      Player* tempP = players[i];
      for(int j=0; j<players[i]->getPlanets().size(); j++)
	{
	  Planet* tempPl = tempP->getPlanets()[j];
	  tempPl->setShips( tempPl->getShips() +  tempPl->getProduction());
	}
    }

  for(int k=0; k<fleets.size(); k++)
    {
      Fleet* tempF = fleets[k];
      /* fleet has arrived */
      if(fleets[k]->getArrivalTurn() == currentTurn)
	{
	  /* fleet owner same as destination owner, so reinforcing a planet */
	  if(tempF->getOwner() == tempF->getDestination()->getOwner())
	    {
	      tempF->getDestination()->setShips(tempF->getDestination()->getShips() + tempF->getNumShips());
	    }
	  else /* attacking planet */
	    {
	      double attackScore, defenseScore;

	      attackScore = tempF->getNumShips()*tempF->getKillPercent();
	      defenseScore = tempF->getDestination()->getShips()*tempF->getDestination()->getKillPercent();

	      if(attackScore >= defenseScore) /* attackers win */
		{
		  if(tempF->getDestination()->getOwner() != NULL)
		    tempF->getDestination()->getOwner()->removeFromPlanets(tempF->getDestination());

		  tempF->getOwner()->addToPlanets(tempF->getDestination());
		  tempF->getDestination()->setOwner(tempF->getOwner());
		  
		  tempF->getDestination()->setShips((int)attackScore-defenseScore);
		  emit displayInfo(QString("Turn %1: Planet %2 has fallen to %3").arg(currentTurn).arg(tempF->getDestination()->getName()).arg(tempF->getOwner()->getName()));
		  
		}
	      else /* defense wins */
		{
		  tempF->getDestination()->setShips((int)defenseScore-attackScore);
		  emit displayInfo(QString("Turn %1: Planet %2 has held against an attack from %3.").arg(currentTurn).arg(tempF->getDestination()->getName()).arg(tempF->getOwner()->getName()));
		}
	    }
	  /* processed fleet, so remove it */
	  fleets.removeAt(k);
	}
    }
     

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
  
  /* on first selection and since last assumes that the vector is not empty */
  if(fleets.isEmpty())
    {
      fleet = new Fleet();
      fleets.append(fleet);
    }
  
  fleet = fleets.last();
  
  if(fleet->getSource() == NULL) /* selecting source */
    {

      if(planet->getOwner() != players[currentPlayer]) /* if trying to choose a source planet that isn't yours */
	return;

      planet->blink();
      fleet->setSource(planet);
      fleet->setKillPercent(planet->getKillPercent());
      fleet->setOwner(players[currentPlayer]);

      emit displayControl(QString("<font color=%1>%2</font>:Select destination planet").arg(players[currentPlayer]->getColor().name()).arg(players[currentPlayer]->getName()));
    }
  else if(fleet->getDestination() == NULL) /* selecting destination */
    {
      if(fleet->getSource() == planet) /* source and destination are the same */
	return;

      planet->blink();
      fleet->setDestination(planet);
      
      emit displayShipNumber();
      
      emit displayControl(QString("<font color=%1>%2</font>:Number of ships").arg(players[currentPlayer]->getColor().name()).arg(players[currentPlayer]->getName()));
      
    }
  

}

void GameController::onSetFleetShipNumber(int ships)
{
  Fleet* fleet = NULL;

  fleet = fleets.last();

  fleet->getSource()->setShips(fleet->getSource()->getShips() - ships);
  
  fleet->setNumShips(ships);
  fleet->setKillPercent(fleet->getSource()->getKillPercent());
  fleet->setArrivalTurn(currentTurn+2);

  fleet->getSource()->blink();
  fleet->getDestination()->blink();

  fleet = new Fleet();
  fleets.append(fleet);
  
  emit displayControl(QString("<font color=%1>%2</font>:Select source planet").arg(players[currentPlayer]->getColor().name()).arg(players[currentPlayer]->getName()));

}

void GameController::onDisplayFleets()
{
  QString temp;

  for(int i=0; i<fleets.size() - 1; i++)
    {
      temp += QString("%1").arg(i) + " " + fleets[i]->getSource()->getName() + "->" + fleets[i]->getDestination()->getName() + " " + QString("%1").arg(fleets[i]->getNumShips()) + ":" + QString("%1").arg(fleets[i]->getKillPercent()) + " " + fleets[i]->getOwner()->getName(); 
      
      std::cout<<temp.toStdString()<<std::endl;
      temp = "";
    }

}

void GameController::populateMap()
{
  int nameIterator = 0;

  for(int i=0; i<planets; i++)
    {
      Planet* p = new Planet();
      
      p->setName(pNames[nameIterator]);
      p->setShips(16);
      p->setKillPercent(0.8);
      p->setProduction(11);

      connect(p, SIGNAL(selectPlanet(Planet*)), this, SLOT(onSetSelectPlanet(Planet*)));
      
      emit triggerPlanetLocate(p, i, i);
      nameIterator++;
    }

  for(int j=0; j<players.size(); j++)
    {
      Planet* p = new Planet();
     
      p->setName(pNames[nameIterator]);
      p->setOwner(players[j]);
      p->setShips(10);
      p->setProduction(10);
      p->setKillPercent(0.4);

      players[j]->addToPlanets(p);
      
      connect(p, SIGNAL(selectPlanet(Planet*)), this, SLOT(onSetSelectPlanet(Planet*)));
      
      emit triggerPlanetLocate(p, 0, j+1);
      nameIterator++;
      
    }

}
