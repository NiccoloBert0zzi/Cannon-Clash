#include "Entity.h"
#include "Geometry.h"
#include "Lib.h"
using namespace glm;

Enemy::Enemy() : Entity(Type::ENEMY)
{
	this->setAlive(true);
}

void Enemy::build()
{
	float border_space = 0.4f * 25.0f;
	this->createPolygonalShape(createCannonBall(0.6f, 0.3f, 100), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Genera casualmente un valore tra 0 e 3 per decidere il lato del bordo da cui partire
	int side = rand() % 4;  // 0 per il bordo superiore, 1 per il bordo destro, 2 per il bordo inferiore, 3 per il bordo sinistro

	// Genera coordinate casuali sul bordo dello schermo in base al lato scelto
	float randomX{}, randomY{};
	switch (side) {
	case 0:  // Bordo superiore
		randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * width;
		randomY = height;
		break;
	case 1:  // Bordo destro
		randomX = width;
		randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * height;
		break;
	case 2:  // Bordo inferiore
		randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * width;
		randomY = 0.0f;
		break;
	case 3:  // Bordo sinistro
		randomX = 0.0f;
		randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * height;
		break;
	}

	// Applica le nuove coordinate al nemico
	this->setXShiftValue(randomX);
	this->setYShiftValue(randomY);

}

void Enemy::updatePosition()
{
	// Calcoliamo la posizione del centro dello schermo
	float centerX = width / 2;
	float centerY = height / 2;

	// Calcoliamo la differenza tra la posizione attuale del nemico e il centro dello schermo
	float deltaX = centerX - this->getXShiftValue();
	float deltaY = centerY - this->getYShiftValue();

	// Calcoliamo l'angolo tra il nemico e il centro dello schermo
	float angleToCenter = atan2(deltaY, deltaX); // In radianti

	// Calcoliamo i movimenti del nemico utilizzando l'angolo verso il centro
	float speed = DEFAULT_BULLET_SPEED - 2.0f; // Imposta la velocità desiderata
	float xMovement = speed * cos(angleToCenter);
	float yMovement = speed * sin(angleToCenter);

	// Applichiamo i movimenti al nemico
	this->setXShiftValue(this->getXShiftValue() + xMovement);
	this->setYShiftValue(this->getYShiftValue() + yMovement);
}
void Enemy::checkCollisionWithPlayer()
{
	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == Type::PLAYER) {
				Player* player = dynamic_cast<Player*>(entity);
				if (this->isCollided(player->getWheel())) {
					player->decreaseHearts();
					this->setAlive(false);
				}
				// Controlla se il nemico è stato colpito da un proiettile del giocatore
				if (this->isAlive()) {
					for (Bullet* bullet : *player->getBullets()) {
						if (this->isCollided(bullet)) {
							player->increaseScore();
							this->setAlive(false);
							bullet->setAlive(false);
						}
					}
				}
			}
		}
	}
}