#include "Entity.h"
#include "VAO_Handler.h"

#define  PI   3.14159265358979323846

Entity::Entity()
{
}
//getters
GLuint* Entity::getVAO() { return &VAO; }
GLuint* Entity::getVBO_G() { return &VBO_G; }
GLuint* Entity::getVBO_C() { return &VBO_C; }
GLuint Entity::getEBO_indici() { return EBO_indici; }
int Entity::getnTriangles() { return nTriangles; }
vector<vec3>* Entity::getVertici() { return &vertici; }
float Entity::getVerticeX(int i)
{
	return vertici[i].x;
}
float Entity::getVerticeY(int i)
{
	return vertici[i].y;
}
vector<vec4>* Entity::getColors() { return &colors; }
int Entity::getVerticiSize(void) { return vertici.size(); }
vec3* Entity::getVerticiData(void) { return vertici.data(); }

int Entity::getColorsSize(void) { return colors.size();  }
vector<vec3> Entity::getCP() { return CP; }
float Entity::getS() { return s; }
vector<vec4> Entity::getColCP() { return colCP; }
int Entity::getNv() { return nv; }
int Entity::getNcp() { return ncp; }
vector<vec3> Entity::getDerivata() { return Derivata; }
vector<vec3> Entity::getPoligonale() { return Poligonale; }
mat4 Entity::getModel() { return Model; }
int Entity::getSceltaFs() { return sceltaFs; }
char Entity::getRender() { return render; }
vec4 Entity::getCorner_b_obj() { return corner_b_obj; }
vec4 Entity::getCorner_t_obj() { return corner_t_obj; }
vec4 Entity::getCorner_b() { return corner_b; }
vec4 Entity::getCorner_t() { return corner_t; }
bool Entity::getAlive() { return alive; }
//setters
void Entity::setVAO(GLuint VAO) { this->VAO = VAO; }
void Entity::setVBO_G(GLuint VBO_G) { this->VBO_G = VBO_G; }
void Entity::setVBO_C(GLuint VBO_C) { this->VBO_C = VBO_C; }
void Entity::setEBO_indici(GLuint EBO_indici) { this->EBO_indici = EBO_indici; }
void Entity::setnTriangles(int nTriangles) { this->nTriangles = nTriangles; }
void Entity::setVertici(vector<vec3> vertici) { this->vertici = vertici; }
void Entity::setColors(vector<vec4> colors) { this->colors = colors; }
void Entity::setCP(vector<vec3> CP) { this->CP = CP; }
void Entity::setS(float s) { this->s = s; }
void Entity::setColCP(vector<vec4> colCP) { this->colCP = colCP; }
void Entity::setNv(int nv) { this->nv = nv; }
void Entity::setNcp(int ncp) { this->ncp = ncp; }
void Entity::setDerivata(vector<vec3> Derivata) { this->Derivata = Derivata; }
void Entity::setPoligonale(vector<vec3> Poligonale) { this->Poligonale = Poligonale; }
void Entity::setModel(mat4 Model) { this->Model = Model; }
void Entity::setSceltaFs(int sceltaFs) { this->sceltaFs = sceltaFs; }
void Entity::setRender(char render) { this->render = render; }
void Entity::setCorner_b_obj(vec4 corner_b_obj) { this->corner_b_obj = corner_b_obj; }
void Entity::setCorner_t_obj(vec4 corner_t_obj) { this->corner_t_obj = corner_t_obj; }
void Entity::setCorner_b(vec4 corner_b) { this->corner_b = corner_b; }
void Entity::setCorner_t(vec4 corner_t) { this->corner_t = corner_t; }
void Entity::setAlive(bool alive) { this->alive = alive; }

void Entity::addVertice(vec3 vertice) { vertici.push_back(vertice); }
void Entity::addColor(vec4 color) { colors.push_back(color); }

void Entity::Build(float cx, float cy, float raggiox, float raggioy, Entity* entity) 
{
	int i;
	entity->addVertice(vec3(-1.0, -1.0, 0.0));
	entity->addVertice(vec3(1.0, -1.0, 0.0));
	entity->addVertice(vec3(-1.0, 1.0, 0.0));
	entity->addVertice(vec3(1.0, 1.0, 0.0));
	for (i = 0; i < entity->getVerticiSize(); i++)
		entity->addColor(vec4(0.13, 0.44, 0.70, 1.0));
	entity->setNv(entity->getVerticiSize());
	entity->setSceltaFs(0);
	entity->setRender(GL_TRIANGLE_STRIP);
}


void Scene::addEntity(Entity entity)
{
	entities.push_back(entity);
}

Entity Scene::getEntity(int i)
{
	return entities[i];
}

void Cuore::Build(float cx, float cy, float raggiox, float raggioy, Entity* fig)
{
	int i;
	float stepA = (2 * PI) / fig->getnTriangles();
	float t;


	fig->addVertice(vec3(cx, cy, 0.0));

	fig->addColor(vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->getnTriangles(); i++)
	{
		t = (float)i * stepA;
		fig->addVertice(vec3(cx + raggiox * (16 * pow(sin(t), 3)), cy + raggioy * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t))), 0.0));
		//Colore 
		fig->addColor(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));


	}
	fig->setNv(fig->getVerticiSize());
	fig->setSceltaFs(1);
	fig->setRender(GL_TRIANGLE_FAN);

}

void Farfalla::Build(float cx, float cy, float raggiox, float raggioy, Entity* fig)
{
	int i;
	float stepA = (2 * PI) / fig->getnTriangles();
	float t, xx, yy;
	float xmax = 0;
	float xmin = 0;

	float ymax = 0;
	float ymin = 0;


	fig->addVertice(vec3(cx, cy, 0.0));

	fig->addColor(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->getnTriangles(); i++)
	{
		t = (float)i * stepA;
		xx = cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		yy = cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5));
		fig->addVertice(vec3(xx, yy, 0.0));
		//Colore 
		fig->addColor(vec4(1.0, 0.0, 0.0, 1.0)); //Nota che la quarta componente corrisponde alla trasparenza del colore
	}

	fig->setNv(fig->getVerticiSize());
	fig->setSceltaFs(1);
	fig->setRender(GL_TRIANGLE_FAN);
	fig->setNv(fig->getVerticiSize());

	//Calcolo di xmin, ymin, xmax, ymax

	for (i = 1; i < fig->getNv(); i++)
		if (fig->getVerticeX(i) <= xmin)
			xmin = fig->getVerticeX(i);


	for (i = 1; i < fig->getNv(); i++)
		if (fig->getVerticeX(i) > xmax)
			xmax = fig->getVerticeX(i);

	for (i = 1; i < fig->getNv(); i++)
		if (fig->getVerticeY(i) <= ymin)
			ymin = fig->getVerticeY(i);


	for (i = 1; i < fig->getNv(); i++)
		if (fig->getVerticeY(i) > ymax)
			ymax = fig->getVerticeY(i);

	//Aggiorno i valori del corner più in basso a sinistra (corner_b) e del corner più in alto a destra (conrner_t)

	fig->setCorner_b_obj(vec4(xmin, ymin, 0.0, 1.0));
	fig->setCorner_t_obj(vec4(xmax, ymax, 0.0, 1.0));
	//Aggiungo i vertici della spezzata per costruire il bounding box
	fig->addVertice(vec3(xmin, ymin, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));
	fig->addVertice(vec3(xmax, ymin, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));
	fig->addVertice(vec3(xmax, ymax, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));
	fig->addVertice(vec3(xmin, ymin, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));
	fig->addVertice(vec3(xmin, ymax, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));
	fig->addVertice(vec3(xmax, ymax, 0.0));
	fig->addColor(vec4(1.0, 0.0, 0.0, 1.0));

	//Aggiorno il numero dei vertici della figura
	fig->setNv(fig->getVerticiSize());
}

