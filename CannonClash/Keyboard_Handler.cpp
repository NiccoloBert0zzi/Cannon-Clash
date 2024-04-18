#include "Keyboard_Handler.h"

void keyboardClicked(unsigned char key, int x, int y)
{
	Entity* entity = Entity::getEntityByType(Type::PLAYER);
	if (entity != NULL) {
		Player* player = dynamic_cast<Player*>(entity);
		switch (key)
		{
		case ' ':
			player->shoot();
			break;
		default:
			break;
		}
	}
}

