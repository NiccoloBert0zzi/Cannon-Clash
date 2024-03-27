#include <iostream>
#include <fstream>
#include <string>
#include "Shader.h"
#include "Lib.h"
#include "geometria.h"
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
Scene Scena;
Entity piano = {};
//Forma Curva = {}, Poligonale = {}, Derivata = {}, shape = {};

mat4 Projection;
GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

// viewport size
int width = 1280;
int height = 720;
float w_update, h_update;

void reshape(int w, int h)
{
	Projection = ortho(0.0f, (float)width, 0.0f, (float)height);

	float AspectRatio_mondo = (float)(width) / (float)(height); //Rapporto larghezza altezza di tutto ci  che   nel mondo
	//Se l'aspect ratio del mondo   diversa da quella della finestra devo mappare in modo diverso 
	//per evitare distorsioni del disegno
	if (AspectRatio_mondo > w / h)   //Se ridimensioniamo la larghezza della Viewport
	{
		glViewport(0, 0, w, w / AspectRatio_mondo);
		w_update = (float)w;
		h_update = w / AspectRatio_mondo;
	}
	else {  //Se ridimensioniamo la larghezza della viewport oppure se l'aspect ratio tra la finestra del mondo 
		//e la finestra sullo schermo sono uguali
		glViewport(0, 0, h * AspectRatio_mondo, h);
		w_update = h * AspectRatio_mondo;
		h_update = (float)h;
	}
}
void drawScene(void)
{
	int k;

	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	vec2 resolution = vec2(w_update, h_update);

	glUniform1f(loctime, time);
	glUniform2f(locres, resolution.x, resolution.y);


	Entity piano = Scena.getEntity(0);
	piano.setModel(mat4(1.0));
	piano.setModel(translate(piano.getModel(), vec3(0.5, 0.5, 0.0)));
	piano.setModel(scale(piano.getModel(), vec3((float)width, (float)height, 1.0)));
	glUniformMatrix4fv(MatProj, 1, GL_FALSE, value_ptr(Projection));  //comunica i valori della variabile uniform Projection al vertex shader
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(piano.getModel())); //comunica i valori della variabile uniform Model  al vertex shader
	glUniform1i(locSceltafs, piano.getSceltaFs());
	glBindVertexArray(*piano.getVAO());
	glDrawArrays(piano.getRender(), 0, piano.getNv());
	glBindVertexArray(0);

	glutSwapBuffers(); 

}
void updateScale(int value) {
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
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cannon Clash");
	glutReshapeFunc(reshape);
	glutDisplayFunc(drawScene);
	/*glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	glutTimerFunc(250, update_Barca, 0); //gestione evento oziosit : viene richiamata la funzione updateScale ogni 250 millisecondi che aggiorna i parametri di scalatura e forza il ridisegno
	glutTimerFunc(250, update_f, 0);*/

	glutTimerFunc(32, updateScale, 0);
	glewExperimental = GL_TRUE;
	glewInit();

	Shader::INIT_SHADER();
	INIT_VAO(&piano,&Scena);
	//Init VAO per la gestione del disegno

	INIT_VAO_Text();
	Init_Freetype();

	//Per gestire i colori con trasparenza: mescola i colori di geometrie che si sovrappongono
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


