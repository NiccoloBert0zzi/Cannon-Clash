#include "Entity.h"
#include "VAO_Handler.h"

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

void Entity::build(float cx, float cy, float raggiox, float raggioy, Entity* fig)
{

}

void Scene::addEntity(Entity entity)
{
	entities.push_back(entity);
}

Entity Scene::getEntity(int i)
{
	return entities[i];
}
