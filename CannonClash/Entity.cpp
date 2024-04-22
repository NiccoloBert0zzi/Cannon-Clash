#include "Entity.h"
#include "VAO_Handler.h"
#include "Geometry.h"
#include "Lib.h"
#include <vector>
using namespace glm;


#define DEFAULT_SIZE 25.0f
#define DEFAULT_BULLET_SPEED 10.0f
#define P_VAL 100


#pragma region Entity

Entity::Entity(Type t)
{
	backgroundChecker = false;
	xShiftValue = 0.0f;
	yShiftValue = 0.0f;
	xScaleValue = DEFAULT_SIZE;
	yScaleValue = DEFAULT_SIZE;
	rotationValue = 0.0f;
	type = t;
	alive = true;
	model = mat4(1.0f);
	VAO = 0;
	VBO_G = 0;
	VBO_C = 0;
	hitbox = { vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f) };
}

Entity* Entity::getEntityByType(Type type)
{
	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == type) {
				return entity;
			}
		}
	}
	return NULL;
}

bool Entity::isCollided(Entity entity)
{
	Hitbox thisHitbox = this->getHitbox();
	Hitbox otherHitbox = entity.getHitbox();

	// Verifica se le hitbox si sovrappongono lungo l'asse x
	bool xOverlap = (thisHitbox.cornerBot.x < otherHitbox.cornerTop.x) && (thisHitbox.cornerTop.x > otherHitbox.cornerBot.x);

	// Verifica se le hitbox si sovrappongono lungo l'asse y
	bool yOverlap = (thisHitbox.cornerBot.y < otherHitbox.cornerTop.y) && (thisHitbox.cornerTop.y > otherHitbox.cornerBot.y);

	// Le hitbox si toccano se si sovrappongono sia lungo l'asse x che lungo l'asse y
	return xOverlap && yOverlap;
}



void Entity::createPolygonalShape(vector<vec3> polygonVertices, vec4 color1, vec4 color2)
{
	vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
	colors.push_back(color2);
	float xMin = polygonVertices[0].x;
	float yMin = polygonVertices[0].y;
	float xMax = polygonVertices[0].x;
	float yMax = polygonVertices[0].y;
	for (vec3 vertex : polygonVertices) {
		vertices.push_back(vec3(vertex.x, vertex.y, 0.0f));
		colors.push_back(color1);
		if (vertex.x < xMin)
			xMin = vertex.x;
		else if (vertex.x > xMax)
			xMax = vertex.x;
		if (vertex.y < yMin)
			yMin = vertex.y;
		else if (vertex.y > yMax)
			yMax = vertex.y;
	}
	hitbox.cornerBot = vec3(xMin, yMin, 0.0f);
	hitbox.cornerTop = vec3(xMax, yMax, 0.0f);
}

void Entity::initVAO()
{
	INIT_VAO(this);
}

void Entity::updateVAO()
{
	UPDATE_VAO(this);
}

GLuint* Entity::getVAO()
{
	return &VAO;
}

GLuint* Entity::getVBO_G()
{
	return &VBO_G;
}

GLuint* Entity::getVBO_C()
{
	return &VBO_C;
}

vector<vec3>* Entity::getVertices()
{
	return &vertices;
}

vector<vec4>* Entity::getVerticesColors()
{
	return &colors;
}

int Entity::getNV()
{
	return vertices.size();
}

mat4* Entity::getModel()
{
	return &model;
}

float Entity::getXShiftValue()
{
	return xShiftValue;
}

float Entity::getYShiftValue()
{
	return yShiftValue;
}

float Entity::getXScaleValue()
{
	return xScaleValue;
}

float Entity::getYScaleValue()
{
	return yScaleValue;
}

float Entity::getRotationValue()
{
	return rotationValue;
}

void Entity::setXShiftValue(float value)
{
	xShiftValue = value;
}

void Entity::setYShiftValue(float value)
{
	yShiftValue = value;
}

void Entity::setXScaleValue(float value)
{
	xScaleValue = value;
}

void Entity::setYScaleValue(float value)
{
	yScaleValue = value;
}

void Entity::setRotationValue(float value)
{
	rotationValue = value;
}

Hitbox Entity::getHitbox()
{
	return hitbox;
}

vec3 Entity::getMidPoint()
{
	float x = (hitbox.cornerBot.x + hitbox.cornerTop.x) / 2;
	float y = (hitbox.cornerBot.y + hitbox.cornerTop.y) / 2;
	return vec3(x, y, 0.0f);
}

float Entity::getEntityWidth()
{
	return hitbox.cornerTop.x - hitbox.cornerBot.x;
}

float Entity::getEntityHeight()
{
	return hitbox.cornerTop.y - hitbox.cornerBot.y;
}

void Entity::updateHitbox(float newX, float newY)
{
	// Aggiorna l'hitbox in base alla nuova posizione
	float xMin = newX;
	float yMin = newY;
	float xMax = newX;
	float yMax = newY;
	for (vec3 vertex : vertices) {
		if (vertex.x < xMin)
			xMin = vertex.x;
		else if (vertex.x > xMax)
			xMax = vertex.x;
		if (vertex.y < yMin)
			yMin = vertex.y;
		else if (vertex.y > yMax)
			yMax = vertex.y;
	}
	hitbox.cornerBot = vec3(xMin, yMin, 0.0f);
	hitbox.cornerTop = vec3(xMax, yMax, 0.0f);
}

bool Entity::isBackground()
{
	return backgroundChecker;
}

void Entity::changePane()
{
	backgroundChecker = !backgroundChecker;
}

void Entity::build()
{
	this->createPolygonalShape(createRectangle(2.0f, 2.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->setXScaleValue((float)width);
	this->setYScaleValue((float)height);
	this->setXShiftValue((float)width / 2);
	this->setYShiftValue((float)height / 2);
}

Type Entity::getType()
{
	return type;
}
void Entity::setAlive(bool value)
{
	alive = value;
}

bool Entity::isAlive()
{
	return alive;
}
#pragma endregion

#pragma region Heart
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

#pragma endregion

#pragma region Bullet

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
	this->updateHitbox(this->getXShiftValue(), this->getYShiftValue());
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

		// Aggiorna le hitbox del proiettile
		this->updateHitbox(newX, newY);
		return true;
	}
	return false;
}

#pragma endregion

#pragma region Player
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

//bullets
void Player::shoot()
{
	float x = cannon->getXShiftValue();
	float y = cannon->getYShiftValue();
	Bullet* bullet = new Bullet();
	bullet->build(x, y, cannon->getRotationValue());

	bullet->initVAO();
	bullets->push_back(bullet);
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
	}else {
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
#pragma endregion

#pragma region Enemy

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
	float randomX, randomY;
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
	this->updateHitbox(this->getXShiftValue(), this->getYShiftValue());

}

void Enemy::updatePosition()
{
	// Calcoliamo la posizione del centro dello schermo
	float centerX = width / 2;
	float centerY = height / 2;

	// Calcoliamo la differenza tra la posizione attuale del nemico e il centro dello schermo
	float deltaX = centerX - getXShiftValue();
	float deltaY = centerY - getYShiftValue();

	// Calcoliamo l'angolo tra il nemico e il centro dello schermo
	float angleToCenter = atan2(deltaY, deltaX); // In radianti

	// Calcoliamo i movimenti del nemico utilizzando l'angolo verso il centro
	float speed = DEFAULT_BULLET_SPEED - 2.0f; // Imposta la velocità desiderata
	float xMovement = speed * cos(angleToCenter);
	float yMovement = speed * sin(angleToCenter);

	// Applichiamo i movimenti al nemico
	setXShiftValue(getXShiftValue() + xMovement);
	setYShiftValue(getYShiftValue() + yMovement);
	this->updateHitbox(this->getXShiftValue(), this->getYShiftValue());
}
void Enemy::checkCollisionWithPlayer()
{
	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == Type::PLAYER) {
				Player* player = dynamic_cast<Player*>(entity);
				if (! this->isCollided(*player->getWheel())) {
					player->decreaseHearts();
					this->setAlive(false);
				}
			}
		}
	}
}
#pragma endregion

