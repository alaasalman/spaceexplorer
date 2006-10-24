#include "Player.h"


Player::Player()
{
}

Player::Player(QString initialName, QColor initialColor, bool computerPlayer)
{
  name = initialName;
  color = initialColor;
  this->computer = computerPlayer;
}

Player::~Player()
{
}

QString Player::getName()
{
  return name;
}

void Player::setName(QString newName)
{
  name = newName;
}

QColor Player::getColor()
{
  return color;
}

void Player::setColor(QColor newColor)
{
  color = newColor;
}

bool Player::getComputer()
{
  return this->computer;
}

void Player::setComputer(bool newComputer)
{
  this->computer = newComputer;
}
