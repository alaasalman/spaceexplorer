#ifndef START_DIALOG_H_
#define START_DIALOG_H_

#include <QtGui>


class StartDialog : public QDialog
{
  Q_OBJECT;

 public:
  StartDialog(QWidget*);
  ~StartDialog();

 private:
  void onAddComputerPlayer();
  void removePlayer();
  
  
  private slots:
    void onAddHumanPlayer();
  void onChangePlayer(int);
  void onChangeTurns(int);
  void onChangeNeutralPlanet(int);
  void onFinishedDialog();

 signals:
  void addHumanPlayer(QString, QColor);
  void changeTurnsNum(int);
  void changeNeutralPlanetsNum(int);
  void addComputerPlayer(QString, QColor);
  
 private:
  QListWidget* playerList;
  QLineEdit* humanName;
  QPushButton* addHuman;
  QPushButton* okButton;
  QPushButton* cancelButton;
  int numOfPlayers;
  QColor playerColors[10];
  QSlider* playerNumbers;
  QLabel* playerNum;
  QLabel* neutralPlanetNum;
  QSlider* neutralPlanetNumbers;
  QLabel* turnsNum;
  QSlider* turnsNumber;
};

#endif
