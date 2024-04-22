#include "Entity.h"
#include "Geometry.h"

Heart::Heart() : Entity(Type::HEART) {
	this->setAlive(true);
}

void Heart::build(float size)
{
	float border_space = 0.4f * 25.0f;
	vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	this->createPolygonalShape(createHearth(size, size, 100), red, red);
	this->setYShiftValue((float)height - this->getEntityHeight() / 2 * this->getYScaleValue() - border_space);
	this->setXShiftValue((float)width - (border_space + this->getEntityWidth() / 2 * this->getXScaleValue() + xOffset_heart_build * (this->getEntityWidth() * this->getXScaleValue() + 5.0f)));
	this->updateHitbox(this->getXShiftValue(), this->getYShiftValue());
	xOffset_heart_build++;
}
