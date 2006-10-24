#ifndef PLAYER_H_
#define PLAYER_H_

#include <QtGui>


class Player : public QObject
{
  Q_OBJECT;

 public:
  Player();
  Player(QString, QColor);
  ~Player();
  QString getName();
  void setName(QString);
  QColor getColor();
  void setColor(QColor);

 private:
  QString name;
  QColor color;

};

#endif
