#ifndef PLAYER_H_
#define PLAYER_H_

#include <QtGui>


class Player : public QObject
{
  Q_OBJECT;

 public:
  Player();
  Player(QString, QColor, bool);
  ~Player();
  QString getName();
  void setName(QString);
  QColor getColor();
  void setColor(QColor);
  bool getComputer();
  void setComputer(bool);

 private:
  QString name;
  QColor color;
  bool computer;

};

#endif
