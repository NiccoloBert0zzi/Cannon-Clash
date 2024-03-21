#include <iostream>
#include <fstream>
#include <string>
#include "ShaderMaker.h"
#include "Lib.h"
//#include "Strutture.h"
//#include "geometria.h"
//#include "inizializzazioni.h"
//#include "Gestione_VAO.h"
//#include "Gestione_Gioco.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "GestioneTesto.h"
#include <ft2build.h>
#include FT_FREETYPE_H

mat4 Projection;

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
	/*glutDisplayFunc(drawScene);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(keyboardReleasedEvent);
	glutTimerFunc(250, update_Barca, 0); //gestione evento oziosit : viene richiamata la funzione updateScale ogni 250 millisecondi che aggiorna i parametri di scalatura e forza il ridisegno
	glutTimerFunc(250, update_f, 0);*/

	glewExperimental = GL_TRUE;
	glewInit();
	//INIT_SHADER();
	//INIT_VAO();
	//Init VAO per la gestione del disegno

	//INIT_VAO_Text();
	Init_Freetype();

	//Per gestire i colori con trasparenza: mescola i colori di geometrie che si sovrappongono
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}


