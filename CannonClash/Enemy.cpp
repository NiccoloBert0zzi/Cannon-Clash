#include "Entity.h"
#include "Geometry.h"
#include "VAO_Handler.h"
#include "Lib.h"
using namespace glm;

Enemy::Enemy() : Entity(Type::ENEMY)
{
	this->setAlive(false);
	this->setDead(false);
}

void Enemy::build()
{

	vector<vec3> controlPoints = readPolygonVertices((char*)"slime.txt");



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
	this->setXScaleValue(this->getXScaleValue() * 4.0f);
	this->setYScaleValue(this->getYScaleValue() * 4.0f);

	// Applica le nuove coordinate al nemico
	this->setXShiftValue(randomX);
	this->setYShiftValue(randomY);

	this->createHermiteShape(controlPoints, vec3(0.0f, 0.0f, 0.0f), vec4(0.3f, 0.3f, 0.3f, 1.0f), vec4(0.4f, 0.4f, 0.4f, 1.0f));
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
void Enemy::checkEnemyCollision()
{
	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == Type::PLAYER) {
				Player* player = dynamic_cast<Player*>(entity);
				if (this->isCollided(player->getWheel())) {
					player->decreaseHearts();
					this->setAlive(false);
					this->setDead(true);
				}
				// Controlla se il nemico è stato colpito da un proiettile del giocatore
				if (this->isAlive()) {
					for (Bullet* bullet : *player->getBullets()) {
						if (this->isCollided(bullet)) {
							player->increaseScore();
							this->setAlive(false);
							this->setDead(true);
							bullet->setAlive(false);
						}
					}
				}
			}
		}
	}
}

void Enemy::setDead(bool value)
{
	dead = value;
}

bool Enemy::isDead()
{
	return dead;
}
