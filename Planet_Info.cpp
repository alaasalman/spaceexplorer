#include "Planet_Info.h"


Planet_Info::Planet_Info(QWidget* parent)
  : QFrame(parent)
{
  planet_name = new QLabel("Planet Name:");
  planet_owner = new QLabel("Owner:");
  planet_ships = new QLabel("Ships:");
  planet_production = new QLabel("Production:");
  planet_killpercent = new QLabel("Kill Percent:");

  planet_name_text = new QLabel();
  planet_name_text->setMinimumWidth(50);

  planet_owner_text = new QLabel();
  planet_owner_text->setMinimumWidth(50);

  planet_ships_text = new QLabel();
  planet_ships_text->setMinimumWidth(50);

  planet_production_text = new QLabel();
  planet_production_text->setMinimumWidth(50);

  planet_killpercent_text = new QLabel();
  planet_killpercent_text->setMinimumWidth(50);

  
  QGridLayout* qglayout = new QGridLayout();
  qglayout->addWidget(planet_name, 0, 0);
  qglayout->addWidget(planet_name_text, 0, 1);
  qglayout->addWidget(planet_owner, 1, 0);
  qglayout->addWidget(planet_owner_text, 1, 1);
  qglayout->addWidget(planet_ships, 2, 0);
  qglayout->addWidget(planet_ships_text, 2, 1);
  qglayout->addWidget(planet_production, 3, 0);
  qglayout->addWidget(planet_production_text, 3, 1);
  qglayout->addWidget(planet_killpercent, 4, 0);
  qglayout->addWidget(planet_killpercent_text, 4, 1);
  
  this->setLayout(qglayout);

}

Planet_Info::~Planet_Info()
{
  delete planet_name;
  delete planet_owner;
  delete planet_ships;
  delete planet_production;
  delete planet_killpercent;
  delete planet_name_text;
  delete planet_owner_text;
  delete planet_ships_text;
  delete planet_production_text;
  delete planet_killpercent_text;
}

void Planet_Info::showPlanet(Planet* planet)
{
  if( planet->getOwner() == NULL )
    {
      planet_name_text->clear();
      planet_owner_text->clear();
      planet_ships_text->clear();
      planet_production_text->clear();
      planet_killpercent_text->clear();
      return;
    }
  else
    {
      planet_name_text->setText(planet->getName());
      planet_owner_text->setText(planet->getOwner()->getName());
      planet_ships_text->setNum(planet->getShips());
      planet_production_text->setNum(planet->getProduction());
      planet_killpercent_text->setNum(planet->getKillPercent());
    }

}
