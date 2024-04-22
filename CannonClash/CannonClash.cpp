#include <iostream>
#include <fstream>
#include <string>
#include "Lib.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Text_Handler.h"
#include <ft2build.h>
#include <ctime>
#include FT_FREETYPE_H

unsigned int VAO_Text, VBO_Text;

//init
vector<vector<Entity*>*> scene;
vector<Entity*> piano;
//Forma Curva = {}, Poligonale = {}, Derivata = {}, shape = {};

mat4 Projection;
GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

// viewport size
int width = 1280;
int height = 720;

void drawEntity(Entity* entity)
{
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	*entity->getModel() = mat4(1.0);
	*entity->getModel() = translate(*entity->getModel(), vec3(entity->getXShiftValue(), entity->getYShiftValue(), 0.0f));
	*entity->getModel() = scale(*entity->getModel(), vec3(entity->getXScaleValue(), entity->getYScaleValue(), 1.0f));
	*entity->getModel() = rotate(*entity->getModel(), radians(entity->getRotationValue()), vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(*entity->getModel()));
	glUniform2f(locres, width, height);
	if (entity->isBackground())
		glUniform1i(locSceltafs, 1);
	else
		glUniform1i(locSceltafs, 0);
	glUniform1f(loctime, time);
	glBindVertexArray(*entity->getVAO());
	glDrawArrays(GL_TRIANGLE_FAN, 0, entity->getNV());
	glBindVertexArray(0);
}

void drawScene(void)
{
	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (vector<Entity*>* container : scene)
	{
		for (Entity* entity : *container)
		{
			if (entity->isAlive()) {
				if (entity->getType() == Type::PLAYER) {
					Player* player = dynamic_cast<Player*>(entity);
					for (Bullet* bullet : *player->getBullets()) {
						drawEntity(bullet);
					}
					for (Heart* heart : *player->getHearts()) {
						drawEntity(heart);
					}
					drawEntity(player->getWheel());
					drawEntity(player->getCannon());
				}
				drawEntity(entity);
			}
		}
	}
	glutSwapBuffers();
	glUseProgram(Shader::getProgramId());
}

void updateScale(int value) {
	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->isAlive()) {
				if (entity->getType() == Type::PLAYER) {
					Player* player = dynamic_cast<Player*>(entity);
					player->updateHearts();
					player->updateBullets();
					player->updatePlayerPartsVAO();
				}
				else if (entity->getType() == Type::ENEMY) {
					Enemy* enemy = dynamic_cast<Enemy*>(entity);
					enemy->updatePosition();
					enemy->checkCollisionWithPlayer();
				}
				entity->updateVAO();
			}
		}
	}
	glutTimerFunc(32, updateScale, 0);
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Cannon Clash");
	glutDisplayFunc(drawScene);

	glutTimerFunc(32, updateScale, 0);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader::INIT_SHADER();
	INIT_VAO(&piano, &scene);
	INIT_VAO_Text();
	Init_Freetype();

	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(keyboardPressed);
	glutKeyboardUpFunc(keyboardReleased);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


