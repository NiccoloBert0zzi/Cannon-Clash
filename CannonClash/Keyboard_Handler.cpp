#include "Keyboard_Handler.h"
#include <GL/glut.h>

bool isSpaceKeyPressed = false;

void keyboardPressed(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        if (!isSpaceKeyPressed) // Controlla se il tasto è già stato premuto
        {
            Entity* entity = Entity::getEntityByType(Type::PLAYER);
            if (entity != NULL) {
                Player* player = dynamic_cast<Player*>(entity);
                player->shoot();
            }
            isSpaceKeyPressed = true; // Imposta il flag a true quando il tasto viene premuto
        }
    }
}

void keyboardReleased(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        isSpaceKeyPressed = false; // Imposta il flag a false quando il tasto viene rilasciato
    }
}

