#include "Entity.h"
#include "Geometry.h"

Bullet::Bullet() : Entity(Type::BULLET)
{
	this->setAlive(true);
}

void Bullet::build(float x, float y, float angle)
{
	this->setXShiftValue(x);
	this->setYShiftValue(y);
	xBulletMovement = DEFAULT_BULLET_SPEED * cos(radians(90.0f + angle));
	yBulletMovement = DEFAULT_BULLET_SPEED * sin(radians(90.0f + angle));
	this->setXScaleValue((float)DEFAULT_SIZE * 2 / 3);
	this->setYScaleValue((float)DEFAULT_SIZE * 2 / 3);
	this->setRotationValue(angle);
	this->createPolygonalShape(createCannonBall(0.6f, 0.3f, 100), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

bool Bullet::updatePosition()
{
	float newX = this->getXShiftValue() + xBulletMovement;
	float newY = this->getYShiftValue() + yBulletMovement;

	// Controlla che il proiettile non esca dallo schermo
	if (newX >= 0 && newX <= width && newY >= 0 && newY <= height) {
		// Il proiettile è all'interno dello schermo, aggiorna la posizione
		this->setXShiftValue(newX);
		this->setYShiftValue(newY);
		return true;
	}
	return false;
}
