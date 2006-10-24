#include "SpaceMap.h"

#include <iostream>
using namespace std;

SpaceMap::SpaceMap(QWidget* parent)
    :QTableWidget(16,16,parent)
{
    
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
    this->setMinimumSize(600, 600);
    //    this->resizeRowsToContents();
    //this->resizeColumnsToContents();

    this->setMouseTracking(true);
    
    connect(this, SIGNAL(cellPressed(int,int)), this, SLOT(onSpacePressed(int,int)));
    connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(onSpaceEntered(int,int)));

}

void SpaceMap::mouseMoveEvent(QMouseEvent* event)
{
  int col = this->columnAt(event->pos().x());
  int row = this->rowAt(event->pos().y());
  //cout<<"col "<<col<<" row "<<row<<endl;
  this->onSpaceEntered(row, col);
}

void SpaceMap::onSpacePressed(int row, int column)
{
  cout <<"Pressed" <<row<<" "<<column<<endl;
  if(this->cellWidget(row, column) != NULL)
    {
      this->cellWidget(row, column)->update();

    }
  else
    {
      return;
    }

}

void SpaceMap::onSpaceEntered(int row, int column)
{
  //cout<<"Entered "<<row<<" "<<column<<endl;
  if((row >= 0 & column >= 0) && this->cellWidget(row, column) != NULL)
    {
      emit overPlanet(((Planet*)this->cellWidget(row, column)));
    }

}

void SpaceMap::placePlanet(Planet* planet, int row, int column)
{
  this->setCellWidget(row, column, planet);
  //this->cellWidget(row, column)->update();
}

void SpaceMap::paintEvent(QPaintEvent* event)
{
  QTableWidget::paintEvent(event);
  //cout<<"SDSDSDSDS"<<endl;

}


SpaceMap::~SpaceMap()
{
}
