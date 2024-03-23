#include "Shader.h"
#include <iostream>
#include <fstream>

// Inizializzazione delle variabili statiche della classe Shader
unsigned int Shader::programId;
unsigned int Shader::programId_text;
char* Shader::vertexShader;
char* Shader::fragmentShader;

// Funzione per creare un programma shader
GLuint Shader::createProgram(char* vertexfilename, char* fragmentfilename)
{
	GLenum ErrorCheckValue = glGetError();
	int success;
	char infoLog[512];

	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Caricamento e compilazione del Vertex Shader
	GLchar* VertexShader = readShaderSource(vertexfilename);
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, (const char**)&VertexShader, NULL);
	glCompileShader(vertexShaderId);

	// Controllo degli errori nella compilazione del Vertex Shader
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Caricamento e compilazione del Fragment Shader
	const GLchar* FragmentShader = readShaderSource(fragmentfilename);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char**)&FragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	// Controllo degli errori nella compilazione del Fragment Shader
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Controllo generale degli errori
	ErrorCheckValue = glGetError();
	std::cout << ErrorCheckValue;

	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}

	// Creazione del programma shader e collegamento dei due shader compilati
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	return programId;
}

// Funzione per leggere il codice sorgente dello shader da file
char* Shader::readShaderSource(const char* shaderFile)
{
	FILE* fp;
	fopen_s(&fp, shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

// Funzione per inizializzare i programmi shader
void Shader::INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	vertexShader = (char*)"vertexShader_M.glsl";
	fragmentShader = (char*)"fragmentShader_Green_Spiral.glsl";

	programId = Shader::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);

	// Inizializzazione del programma shader per la gestione del testo
	vertexShader = (char*)"VertexShader_Text.glsl";
	fragmentShader = (char*)"FragmentShader_Text.glsl";

	programId_text = Shader::createProgram(vertexShader, fragmentShader);
}

// Funzioni per ottenere gli ID dei programmi shader
unsigned int Shader::getProgramId(void)
{
	return programId;
}

unsigned int Shader::getProgramId_text(void)
{
	return programId_text;
}

// Funzioni per ottenere i nomi dei file shader
char* Shader::getVertexShader(void)
{
	return vertexShader;
}

char* Shader::getFragmentShader(void)
{
	return fragmentShader;
}
