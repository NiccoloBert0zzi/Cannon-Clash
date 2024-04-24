#include "Lib.h"
#include "VAO_Handler.h"
#include "Shader.h"
#include "Entity.h"

extern unsigned int VAO_Text, VBO_Text;
#pragma warning(disable:4996)

extern mat4 Projection;
extern GLuint MatProj, MatModel, loctime, locres, locCol1, locCol2, locCol3, locSceltafs;

void INIT_VAO(Entity* entity)
{

	glGenVertexArrays(1, entity->getVAO());
	glBindVertexArray(*entity->getVAO());
	glGenBuffers(1, entity->getVBO_G());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_G());
	glBufferData(GL_ARRAY_BUFFER, entity->getNV() * sizeof(vec3), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, entity->getVBO_C());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_C());
	glBufferData(GL_ARRAY_BUFFER, entity->getNV() * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

}
void UPDATE_VAO(Entity* entity) {
	vector<vec3> vertices = *entity->getVertices();
	vector<vec4> colors = *entity->getVerticesColors();
	glBindVertexArray(*entity->getVAO());
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_G());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getNV() * sizeof(vec3), vertices.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, *entity->getVBO_C());
	glBufferSubData(GL_ARRAY_BUFFER, 0, entity->getNV() * sizeof(vec4), colors.data());
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}
void INIT_VAO_Text(GLuint* VAO_Text, GLuint* VBO_Text)
{

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, VAO_Text);
	glGenBuffers(1, VBO_Text);
	glBindVertexArray(*VAO_Text);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO_Text);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void INIT_VAO(vector<Entity*>* piano, vector<vector<Entity*>*>* scene)
{
	//background
	Entity* backgroundPane = new Entity(Type::BACKGROUND);
	backgroundPane->build();
	backgroundPane->changePane();
	piano->push_back(backgroundPane);

	//player
	vector<Entity*>* players = new vector<Entity*>();
	Player* player = new Player();
	players->push_back(player);
	player->build();
	
	//enemy
	vector<Entity*>* enemys = new vector<Entity*>();
	for (size_t i = 0; i < 2; i++) {
		Enemy* enemy = new Enemy();
		enemys->push_back(enemy);
		enemy->build();
	}

	scene->push_back(piano);
	scene->push_back(players);
	scene->push_back(enemys);

	for (vector<Entity*>* container : *scene) {
		for (Entity* entity : *container) {
			if (entity->getType() == Type::PLAYER) {
				Player* player = dynamic_cast<Player*>(entity);
				player->initHearts();
				player->initBullets();
				player->initPlayerPartsVAO();
			}
			entity->initVAO();
		}
	}

	get_ShaderLocation();
}



void get_ShaderLocation(void)
{
	Projection = ortho(0.0f, (float)width, 0.0f, (float)height);
	//Projection   la matrice che mappa la finestra sul mondo nelle coordinate NDC (cormalizzate di device che trariano tra (-1,1) ed (1,1)
	//Viene ricavata la location della variabile Uniform Projection presente nel fragment shader
	MatProj = glGetUniformLocation(Shader::getProgramId(), "Projection");
	//Viene ricavata la location della variabile Uniform Model presente nel fragment shader
	MatModel = glGetUniformLocation(Shader::getProgramId(), "Model");
	loctime = glGetUniformLocation(Shader::getProgramId(), "time");
	locres = glGetUniformLocation(Shader::getProgramId(), "resolution");

	locSceltafs = glGetUniformLocation(Shader::getProgramId(), "scelta_fs");
	glViewport(0, 0, width, height);

}
