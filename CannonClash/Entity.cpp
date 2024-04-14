#include "Entity.h"
#include "VAO_Handler.h"
#include "Lib.h"
#include <vector>
using namespace glm;


#define DEFAULT_SIZE 25.0f
#define DEFAULT_PROJECTILE_SPEED 10.0f
#define P_VAL 100
#define PI 3.14159265358979323846
static int xOffset = 0;
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

Hitbox Entity::getHitboxWorldCoordinates()
{
	float xBottom = (float)width / 2 + hitbox.cornerBot.x * xScaleValue + xShiftValue;
	float yBottom = (float)height / 2 + hitbox.cornerBot.y * yScaleValue + yShiftValue;
	float xTop = (float)width / 2 + hitbox.cornerTop.x * xScaleValue + xShiftValue;
	float yTop = (float)height / 2 + hitbox.cornerTop.y * yScaleValue + yShiftValue;
	return { vec3(xBottom, yBottom, 0.0f), vec3(xTop, yTop, 0.0f) };
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

#pragma endregion

#pragma region Heart
Hearth::Hearth() : Entity(Type::HEART) {
	alive = true;
}

void Hearth::build(float size)
{
	float border_space = 0.4f * 25.0f;
	vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	this->createPolygonalShape(createHearth(size, size, 100), red, red);
	this->setYShiftValue((float)height - this->getEntityHeight() / 2 * this->getYScaleValue() - border_space);
	this->setXShiftValue((float)width-(border_space + this->getEntityWidth() / 2 * this->getXScaleValue() + xOffset * (this->getEntityWidth() * this->getXScaleValue() + 5.0f)));
	xOffset++;
}

vector<vec3> Hearth::createHearth(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		float x = rx * 16 * pow(sin(theta_i), 3);
		float y = ry * (13 * cos(theta_i) - 5 * cos(2 * theta_i) - 2 * cos(3 * theta_i) - cos(4 * theta_i));
		vertices.push_back(vec3(x, y, 0.0f));
	}
	return vertices;
}

void Hearth::setAlive(bool value)
{
	//TODO check collision
	alive = value;
}

bool Hearth::isAlive()
{
	return false;
}
#pragma endregion

#pragma region Player
Player::Player() : Entity(Type::PLAYER)
{

	score = 0;
	alive = true;
	cannon = new Entity(Type::CANNON);
	wheel = new Entity(Type::WHEEL);

}
void Player::build()
{
	vec4 cannon_wheel = vec4(0.58f, 0.39f, 0.03f, 1.0f);
	vec4 white_center = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	wheel->createPolygonalShape(createCircle(1.5f, 1.5f, 100), cannon_wheel, white_center);
	cannon->createPolygonalShape(createRectangle(1.5f, 1.5f), cannon_wheel, white_center);
	this->setXShiftValue(width / 2);
	this->setYShiftValue(height / 2);
}

void Player::setScore(int value)
{
	score = value;
}

void Player::setAlive(bool value)
{
	alive = value;
}

int Player::getScore()
{
	return score;
}

bool Player::isAlive()
{
	return alive;
}

Entity* Player::getCannon()
{
	return cannon;
}

Entity* Player::getWheel()
{
	return wheel;
}

vector<vec3> Player::createCircle(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		vertices.push_back(vec3(rx * cos(theta_i), ry * sin(theta_i), 0.0f));
	}
	return vertices;
}
vector<vec3> Player::createRectangle(float width, float height)
{
	vector<vec3> vertices;
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	return vertices;
}
#pragma endregion


