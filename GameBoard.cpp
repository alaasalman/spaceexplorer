#include "GameBoard.h"


GameBoard::GameBoard(QWidget* parent)
:QWidget(parent)
{
  
  spacemap = new SpaceMap(this);
  spacemap->setGeometry(0, 0, 550, 550);
  
  planet_info = new Planet_Info(this);
  planet_info->setGeometry(0, 0, 80, 80);

  controlInfo = new QLabel("SDSDSDSDS");
  controlInfo->setGeometry(0, 0, 530, 10);

  endTurn = new QPushButton("End Turn");
  endTurn->setFixedSize(75, 25);
  //  endTurn->setGeometry(0, 0, 20, 10);

  displayInfo = new QTextEdit();
  displayInfo->setFixedSize(630, 50);
  //  displayInfo->setGeometry(0, 0, 550, 50);
  
  QPalette mainPal;
  mainPal.setColor(QPalette::Window, Qt::black);
  mainPal.setColor(QPalette::Text, Qt::white);
  mainPal.setColor(QPalette::WindowText, Qt::white);
  this->setAutoFillBackground(true);
  spacemap->setAutoFillBackground(true);
  spacemap->setBackgroundRole(QPalette::Window);

  this->setPalette(mainPal);
  planet_info->setPalette(mainPal);
  spacemap->setPalette(mainPal);
  controlInfo->setPalette(mainPal);
  endTurn->setPalette(mainPal);
  displayInfo->setPalette(mainPal);

  

  this->setMouseTracking(true);
  
  QHBoxLayout* qhbLayout = new QHBoxLayout();
  qhbLayout->addWidget(controlInfo);
  qhbLayout->addWidget(endTurn);

  QVBoxLayout* qvbLayout = new QVBoxLayout();
  qvbLayout->addLayout(qhbLayout);
  qvbLayout->addWidget(spacemap);
  qvbLayout->addWidget(displayInfo);

  QHBoxLayout* qhbLayoutGeneral = new QHBoxLayout();
  qhbLayoutGeneral->addLayout(qvbLayout);
  qhbLayoutGeneral->addWidget(planet_info);

  /*  QGridLayout* qglayout = new QGridLayout();
      qglayout->addWidget(controlInfo, 0, 0);
      qglayout->addWidget(spacemap, 1, 0, 2, 1);
      qglayout->addWidget(planet_info, 0, 1, 2, 1);*/
  
  this->setLayout(qhbLayoutGeneral);
  
  connect(spacemap, SIGNAL(overPlanet(Planet*)), this, SLOT(onDisplayPlanet(Planet*)));
  connect(endTurn, SIGNAL(pressed()), this, SLOT(onTurnButton()));
}

void GameBoard::onAddPlanet(Planet* planet, int row, int column)
{
  spacemap->placePlanet(planet, row, column);
}

void GameBoard::onDisplayPlanet(Planet* planet)
{
  planet_info->showPlanet(planet);
}

void GameBoard::onDisplayInfo(QString info)
{
  displayInfo->append(info);
}

void GameBoard::onDisplayControl(QString controlString)
{
  controlInfo->setText(controlString);
}

void GameBoard::onTurnButton()
{
  emit changeTurn();
}

GameBoard::~GameBoard()
{
  delete spacemap;
  delete planet_info;
  delete controlInfo;
  delete endTurn;
  delete displayInfo;
}

