#include "Entity.h"
#include "Geometry.h"

Player::Player() : Entity(Type::PLAYER)
{
	score = 0;
	cannon = new Entity(Type::CANNON);
	wheel = new Entity(Type::WHEEL);
	bullets = new vector<Bullet*>();
	hearts = new vector<Heart*>();
	this->setAlive(true);
}
void Player::build()
{
	//heart
	for (int i = 0; i < 3; i++) {
		Heart* heart = new Heart();
		heart->build(0.04f);
		hearts->push_back(heart);
	}

	//wheel
	vec4 cannon_wheel_color = vec4(0.58f, 0.39f, 0.03f, 1.0f);
	vec4 white_center_color = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	wheel->createPolygonalShape(createCircle(1.5f, 1.5f, 100), cannon_wheel_color, white_center_color);
	wheel->setXShiftValue(width / 2);
	wheel->setYShiftValue(height / 2);
	wheel->updateHitbox(wheel->getXShiftValue(), wheel->getYShiftValue());
	//cannon
	vec4 cannon_color = vec4(0.5f, 0.5f, 0.5f, 1.0f); // Grigio medio per il cannone
	cannon->createPolygonalShape(createRectangle(1.5f, 3.0f), cannon_color, cannon_color);
	cannon->setXShiftValue(width / 2);
	cannon->setYShiftValue(height / 2);
	cannon->updateHitbox(cannon->getXShiftValue(), cannon->getYShiftValue());
	//set player in center for movement correctly
	this->setXShiftValue(width / 2);
	this->setYShiftValue(height / 2);
	this->updateHitbox(this->getXShiftValue(), this->getYShiftValue());
}

void Player::setScore(int value)
{
	score = value;
}

int Player::getScore()
{
	return score;
}

void Player::increaseScore()
{
	score += 100;
}

//bullets
void Player::shoot()
{
	if (this->isAlive()) {
		float x = cannon->getXShiftValue();
		float y = cannon->getYShiftValue();
		Bullet* bullet = new Bullet();
		bullet->build(x, y, cannon->getRotationValue());

		bullet->initVAO();
		bullets->push_back(bullet);
	}
}
vector<Bullet*>* Player::getBullets()
{
	return bullets;
}
void Player::initBullets()
{
	for (Bullet* bullet : *bullets) {
		bullet->initVAO();
	}
}
void Player::updateBullets()
{
	for (size_t i = 0; i < bullets->size(); ++i) {
		Bullet* bullet = (*bullets)[i];
		if (!bullet->updatePosition()) {
			removeBullet(i);
		}
		else {
			bullet->updateVAO();
		}
	}
}

void Player::removeBullet(int index)
{
	// Controlla che l'indice sia valido
	if (index < 0 || index >= bullets->size()) {
		// Indice non valido, esci dalla funzione
		return;
	}

	// Dealloca il proiettile all'indice specificato
	delete (*bullets)[index];

	// Sposta gli elementi successivi nel vettore
	for (size_t i = index; i < bullets->size() - 1; ++i) {
		(*bullets)[i] = (*bullets)[i + 1];
	}

	// Rimuovi l'ultimo elemento dal vettore
	bullets->pop_back();
}


//hearts
vector<Heart*>* Player::getHearts()
{
	return hearts;
}
void Player::initHearts()
{
	for (Heart* heart : *hearts) {
		heart->initVAO();
	}
}
void Player::updateHearts()
{
	for (Heart* heart : *hearts) {
		heart->updateVAO();
	}
}

void Player::decreaseHearts() {
	// Diminuisci il numero di cuori
	if (!hearts->empty()) {
		hearts->pop_back();
		if (hearts->empty())
			this->setAlive(false);
	}
}

//player parts
Entity* Player::getCannon()
{
	return cannon;
}
Entity* Player::getWheel()
{
	return wheel;
}
void Player::updatePlayerPartsVAO()
{
	wheel->updateVAO();
	cannon->updateVAO();
}
void Player::initPlayerPartsVAO()
{
	wheel->initVAO();
	cannon->initVAO();
}