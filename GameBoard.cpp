#include "GameBoard.h"


GameBoard::GameBoard(QWidget* parent)
:QWidget(parent)
{
  //this->setGeometry(0, 0, 200, 200);
  spacemap = new SpaceMap(this);
  
  planet_info = new Planet_Info(this);
  
  QPalette mainPal;
  mainPal.setColor(QPalette::Window, Qt::black);
  mainPal.setColor(QPalette::Text, Qt::white);
  mainPal.setColor(QPalette::WindowText, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(mainPal);

  planet_info->setPalette(mainPal);
  spacemap->setPalette(mainPal);

  this->setMouseTracking(true);
  QGridLayout* qglayout = new QGridLayout();
  qglayout->addWidget(spacemap, 0, 0, 2, 1);
  qglayout->addWidget(planet_info, 0, 1, 1, 1);
  
  this->setLayout(qglayout);
  
  connect(spacemap, SIGNAL(overPlanet(Planet*)), this, SLOT(onDisplayPlanet(Planet*)));
}

void GameBoard::onAddPlanet(Planet* planet, int row, int column)
{
  spacemap->placePlanet(planet, row, column);
}

void GameBoard::onDisplayPlanet(Planet* planet)
{
  planet_info->showPlanet(planet);
}

GameBoard::~GameBoard()
{
  delete spacemap;
  delete planet_info;
}

