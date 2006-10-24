#ifndef START_DIALOG_H_
#define START_DIALOG_H_

#include <QtGui>


class StartDialog : public QDialog
{
  Q_OBJECT;

 public:
  StartDialog(QWidget*);
  ~StartDialog();
  void addPlayer();
  void removePlayer();

  public slots:
    void onAddHumanPlayer();
  void onAddPlayer(int);

 signals:
  void addHumanPlayer(QString, QColor);
  
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
};

#endif
