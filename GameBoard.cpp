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
  //  endTurn->setGeometry(0, 0, 75, 25);
  
  shipNumber = new QLineEdit();
  shipNumber->setFixedSize(75, 25);
  shipNumber->setVisible(false);

  displayInfo = new QTextEdit();
  displayInfo->setFixedSize(630, 150);
  //  displayInfo->setGeometry(0, 0, 550, 50);
  
  // QPalette mainPal;
  //mainPal.setColor(QPalette::Window, Qt::black);
  //mainPal.setColor(QPalette::Text, Qt::white);
  //mainPal.setColor(QPalette::WindowText, Qt::white);
  //mainPal.setColor(backgroundRole(), Qt::black);
  QColor col(Qt::green);
  QPalette mainPal;
  mainPal.setColorGroup( QPalette::Active, Qt::white, Qt::black, col.light(), col.dark(), col, col.dark(75), col.dark(75), col.dark(), Qt::black );
  mainPal.setColorGroup( QPalette::Inactive, Qt::white, Qt::black, col.light(), col.dark(), col, col.dark(75), col.dark(75), col.dark(), Qt::black );
  mainPal.setColorGroup( QPalette::Disabled, Qt::white, Qt::black, col.light(), col.dark(), col, col.dark(75), col.dark(75), col.dark(), Qt::black );

  QColor colo(Qt::black);
  QPalette pal;
  pal.setColorGroup(QPalette::Active, Qt::white, Qt::black, col.light(), col.dark(), col, col.dark(75), colo.light(), colo.light(), Qt::darkGreen );

  this->setAutoFillBackground(true);
  spacemap->setAutoFillBackground(true);
  
  
  this->setPalette(mainPal);
  planet_info->setPalette(mainPal);
  spacemap->setPalette(pal);
  controlInfo->setPalette(mainPal);
  endTurn->setPalette(mainPal);
  displayInfo->setPalette(pal);
  shipNumber->setPalette(mainPal);
  

  this->setMouseTracking(true);
  
  QHBoxLayout* qhbLayout = new QHBoxLayout();
  qhbLayout->addWidget(controlInfo);
  qhbLayout->addWidget(shipNumber);
  qhbLayout->addWidget(endTurn);

  QVBoxLayout* qvbLayout = new QVBoxLayout();
  qvbLayout->addLayout(qhbLayout);
  qvbLayout->addWidget(spacemap);
  qvbLayout->addWidget(displayInfo);
  
  QHBoxLayout* qhbLayoutGeneral = new QHBoxLayout();
  qhbLayoutGeneral->addLayout(qvbLayout);
  qhbLayoutGeneral->addWidget(planet_info);
  
  //this->setFocusPolicy(Qt::StrongFocus);
  //shipNumber->setFocusPolicy(Qt::StrongFocus);
  this->setLayout(qhbLayoutGeneral);
  
  connect(spacemap, SIGNAL(overPlanet(Planet*)), this, SLOT(onDisplayPlanet(Planet*)));
  connect(endTurn, SIGNAL(pressed()), this, SLOT(onTurnButton()));
  connect(shipNumber, SIGNAL(returnPressed()), this, SLOT(onShipNumberSelect()));
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

void GameBoard::onDisplayShipNumber()
{
  shipNumber->setText("");
  shipNumber->setVisible(true);
  shipNumber->setEnabled(true);
  shipNumber->setFocus();
}

void GameBoard::onShipNumberSelect()
{
  
  int ships = 0;

  ships = shipNumber->text().toInt();
  emit setFleetShipNumber(ships);
  shipNumber->setVisible(false);

}

void GameBoard::keyPressEvent(QKeyEvent* event)
{
  
  if(event->key() == Qt::Key_Escape)
    qDebug("ESCAPE");
  else
    event->ignore();
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

