#include "Entity.h"
#include "VAO_Handler.h"
#include "Geometry.h"
#include "Lib.h"
using namespace glm;

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

bool Entity::isCollided(Entity *entity)
{
	Hitbox hitbox1 = this->getHitboxWorldCoordinates();
	Hitbox hitbox2 = entity->getHitboxWorldCoordinates();
	if (hitbox1.cornerBot.x <= hitbox2.cornerTop.x
		&& hitbox1.cornerTop.x >= hitbox2.cornerBot.x
		&& hitbox1.cornerBot.y <= hitbox2.cornerTop.y
		&& hitbox1.cornerTop.y >= hitbox2.cornerBot.y) {
		return true;
	}
	return false;
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
	hitbox.cornerBot = vec4(xMin, yMin, 0.0f, 1.0f);
	hitbox.cornerTop = vec4(xMax, yMax, 0.0f, 1.0f);

	vertices.push_back(vec3(xMin, yMin, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(xMax, yMin, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(xMax, yMax, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(xMin, yMin, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(xMin, yMax, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	vertices.push_back(vec3(xMax, yMax, 0.0));
	colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
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

Hitbox Entity::getHitboxWorldCoordinates()
{
	float xBottom = (float)width / 2 + hitbox.cornerBot.x * xScaleValue + xShiftValue;
	float yBottom = (float)height / 2 + hitbox.cornerBot.y * yScaleValue + yShiftValue;
	float xTop = (float)width / 2 + hitbox.cornerTop.x * xScaleValue + xShiftValue;
	float yTop = (float)height / 2 + hitbox.cornerTop.y * yScaleValue + yShiftValue;
	return { vec3(xBottom, yBottom, 0.0f), vec3(xTop, yTop, 0.0f) };
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

	mat4 modelMatrix = *this->getModel();
	// Moltiplicare la matrice di trasformazione per il vettore cornerBot
	vec4 cornerBotTransformed = modelMatrix * vec4(this->hitbox.cornerBot, 1.0f);
	vec4 cornerTopTransformed = modelMatrix * vec4(this->hitbox.cornerTop, 1.0f);

	// Assegnare il risultato alla proprietà cornerBot della hitbox
	this->hitbox.cornerBot = vec3(cornerBotTransformed);
	this->hitbox.cornerTop = vec3(cornerTopTransformed);

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
