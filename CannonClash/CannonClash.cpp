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
Scene Scena;
Entity piano = {};
//Forma Curva = {}, Poligonale = {}, Derivata = {}, shape = {};

mat4 Projection;
GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

// viewport size
int width = 1280;
int height = 720;
float w_update, h_update;
float dx_t = 0, dy_t = 0;
bool drawBB = TRUE;

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

	/*Matrice di modellazione farfalla */
	Entity e = Scena.getEntity(1);
	Farfalla farfalla = static_cast<Farfalla&>(e);
	farfalla.setModel(mat4(1.0));
	for (size_t i = 0; i < 2; i++)
	{
		farfalla.setModel(translate(farfalla.getModel(), vec3(900.0 + 50 * cos(farfalla.dx_f), 500.0 + 50 * sin(farfalla.dx_f), 0.0)));
		farfalla.setModel(scale(farfalla.getModel(), vec3(80.5, 80.5, 1.0)));
		//Agiornamento in coordinate del mondo delle coordinate del Bounding Box della Farfalla
		farfalla.setCorner_b(farfalla.getCorner_b_obj());
		farfalla.setCorner_t(farfalla.getCorner_t_obj());
		farfalla.setCorner_b(farfalla.getModel() * farfalla.getCorner_b());
		farfalla.setCorner_t(farfalla.getModel() * farfalla.getCorner_t());
	}

	//Disegno la farfalla fino a quando non sia avvenuta la prima collisione con la palla del cannone

	if (farfalla.getAlive() == TRUE)
	{
		glUniform1i(locSceltafs, farfalla.getSceltaFs());
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(farfalla.getModel()));
		glBindVertexArray(*farfalla.getVAO());
		glDrawArrays(GL_TRIANGLE_FAN, 0, farfalla.getNv() - 6);
		if (drawBB == TRUE)
			//		//Disegno Bounding Box
			glDrawArrays(GL_LINE_STRIP, farfalla.getNv() - 6, 6);
		glBindVertexArray(0);
	}
	else
		RenderText(Shader::getProgramId_text(), Projection, "GAME OVER", VAO_Text, VBO_Text, 100.0f, 600.0f, 1.0f, glm::vec3(1.0, 1.0f, 0.2f));
	glUseProgram(Shader::getProgramId());

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
	glutTimerFunc(64, update, 0);
	/*glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	glutTimerFunc(250, update_Barca, 0); //gestione evento oziosit : viene richiamata la funzione updateScale ogni 250 millisecondi che aggiorna i parametri di scalatura e forza il ridisegno
	;*/

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


