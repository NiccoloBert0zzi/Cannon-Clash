#include <iostream>
#include <fstream>
#include <string>
#include "Shader.h"
#include "Lib.h"
#include "VAO_Handler.h"
//#include "Gestione_Gioco.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Text_Handler.h"
#include <ft2build.h>
#include "Entity.h"
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

void drawScene(void)
{
	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	vec2 resolution = vec2(width, height);

	for (vector<Entity*>* container : scene)
	{
		for (Entity* entity : *container)
		{
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
	}
	glutSwapBuffers();
	glUseProgram(Shader::getProgramId());
}
void updateScale(int value) {
	for (vector<Entity*>* container : scene)
		for (Entity* entity : *container)
			entity->updateVAO();
	glutTimerFunc(32, updateScale, 0);
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Cannon Clash");
	glutDisplayFunc(drawScene);
	/*glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	glutTimerFunc(250, update_Barca, 0); //gestione evento oziosit : viene richiamata la funzione updateScale ogni 250 millisecondi che aggiorna i parametri di scalatura e forza il ridisegno
	;*/

	glutTimerFunc(32, updateScale, 0);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader::INIT_SHADER();
	INIT_VAO(&piano, &scene);
	//Init VAO per la gestione del disegno

	INIT_VAO_Text();
	Init_Freetype();

	//Per gestire i colori con trasparenza: mescola i colori di geometrie che si sovrappongono
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


