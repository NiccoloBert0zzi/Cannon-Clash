#include "Geometry.h"

vector<vec3> createRectangle(float width, float height) {
	vector<vec3> vertices;
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, height / 2, 0.0f));
	vertices.push_back(vec3(-width / 2, -height / 2, 0.0f));
	vertices.push_back(vec3(width / 2, -height / 2, 0.0f));
	return vertices;
}

vector<vec3> createHearth(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		float x = rx * 16 * pow(sin(theta_i), 3);
		float y = ry * (13 * cos(theta_i) - 5 * cos(2 * theta_i) - 2 * cos(3 * theta_i) - cos(4 * theta_i));
		vertices.push_back(vec3(x, y, 0.0f));
	}
	return vertices;
}

vector<vec3> createCircle(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++) {
		float theta_i = (float)i * step;
		vertices.push_back(vec3(rx * cos(theta_i), ry * sin(theta_i), 0.0f));
	}
	return vertices;

}

vector<vec3> createCannonBall(float outerRadius, float innerRadius, int precision)
{
	float outerStep = 2 * PI / precision;
	float innerStep = 2 * PI / precision; // Stessa precisione per entrambi i cerchi
	vector<vec3> vertices;

	// Cerchio interno (bianco)
	for (int i = 0; i <= precision; i++) {
		float theta_i = (float)i * innerStep;
		vertices.push_back(vec3(innerRadius * cos(theta_i), innerRadius * sin(theta_i), 0.0f));
	}

	// Cerchio esterno (nero)
	for (int i = 0; i <= precision; i++) {
		float theta_i = (float)i * outerStep;
		vertices.push_back(vec3(outerRadius * cos(theta_i), outerRadius * sin(theta_i), 0.0f));
	}

	return vertices;
}



vector<vec3> createPlayerCockpit(float width, float height)
{
	vector<vec3> vertices;
	float halfWidth = width / 2.0f; // Calcolo della metà della larghezza

	// Creazione del rettangolo centrato rispetto alla larghezza
	vertices.push_back(vec3(-halfWidth, 0.0f, 0.0f)); // Angolo in basso a sinistra
	vertices.push_back(vec3(halfWidth, 0.0f, 0.0f)); // Angolo in basso a destra
	vertices.push_back(vec3(halfWidth, height, 0.0f)); // Angolo in alto a destra
	vertices.push_back(vec3(-halfWidth, height, 0.0f)); // Angolo in alto a sinistra
	vertices.push_back(vec3(-halfWidth, 0.0f, 0.0f)); // Ritorno al punto di partenza
	return vertices;
}
