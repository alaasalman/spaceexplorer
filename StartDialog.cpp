#include "StartDialog.h"

#include <iostream>
StartDialog::StartDialog(QWidget* parent)
  :QDialog(parent)
{
  playerList = new QListWidget();
  humanName = new QLineEdit();
  addHuman = new QPushButton();
  okButton = new QPushButton();
  cancelButton = new QPushButton();
  playerNumbers = new QSlider();
  playerNum = new QLabel();
  neutralPlanetNum = new QLabel();
  neutralPlanetNumbers = new QSlider();
  turnsNum = new QLabel();
  turnsNumber = new QSlider();
  

  addHuman->setText("Add Human Player");
  okButton->setText("Ok");
  okButton->setIcon(QIcon("pics/button_ok"));
  cancelButton->setText("Cancel");
  cancelButton->setIcon(QIcon("pics/button_cancel"));


  this->numOfPlayers = 0;
  //  playerColors = new QColor[9];
  playerColors[0] = QColor( 130, 130, 255 );
  playerColors[1] = Qt::yellow;
  playerColors[2] = Qt::red;
  playerColors[3] = Qt::green;
  playerColors[4] = Qt::white;
  playerColors[5] = Qt::cyan;
  playerColors[6] = Qt::magenta;
  playerColors[7] = QColor(235, 153, 46);
  playerColors[8] = QColor( 106, 157, 104 );
  playerColors[9] = QColor( 172, 235, 104 );

  playerNumbers->setMinimum(2);
  playerNumbers->setMaximum(9);
  playerNumbers->setOrientation(Qt::Horizontal);
  
  neutralPlanetNumbers->setMinimum(1);
  neutralPlanetNumbers->setMaximum(35);
  neutralPlanetNumbers->setOrientation(Qt::Horizontal);

  turnsNumber->setMinimum(5);
  turnsNumber->setMaximum(40);
  turnsNumber->setOrientation(Qt::Horizontal);

  this->onChangeTurns(5);
  this->onChangeNeutralPlanet(1);
  this->onChangePlayer(1);
  this->onChangePlayer(2);

  connect(addHuman, SIGNAL(clicked()), this, SLOT(onAddHumanPlayer()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(onFinishedDialog()));
  connect(playerNumbers, SIGNAL(valueChanged(int)), this, SLOT(onChangePlayer(int)));
  connect(neutralPlanetNumbers, SIGNAL(valueChanged(int)), this, SLOT(onChangeNeutralPlanet(int)));
  connect(turnsNumber, SIGNAL(valueChanged(int)), this, SLOT(onChangeTurns(int)));

  
  QGridLayout* qglayout = new QGridLayout();
  
  qglayout->addWidget(playerNum, 0, 0);
  qglayout->addWidget(playerNumbers, 1, 0);
  qglayout->addWidget(playerList, 2, 0);
  qglayout->addWidget(humanName, 3, 0);
  qglayout->addWidget(addHuman, 4, 0);
  qglayout->addWidget(turnsNum, 5, 0);
  qglayout->addWidget(turnsNumber, 6, 0, 1, 2);

  qglayout->addWidget(neutralPlanetNum, 0, 1);
  qglayout->addWidget(neutralPlanetNumbers, 1, 1);
  
  QHBoxLayout* qhblayout = new QHBoxLayout();
  
  qhblayout->addWidget(okButton);
  qhblayout->addWidget(cancelButton);
 
  this->setFixedSize(550,400);
 
   
  qglayout->addLayout(qhblayout, 7, 1);
  this->setLayout(qglayout);

  
  
}

void StartDialog::onAddHumanPlayer()
{
  QString hName = humanName->text();

  if(hName.isEmpty())
    {
      return;
    }
  
  if( !playerList->findItems(hName, Qt::MatchExactly).empty())
    {
      return;
    }
  
  for(int i=0; i<playerList->count(); i++)
    {
      if(playerList->item(i)->text().startsWith("Comp"))
	{
	  QListWidgetItem* temp;
	  
	  temp = playerList->takeItem(i);
	  playerList->insertItem(i, new QListWidgetItem(temp->icon(), hName));
	  
	  return;
	}
    }

  if(numOfPlayers == 9)
    {
      return;
    }

  QColor hColor = playerColors[numOfPlayers];
  QPixmap tinyColor(16, 16);
  tinyColor.fill(hColor);
  playerList->addItem(new QListWidgetItem(QIcon(tinyColor), hName));
    
  this->onChangePlayer(playerNumbers->value() + 1);
  playerNumbers->setValue(playerNumbers->value() + 1);
  numOfPlayers++;
  
}

void StartDialog::onChangePlayer(int value)
{
  playerNum->setText(QString("Number of Players: %1").arg(value)); 
  
  if(value > playerList->count()) //add players
    {
      this->onAddComputerPlayer();
      return;
    }
  
  if(value < playerList->count())
    {
      this->removePlayer();
      return;
    }
}

void StartDialog::onChangeTurns(int value)
{
  turnsNum->setText(QString("Number of turns: %1").arg(value)); 
}

void StartDialog::onChangeNeutralPlanet(int value)
{
  neutralPlanetNum->setText(QString("Number of neutral planets: %1").arg(value));
}

void StartDialog::onAddComputerPlayer()
{
  
  QColor compColor = playerColors[numOfPlayers];
  QPixmap tinyColor(16, 16);
  QString compName = QString("Comp%1").arg(numOfPlayers);

  tinyColor.fill(compColor);

  
  playerList->addItem(new QListWidgetItem(QIcon(tinyColor), compName));

  numOfPlayers++;
      
 
}

void StartDialog::removePlayer()
{
  delete playerList->takeItem(playerList->count() - 1);
  
  numOfPlayers--;
}

void StartDialog::onFinishedDialog()
{
  for(int i=0; i<playerList->count(); i++)
    {
      if(playerList->item(i)->text().startsWith("Comp"))
	{
	  emit addComputerPlayer(playerList->item(i)->text(), playerColors[i]);
	}
      else
	{
	  emit addHumanPlayer(playerList->item(i)->text(), playerColors[i]);
	}
    }

  emit changeTurnsNum(turnsNumber->value());
  emit changeNeutralPlanetsNum(neutralPlanetNumbers->value()); 
  this->accept();
    
}

StartDialog::~StartDialog()
{
  delete playerList;
  delete humanName;
  delete addHuman;
  delete okButton;
  delete cancelButton;
  delete playerColors;
  delete playerNumbers;
  delete playerNum;
  delete neutralPlanetNum;
  delete neutralPlanetNumbers;
  delete turnsNum;
  delete turnsNumber;
}

