#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;

#define PI 3.14159265358979323846
static int xOffset_heart_build = 0;

#pragma once
 vector<vec3> createRectangle(float width, float height);
 vector<vec3> createPlayerCockpit(float width, float height);
 vector<vec3> createHearth(float rx, float ry, int precision);
 vector<vec3> createCircle(float rx, float ry, int precision);
