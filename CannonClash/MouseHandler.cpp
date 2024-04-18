#include "Mouse_Handler.h"
#include <math.h>


void mouseMovement(int x, int y)
{
	Entity* entity = Entity::getEntityByType(Type::PLAYER);
	if (entity != NULL) {
		Player* player = dynamic_cast<Player*>(entity);
		float m = ((float)(height - y) - player->getYShiftValue()) / ((float)x - player->getXShiftValue());
		float angle = degrees(atan(m));
		if ((float)height - y > player->getYShiftValue() && x < player->getXShiftValue())
			angle = 180.0f + angle;
		else if ((float)height - y < player->getYShiftValue() && x < player->getXShiftValue())
			angle += 180.0f;
		else if ((float)height - y < player->getYShiftValue() && x > player->getXShiftValue())
			angle = 360.0f + angle;
		else if (angle == 0.0f && (float)x < player->getXShiftValue())
			angle = 180.0f;
		float xShift = cos(radians(angle)) * player->getCannon()->getXScaleValue();
		float yShift = sin(radians(angle)) * player->getCannon()->getYScaleValue();
		player->getCannon()->setXShiftValue(player->getXShiftValue() + xShift);
		player->getCannon()->setYShiftValue(player->getYShiftValue() + yShift);
		player->getCannon()->setRotationValue(-90.0f + angle);
	}
}
