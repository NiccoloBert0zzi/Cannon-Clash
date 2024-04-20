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
	//TODO check collision
	alive = value;
}

bool Entity::isAlive()
{
	return false;
}
#pragma endregion

#pragma region Heart
Heart::Heart() : Entity(Type::HEART) {
	setAlive(true);
}

void Heart::build(float size)
{
	float border_space = 0.4f * 25.0f;
	vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	this->createPolygonalShape(createHearth(size, size, 100), red, red);
	this->setYShiftValue((float)height - this->getEntityHeight() / 2 * this->getYScaleValue() - border_space);
	this->setXShiftValue((float)width-(border_space + this->getEntityWidth() / 2 * this->getXScaleValue() + xOffset_heart_build * (this->getEntityWidth() * this->getXScaleValue() + 5.0f)));
	xOffset_heart_build++;
}

#pragma endregion

#pragma region Bullet

Bullet::Bullet() : Entity(Type::BULLET)
{
	setAlive(true);
}

void Bullet::build(float x, float y, float angle)
{

	float m = tan(radians(angle));
	this->setXShiftValue(x);
	this->setYShiftValue(y);
	xBulletMovement = DEFAULT_BULLET_SPEED * cos(radians(90.0f + angle));
	yBulletMovement = DEFAULT_BULLET_SPEED * sin(radians(90.0f + angle));
	this->setXScaleValue((float)DEFAULT_SIZE * 2 / 3);
	this->setYScaleValue((float)DEFAULT_SIZE * 2 / 3);
	this->setRotationValue(angle);
	this->createPolygonalShape(createHearth(0.04f, 0.04f, 100), vec4(0.0f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f));
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
		updateHitbox(newX, newY);
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
	setAlive(true);
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
	//cannon
	vec4 cannon_color = vec4(0.5f, 0.5f, 0.5f, 1.0f); // Grigio medio per il cannone
	cannon->createPolygonalShape(createRectangle(1.5f, 3.0f), cannon_color, cannon_color);
	cannon->setXShiftValue(width / 2);
	cannon->setYShiftValue(height / 2);
	//set player in center for movement correctly
	this->setXShiftValue(width / 2);
	this->setYShiftValue(height / 2);
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


