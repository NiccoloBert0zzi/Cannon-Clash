#include "Lib.h"
#include "VAO_Handler.h"
#include "Shader.h"
#include "geometria.h"
#include "Entity.h"

extern unsigned int VAO_Text, VBO_Text;
#pragma warning(disable:4996)

extern mat4 Projection;
extern GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

void INIT_VAO(Entity* entity)
{

glGenVertexArrays(1, entity->getVAO());
glBindVertexArray( *entity->getVAO());
//Genero , rendo attivo, riempio il VBO della geometria dei vertici
glGenBuffers(1, entity->getVBO_G());
glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_G());
glBufferData(GL_ARRAY_BUFFER, entity->getVerticiSize() * sizeof(vec3), entity->getVerticiData(), GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
glEnableVertexAttribArray(0);

//Genero , rendo attivo, riempio il VBO dei colori
glGenBuffers(1, entity->getVBO_C());
glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_C());
glBufferData(GL_ARRAY_BUFFER, entity->getColorsSize() * sizeof(vec4), entity->getVerticiData(), GL_STATIC_DRAW);
//Adesso carico il VBO dei colori nel layer 2
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
glEnableVertexAttribArray(1);

}
void INIT_VAO_Text(void)
{

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO_Text);
	glGenBuffers(1, &VBO_Text);
	glBindVertexArray(VAO_Text);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Text);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void INIT_VAO(Entity* piano, Scene* Scena)
{
	costruisci_piano(piano);
	INIT_VAO(piano);
	Scena->addEntity(*piano);
	get_ShaderLocation();
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






}

void get_ShaderLocation(void)
{
	//Projection   la matrice che mappa la finestra sul mondo nelle coordinate NDC (cormalizzate di device che trariano tra (-1,1) ed (1,1)
	//Viene ricavata la location della variabile Uniform Projection presente nel fragment shader
	MatProj = glGetUniformLocation(Shader::getProgramId(), "Projection");
	//Viene ricavata la location della variabile Uniform Model presente nel fragment shader
	MatModel = glGetUniformLocation(Shader::getProgramId(), "Model");
	loctime = glGetUniformLocation(Shader::getProgramId(), "time");
	locres = glGetUniformLocation(Shader::getProgramId(), "resolution");

	locSceltafs = glGetUniformLocation(Shader::getProgramId(), "scelta_fs");
}
