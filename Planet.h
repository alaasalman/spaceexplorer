#ifndef PLANET_H_
#define PLANET_H_

#include <QtGui>

class Planet : public QWidget
{
  Q_OBJECT;
  
 public:
  Planet();
  ~Planet();
  void paintEvent(QPaintEvent*);
  QString getName();
  QString getOwner();
  int getShips();
  int getProduction();
  double getKillPercent();
  void setName(QString);
  void setOwner(QString);
  void setShips(int);
  void setProduction(int);
  void setKillPercent(double);

  
 private:
  QPixmap* pixie;
  QString name;
  QString owner;
  int ships;
  int production;
  double killpercent;
  
    
};

#endif
