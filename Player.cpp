#include "Player.h"


Player::Player()
{
}

Player::Player(QString initialName, QColor initialColor)
{
  name = initialName;
  color = initialColor;
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
