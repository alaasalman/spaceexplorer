#ifndef GAME_MAIN_WINDOW_H
#define GAME_MAIN_WINDOW_H

#include <QtGui>
#include <QAction>
#include "GameBoard.h"
#include "GameController.h"
#include "StartDialog.h"

class GameMainWindow : public QMainWindow
{
  Q_OBJECT;
  
 public:
  GameMainWindow();
  ~GameMainWindow();

 private:
  void setupActions();
  void setupToolBar();
  void setupMenus();
  void setupConnections();

  public slots:
    void newGame();

 private:
  GameBoard* gameBoard;
  GameController* gameController;
  StartDialog* startDialog;
  QAction* startAction;
  QAction* endAction;
  QAction* exitAction;
  QAction* fleetAction;
  QToolBar* toolBar;
  QMenu* gameMenu;
  
};

#endif
