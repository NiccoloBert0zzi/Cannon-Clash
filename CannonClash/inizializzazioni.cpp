#include "Lib.h"
#include "Strutture.h"
#include "geometria.h"
//#include "Hermite.h"
#include "ShaderMaker.h"
#include "Gestione_VAO.h"

extern unsigned int programId, programId_text;
extern Forma piano;
extern vector<Forma> Scena;
extern unsigned int VAO_Text, VBO_Text;
#pragma warning(disable:4996)

extern mat4 Projection;
extern GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"vertexShader_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_Onde_Nuvole.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);


	//Generazione del program shader per la gestione del testo
	vertexShader = (char*)"VertexShader_Text.glsl";
	fragmentShader = (char*)"FragmentShader_Text.glsl";

	programId_text = ShaderMaker::createProgram(vertexShader, fragmentShader);

}

void INIT_VAO(void)
{
	costruisci_piano(&piano);
	crea_VAO_Vector(&piano);
	Scena.push_back(piano);

	/*Farf.nTriangles = 180;
	Farf.s = 0.2;
	costruisci_farfalla(0.0, 0.0, Farf.s, Farf.s, &Farf);
	crea_VAO_Vector(&Farf);
	Farf.render = GL_TRIANGLE_FAN;
	Farf.alive = TRUE;
	Scena.push_back(Farf);

	//Sommergibile
	vec4 color_top = vec4(0.0, 0.0, 0.0, 1.0);
	vec4 color_bot = vec4(126.0 / 255.0, 135.0 / 255.0, 146.0 / 255.0, 1.0);
	crea_punti_forma_da_file("sommergibile.txt", "r", &Curva);
	vec3 centro = vec3(0.0, -0.2, 0.0);
	costruisci_formaHermite(centro, color_top, color_bot, &Curva);
	crea_VAO_Vector(&Curva);
	Curva.render = GL_TRIANGLE_FAN;
	Curva.sceltaFs = 1;
	Scena.push_back(Curva);
	Curva.CP.clear();
	Curva.Derivata.clear();
	Curva.vertici.clear();


	//Proiettile
	color_top = vec4(1.0, 0.0, 0.0, 1.0);
	color_bot = vec4(1.0, 1.0, 0.0, 1.0);
	crea_punti_forma_da_file("fiore.txt", "r", &Curva);
	centro = vec3(-0.1, 0.1, 0.0);

	costruisci_formaHermite(centro, color_top, color_bot, &Curva);
	crea_VAO_Vector(&Curva);
	Curva.render = GL_TRIANGLE_FAN;
	Curva.sceltaFs = 1;
	Scena.push_back(Curva);
	*/


	//Projection   la matrice che mappa la finestra sul mondo nelle coordinate NDC (cormalizzate di device che trariano tra (-1,1) ed (1,1)


	//Viene ricavata la location della variabile Uniform Projection presente nel fragment shader
	MatProj = glGetUniformLocation(programId, "Projection");
	//Viene ricavata la location della variabile Uniform Model presente nel fragment shader
	MatModel = glGetUniformLocation(programId, "Model");
	loctime = glGetUniformLocation(programId, "time");
	locres = glGetUniformLocation(programId, "resolution");

	locSceltafs = glGetUniformLocation(programId, "scelta_fs");

}
