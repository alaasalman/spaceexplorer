#include "StartDialog.h"


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


  addHuman->setText("Add Human Player");
  okButton->setText("Ok");
  okButton->setIcon(QIcon("pics/button_ok"));
  cancelButton->setText("Cancel");
  cancelButton->setIcon(QIcon("pics/button_cancel"));


  QVBoxLayout* qvblayoutleft = new QVBoxLayout();
  
  qvblayoutleft->addWidget(playerNum);
  qvblayoutleft->addWidget(playerNumbers);
  qvblayoutleft->addWidget(playerList);
  qvblayoutleft->addWidget(humanName);
  qvblayoutleft->addWidget(addHuman);

  QHBoxLayout* qhblayout = new QHBoxLayout();
  
  qhblayout->addWidget(okButton);
  qhblayout->addWidget(cancelButton);
  
  
  qvblayoutleft->addLayout(qhblayout);
  
  this->setLayout(qvblayoutleft);

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

  playerNum->setText("Number of Players: 2");

  connect(addHuman, SIGNAL(clicked()), this, SLOT(onAddHumanPlayer()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(playerNumbers, SIGNAL(valueChanged(int)), this, SLOT(onAddPlayer(int)));

  this->addPlayer();
  this->addPlayer();
  
}

void StartDialog::onAddHumanPlayer()
{
  QString hName = humanName->text();


  if(numOfPlayers == 9)
    {
      return;
    }
  
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
	  emit addHumanPlayer(hName, playerColors[i]);
	  return;
	}
    }

  QColor hColor = playerColors[numOfPlayers];
  QPixmap tinyColor(16, 16);
  tinyColor.fill(hColor);
  playerList->addItem(new QListWidgetItem(QIcon(tinyColor), hName));
  emit addHumanPlayer(hName, hColor);
  
  this->onAddPlayer(playerNumbers->value() + 1);
  playerNumbers->setValue(playerNumbers->value() + 1);
  numOfPlayers++;
  
}

void StartDialog::onAddPlayer(int value)
{
  playerNum->setText(QString("Number of Players: %1").arg(value)); 
  
  if(value > playerList->count()) //add players
    {
      this->addPlayer();
      return;
    }
  
  if(value < playerList->count())
    {
      this->removePlayer();
      return;
    }
}

void StartDialog::addPlayer()
{
  
  QColor hColor = playerColors[numOfPlayers];
  QPixmap tinyColor(16, 16);
  tinyColor.fill(hColor);
  
  playerList->addItem(new QListWidgetItem(QIcon(tinyColor), QString("Comp%1").arg(numOfPlayers)));
  //emit addHumanPlayer(hName, hColor);
  numOfPlayers++;
      
 
}

void StartDialog::removePlayer()
{
  delete playerList->takeItem(playerList->count() - 1);
  
  numOfPlayers--;
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
}

