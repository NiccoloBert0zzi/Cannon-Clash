#include <iostream>
#include <fstream>
#include <string>
#include "Lib.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Text_Handler.h"
#include <ft2build.h>
#include <ctime>
#include <chrono>
#include FT_FREETYPE_H

#ifdef NDEBUG
bool debugMode = false; // Non sei in modalità di debug
#else
bool debugMode = true; // Sei in modalità di debug
#endif


unsigned int VAO_Text, VBO_Text;

//init
vector<vector<Entity*>*> scene;
vector<Entity*> piano;

mat4 Projection;
GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

// viewport size
int width = 1280;
int height = 720;
int score = 0;

// Dichiarazione di una variabile per tenere traccia del tempo trascorso dall'ultima generazione di nemici
float lastEnemySpawnTime = 0.0f;
// Intervallo di tempo tra le generazioni di nemici
float enemySpawnInterval = 1.0f;
float currentTime = 0;

// Funzione per ottenere il tempo corrente in secondi
float getTime() {
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto timeInSeconds = std::chrono::duration<float>(currentTime.time_since_epoch()).count();
	return timeInSeconds;
}

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
	glDrawArrays(GL_TRIANGLE_FAN, 0, entity->getNV() - 6);
	if (debugMode)
		glDrawArrays(GL_LINE_STRIP, entity->getNV() - 6, 6);
	glBindVertexArray(0);
}

void gameOver(char* text)
{
	string str(text);
	renderText(Shader::getProgramId_text(), Projection, str, VAO_Text, VBO_Text, width / 2 - 30.0f * str.length() / 2, height / 2 - 10.0f, 1.0f, vec3(1.0f, 0.0f, 0.0f));
}

void drawScene(void)
{
	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	bool playerAlive = false;
	int numberOfEnemies = 0;

	for (vector<Entity*>* container : scene)
	{
		for (Entity* entity : *container)
		{
			if (entity->getType() == Type::BACKGROUND)
				drawEntity(entity);
			else if (entity->isAlive()) {
				if (entity->getType() == Type::PLAYER) {
					Player* player = dynamic_cast<Player*>(entity);
					//implicito che se è arrivato qui il player è vivo
					playerAlive = true;
					for (Bullet* bullet : *player->getBullets()) {
						drawEntity(bullet);
					}
					for (Heart* heart : *player->getHearts()) {
						drawEntity(heart);
					}
					drawEntity(player->getWheel());
					drawEntity(player->getCannon());
					score = player->getScore();
				}
				if (playerAlive)
					drawEntity(entity);
			}
			if (entity->getType() == Type::ENEMY) {
				Enemy* enemy = dynamic_cast<Enemy*>(entity);
				if (!enemy->isDead())
					numberOfEnemies++;
			}
		}
	}

	if (playerAlive && numberOfEnemies == 0)
		gameOver((char*)"YOU WIN");
	else if (!playerAlive)
		gameOver((char*)"YOU LOSE");
	string _score = "Score: " + to_string(score);
	renderText(Shader::getProgramId_text(), Projection, _score, VAO_Text, VBO_Text, 0 + 10.f, height - 30.0f, 0.5f, vec3(1.0f, 0.0f, 0.0f));
	glutSwapBuffers();
	glUseProgram(Shader::getProgramId());
}

void updateScale(int value) {
	currentTime = getTime();

	for (vector<Entity*>* container : scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == Type::PLAYER) {
				Player* player = dynamic_cast<Player*>(entity);
				player->updateHearts();
				player->updateBullets();
				player->updatePlayerPartsVAO();
			}
			else if (entity->getType() == Type::ENEMY) {
				Enemy* enemy = dynamic_cast<Enemy*>(entity);
				if (enemy->isAlive()) {
					enemy->updatePosition();
					enemy->checkEnemyCollision();
				}
				else {
					if ((currentTime - lastEnemySpawnTime >= enemySpawnInterval) && !enemy->isDead()) {
						enemy->setAlive(true);
						lastEnemySpawnTime = currentTime;
					}
				}
			}
			entity->updateVAO();
		}
	}
	glutTimerFunc(32, updateScale, 0);
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	lastEnemySpawnTime = getTime();
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
	INIT_VAO_Text(&VAO_Text, &VBO_Text);
	Init_Freetype();

	glutPassiveMotionFunc(mouseMovement);
	glutKeyboardFunc(keyboardPressed);
	glutKeyboardUpFunc(keyboardReleased);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


