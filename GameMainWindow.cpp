#include "GameMainWindow.h"


GameMainWindow::GameMainWindow()
:QMainWindow()
{
  //this->setGeometry(0, 0, 200, 200);
   
  this->setupActions();
  this->setupToolBar();
  this->setupMenus();
    
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
}

void GameMainWindow::newGame()
{
  startDialog = new StartDialog(this);
  gameController = new GameController();
  this->setupConnections();

  if(startDialog->exec() == QDialog::Accepted)
    {
      gameBoard = new GameBoard(this);
        connect(gameController, SIGNAL(triggerPlanetLocate(Planet*, int, int)), gameBoard, SLOT(onAddPlanet(Planet*, int, int)));
	gameController->onStartGame();
      this->setCentralWidget(gameBoard);

      
    }
  else
    {
      delete gameController;
    }
}
