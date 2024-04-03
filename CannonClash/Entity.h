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

class Entity {

public:
	Hitbox hitbox;
	GLuint VAO;
	GLuint VBO_V;
	GLuint VBO_C;
	vector<vec3> vertices;
	vector<vec4> colors;
	mat4 model;					// Matrice di modellazione: traslazione * rotazione * scala
	float xShiftValue;			// Valore di traslazione per la x
	float yShiftValue;			// Valore di traslazione per la y
	float xScaleValue;			// Valore di scalatura per la x
	float yScaleValue;			// Valore di scalatura per la y
	float rotationValue;		// Valore di rotazione
	bool backgroundComponent;	// true se fa parte dello sfondo, false altrimenti

public:
	Entity();
	void createPolygonalShape(vector<vec3> polygonVertices, vec4 color1, vec4 color2);
	void createHermiteShape(vector<vec3> controlPoints, vec3 center, vec4 color1, vec4 color2);
	void initVAO();
	void updateVAO();
	GLuint* getVAO();
	GLuint* getVerticesVBO();
	GLuint* getColorsVBO();
	vector<vec3>* getVertices();
	vector<vec4>* getVerticesColors();
	int getNumberOfVertices();
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
	float getWidth();
	float getHeight();
	Hitbox getHitboxWorldCoordinates();
	bool isBackgroundComponent();
	void changePane();

};