#pragma once
#include "Lib.h"

#include <string>
class Entity
{
private:
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint EBO_indici;
	int nTriangles;
	// Punti del piano e colori in cui viene disegnata la curva
	vector<vec3> vertici;
	vector<vec4> colors;
	// Punti del piano e colori che vnegono interpolati (Control Points)
	vector<vec3> CP;
	float s;
	vector<vec4> colCP;
	// Numero massimo di punti in cui viene disegnata la curva
	int nv;
	// Numero massimo di punti di interpolazione
	int ncp;
	vector<vec3> Derivata;
	vector<vec3> Poligonale;
	//Matrice di Modellazione: Traslazione*Rotazione*Scala
	mat4 Model;
	int sceltaFs;   //Intero che indica il fragment shader da utilizzare per la renderizzazione
	char render;	// Tipo di render da usare nella gl_Draw_Arrays,  GL_TRIANGLE_FAN, GL_TRAINGLES; etc.
	vec4 corner_b_obj;   //Corner Bottom del Boundng Box in coordinate dell'Oggetto
	vec4 corner_t_obj;   //Corner Top  del Boundng Box in coordinate dell'Oggetto
	vec4 corner_b;		//Corner Bottom del Boundng Box in coordinate del Mondo
	vec4 corner_t;		////Corner Top  del Boundng Box in coordinate dell'Oggetto
	bool alive;     //Booleano: true: in vita

	public:
		//genera getter e setter
		GLuint* getVAO(void);
		GLuint* getVBO_G(void);
		GLuint* getVBO_C(void);
		GLuint getEBO_indici(void);
		int getnTriangles(void);
		vector<vec3>* getVertici(void);
		vector<vec4>* getColors(void);
		int getVerticiSize(void);
		vec3* getVerticiData(void);
		int getColorsSize(void);
		vector<vec3> getCP(void);
		float getS(void);
		vector<vec4> getColCP(void);
		int getNv(void);
		int getNcp(void);
		vector<vec3> getDerivata(void);
		vector<vec3> getPoligonale(void);
		mat4 getModel(void);
		int getSceltaFs(void);
		char getRender(void);
		vec4 getCorner_b_obj(void);
		vec4 getCorner_t_obj(void);
		vec4 getCorner_b(void);
		vec4 getCorner_t(void);
		bool getAlive(void);

		void setVAO(GLuint VAO);
		void setVBO_G(GLuint VBO_G);
		void setVBO_C(GLuint VBO_C);
		void setEBO_indici(GLuint EBO_indici);
		void setnTriangles(int nTriangles);
		void setVertici(vector<vec3> vertici);
		void setColors(vector<vec4> colors);
		void setCP(vector<vec3> CP);
		void setS(float s);
		void setColCP(vector<vec4> colCP);
		void setNv(int nv);
		void setNcp(int ncp);
		void setDerivata(vector<vec3> Derivata);
		void setPoligonale(vector<vec3> Poligonale);
		void setModel(mat4 Model);
		void setSceltaFs(int sceltaFs);
		void setRender(char render);
		void setCorner_b_obj(vec4 corner_b_obj);
		void setCorner_t_obj(vec4 corner_t_obj);
		void setCorner_b(vec4 corner_b);
		void setCorner_t(vec4 corner_t);
		void setAlive(bool alive);

		Entity();
		void build(float cx, float cy, float raggiox, float raggioy, Entity* fig);
		void addVertice(vec3 vertice);
		void addColor(vec4 color);
};

class Scene : public Entity
{
private:
	vector<Entity> entities;
public:
	void addEntity(Entity entity);
	Entity getEntity(int i);
};

