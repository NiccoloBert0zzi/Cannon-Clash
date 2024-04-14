#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;

extern int width;
extern int height;

typedef struct {
	vec3 cornerBot;
	vec3 cornerTop;
} Hitbox;

enum Type
{
	BACKGROUND,
	HEART,
	PLAYER,
	CANNON,
	WHEEL
};

static vector<vec3> createRectangle(float width, float height) {
	vector<vec3> vertices;
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	return vertices;
}

class Entity {

private:
	Hitbox hitbox;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	vector<vec3> vertices;
	vector<vec4> colors;
	mat4 model;					// Matrice di modellazione: traslazione * rotazione * scala
	float xShiftValue;			// Valore di traslazione per la x
	float yShiftValue;			// Valore di traslazione per la y
	float xScaleValue;			// Valore di scalatura per la x
	float yScaleValue;			// Valore di scalatura per la y
	float rotationValue;		// Valore di rotazione
	bool backgroundChecker;	// true se fa parte dello sfondo, false altrimenti
	Type type;

public:
	Entity(Type t);
	virtual ~Entity() {} // Funzione virtuale di distruttore
	void createPolygonalShape(vector<vec3> polygonVertices, vec4 color1, vec4 color2);
	void createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2);
	void initVAO();
	void updateVAO();
	GLuint* getVAO();
	GLuint* getVBO_G();
	GLuint* getVBO_C();
	vector<vec3>* getVertices();
	vector<vec4>* getVerticesColors();
	int getNV();
	mat4* getModel();
	float getXShiftValue();
	float getYShiftValue();
	float getXScaleValue();
	float getYScaleValue();
	float getRotationValue();
	void setXShiftValue(float value);
	void setYShiftValue(float value);
	void setXScaleValue(float value);
	void setYScaleValue(float value);
	void setRotationValue(float value);
	Hitbox getHitbox();
	vec3 getMidPoint();
	float getEntityWidth();
	float getEntityHeight();
	Hitbox getHitboxWorldCoordinates();
	bool isBackground();
	void changePane();
	void build();
	Type getType();
};

class Hearth :public Entity {

	private:
		bool alive;
		vector<vec3> createHearth(float rx, float ry, int precision);

	public:
		Hearth();
		void build(float size);
		void setAlive(bool value);
		bool isAlive();
};

class Player :public Entity {

	private:
		int score;
		bool alive;
		Entity* cannon;
		Entity* wheel;
		vector<vec3> createCircle(float rx, float ry, int precision);
		vector<vec3> createRectangle(float width, float height);

	public:
		Player();
		void build();
		void setScore(int value);
		void setAlive(bool value);
		int getScore();
		bool isAlive();
		Entity* getCannon();
		Entity* getWheel();
};