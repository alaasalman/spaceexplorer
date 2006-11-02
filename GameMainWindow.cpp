#include "GameMainWindow.h"


GameMainWindow::GameMainWindow()
:QMainWindow()
{
  //this->setGeometry(0, 0, 200, 200);
   
  this->setupActions();
  this->setupToolBar();
  this->setupMenus();
  this->setMinimumSize(800, 800);
  //QLabel mainBckgrnd(this);
  //mainBckgrnd.setGeometry(0, 0, 550, 600);
  //mainBckgrnd.setPixmap(QPixmap("pics/konquest-splash"));
  
    
}

GameMainWindow::~GameMainWindow()
{
  delete gameBoard;
  delete gameController;
}

void GameMainWindow::setupActions()
{
  startAction = new QAction(QIcon("pics/filenew"), tr("&New Game"), this);
  startAction->setEnabled(true);
	
  endAction = new QAction(QIcon("pics/fileclose"), tr("&End Game"), this);
  endAction->setEnabled(false);

  exitAction = new QAction(QIcon("pics/exit"), tr("E&xit"), this);
  exitAction->setEnabled(true);

  connect(startAction, SIGNAL(triggered()), this, SLOT(newGame()));
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


}

void GameMainWindow::setupToolBar()
{
  toolBar = new QToolBar();
  
  toolBar->addAction(startAction);
  toolBar->addAction(endAction); 
  toolBar->addSeparator(); 
  toolBar->addAction(exitAction);

  this->addToolBar(Qt::TopToolBarArea, toolBar);
  toolBar->setMovable(false);
}

void GameMainWindow::setupMenus()
{
  gameMenu = menuBar()->addMenu(tr("&Game"));
  gameMenu->addAction(startAction);
  gameMenu->addSeparator();
  gameMenu->addAction(endAction);
  gameMenu->addSeparator();
  gameMenu->addAction(exitAction);

}

void GameMainWindow::setupConnections()
{

  connect(startAction, SIGNAL(triggered()), gameController, SLOT(onEndGame()));
  connect(startDialog, SIGNAL(addHumanPlayer(QString, QColor)), gameController, SLOT(onAddHumanPlayer(QString, QColor)));
  connect(startDialog, SIGNAL(changeTurnsNum(int)), gameController, SLOT(onChangeTurnsNum(int)));
  connect(startDialog, SIGNAL(changeNeutralPlanetsNum(int)), gameController, SLOT(onChangeNeutralPlanetsNum(int)));
  connect(startDialog, SIGNAL(addComputerPlayer(QString, QColor)), gameController, SLOT(onAddComputerPlayer(QString, QColor)));

}

void GameMainWindow::newGame()
{
  gameController = new GameController();
  startDialog = new StartDialog(this);

  this->setupConnections();

  if(startDialog->exec() == QDialog::Accepted)
    {
      gameBoard = new GameBoard(this);
        connect(gameController, SIGNAL(triggerPlanetLocate(Planet*, int, int)), gameBoard, SLOT(onAddPlanet(Planet*, int, int)));
	connect(gameBoard, SIGNAL(changeTurn()), gameController, SLOT(onChangeTurn()));
	connect(gameController, SIGNAL(displayControl(QString)), gameBoard, SLOT(onDisplayControl(QString)));
	connect(gameController, SIGNAL(displayInfo(QString)), gameBoard, SLOT(onDisplayInfo(QString)));
	gameController->onStartGame();

      this->setCentralWidget(gameBoard);

      
    }
  else
    {
      delete gameController;
    }
}
