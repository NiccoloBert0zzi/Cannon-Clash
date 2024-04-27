#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;


typedef struct {
	GLuint VAO;
	GLuint VBO_V;
	GLuint VBO_C;
	GLuint EBOindexes;
	int nTriangles;
	vector<vec3> vertices;
	vector<vec4> colors;
	vector<vec3> cpCoordinates;	// Coordinate dei punti di controllo
	vector<vec4> cpColors;		// Colori dei punti di controllo
	int nVertices;				// Numero massimo di punti in cui viene disegnata la curve
	int nCP;					// Numero massimo di punti di controllo (punti di interpolazione)
	mat4 model;					// Matrice di modellazione: traslazione * rotazione * scala
	float shiftValue;			// Valore di traslazione
	float scaleValue;			// Valore di scalatura
	float rotationValue;		// Valore di rotazione
} Shape;

typedef struct
{
	float x;
	float y;
	float z;
} Vertex;

#define MAX_DATA 1000	// Numero massimo di vertici da poter memorizzare
#define PI 3.14159265358979323846
static int xOffset_heart_build = 0;

#pragma once
 vector<vec3> createRectangle(float width, float height);
 vector<vec3> createPlayerCockpit(float width, float height);
 vector<vec3> createHearth(float rx, float ry, int precision);
 vector<vec3> createCircle(float rx, float ry, int precision);
 vector<vec3> createCannonBall(float outerRadius, float innerRadius, int precision);
 void create_shape_from_file(char* fileName, Shape* shape, Shape* d);
 vector<vec3> readPolygonVertices(char* fileName);
