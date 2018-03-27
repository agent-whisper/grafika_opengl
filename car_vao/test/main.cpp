#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <list>
#include <math.h>

const std::string WINDOW_TITLE = "BASIC TEMPLATE";

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct shaderProgram {
	GLuint vertShaderID;
	GLuint fragShaderID;
	GLuint shaderProgramID;
	GLuint positionID;
	GLuint colorID;
} shaderProgram;

typedef struct glObject {
	int *numOfVertex;
	GLuint *vao;
	GLuint *vbo;
	shaderProgram *shader;
} glObject;

glObject *car;
glObject *road;
glObject *city;

GLuint shaderProgramID;
GLuint vao = 0;
GLuint vbo;
GLuint positionID, colorID;
GLuint *car_vao;
GLuint *car_vbo;


// =========================================================================================

#pragma region SHADER_FUNCTIONS
// Utitility Functions
static char* readFile(const char* filename) {
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "r");

	if (err) {
		printf("Error opening "); printf(filename); printf("\n");
	}

	fseek(fp, 0, SEEK_END);

	long file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *contents = new char[file_length + 1];

	for (int i = 0; i < file_length + 1; i++) {
		contents[i] = '\0';
	}

	fread(contents, 1, file_length, fp);

	contents[file_length + 1] = '\0';
	fclose(fp);

	return contents;
}

// Shader Functions
GLuint makeVertexShader(const char* shaderSource) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vertexShaderID);
	return vertexShaderID;
} // function to generate vertex shader id

GLuint makeFragmentShader(const char* shaderSource) {
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(fragmentShaderID);
	return fragmentShaderID;
} // function to generate fragment shader id

GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);
	return shaderID;
} // function to generate shader program id
#pragma endregion SHADER_FUNCTIONS

void setupShader(shaderProgram* s) {
	char *vertexShaderSourceCode = readFile("vertexShader.vsh"); // Loads the vertex shader source file
	char *fragmentShaderSourceCode = readFile("fragmentShader.fsh"); // Loads the fragment shader source file
	s->vertShaderID = makeVertexShader(vertexShaderSourceCode); // Generate the vertex shader ID
	s->fragShaderID = makeFragmentShader(fragmentShaderSourceCode); // Generate the fragment shader ID
	s->shaderProgramID = makeShaderProgram(s->vertShaderID, s->fragShaderID); // Generate the shader program ID
}

// Window Functions
void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
} // Function for resizing window. Put in "glutReshapeFunc"

void render() {
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 10; i++) {
		glBindVertexArray(city->vao[i]);
		glDrawArrays(GL_POLYGON, 0, city->numOfVertex[i]);
		glBindVertexArray(0);
	}

	glBindVertexArray(road->vao[0]);
	glDrawArrays(GL_POLYGON, 0, road->numOfVertex[0]);
	glBindVertexArray(0);

	glBindVertexArray(road->vao[1]);
	glDrawArrays(GL_POLYGON, 0, road->numOfVertex[1]);
	glBindVertexArray(0);

	glBindVertexArray(road->vao[2]);
	glDrawArrays(GL_POLYGON, 0, road->numOfVertex[2]);
	glBindVertexArray(0);

	glBindVertexArray(car->vao[0]);
	glDrawArrays(GL_POLYGON, 0, car->numOfVertex[0]);
	glBindVertexArray(0);

	glBindVertexArray(car->vao[1]);
	glDrawArrays(GL_POLYGON, 0, car->numOfVertex[1]);
	glBindVertexArray(0);

	glBindVertexArray(car->vao[2]);
	glDrawArrays(GL_POLYGON, 0, car->numOfVertex[2]);
	glBindVertexArray(0);

	glBindVertexArray(car->vao[3]);
	glDrawArrays(GL_POLYGON, 0, car->numOfVertex[3]);
	glBindVertexArray(0);

	glBindVertexArray(car->vao[4]);
	glDrawArrays(GL_POLYGON, 0, car->numOfVertex[4]);
	glBindVertexArray(0);

	
	glBindVertexArray(car->vao[5]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, car->numOfVertex[5]);
	glBindVertexArray(0);
	
	glBindVertexArray(car->vao[6]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, car->numOfVertex[6]);
	glBindVertexArray(0);

	glutSwapBuffers();
}

// =========================================================================================

int main(int argc, char** argv) {

	// === GLUT INITIALIZATION ===
	glutInit(&argc, argv); // Initializes GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Set up some memory buffers for our display
	glutInitWindowSize(800, 600); // Set window size
	glutCreateWindow(WINDOW_TITLE.data()); // Create the window with the title "Hello Fariz"

	// Bind the window functions to the actual window
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	// Needed to call OpenGL functions
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error");
		return 1;
	}

	// === CAR ===
#pragma region CAR_SETUP
	car = new glObject;
	car->vao = new GLuint[9];
	car->vbo = new GLuint[9];
	car->shader = new shaderProgram[9];
	car->numOfVertex = new int[9];

	// body
	car->numOfVertex[0] = 8;
	glGenVertexArrays(1, &car->vao[0]);
	glBindVertexArray(car->vao[0]);

	glGenBuffers(1, &car->vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[0]);

	GLfloat car_body_vertices[] =
	{
		-1.0f, 0.1f, 0.0f,
		-0.85f, 0.35f, 0.0f,
		-0.15f, 0.35f, 0.0f,
		0.0f, 0.1f, 0.0f,
		0.2f, 0.1f, 0.0f,
		0.3f, 0.0f, 0.0f,
		0.3f, -0.2f, 0.0f,
		-1.0f, -0.2f, 0.0f
	};
	GLfloat car_body_colors[] =
	{ 1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

	setupShader(&car->shader[0]);

	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[0] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_body_vertices), car_body_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body_vertices), sizeof(car_body_colors), car_body_colors);

	car->shader[0].positionID = glGetAttribLocation(car->shader[0].shaderProgramID, "s_vPosition");
	car->shader[0].colorID = glGetAttribLocation(car->shader[0].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[0].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[0].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(car_body_vertices)));
	glUseProgram(car->shader[0].shaderProgramID);
	glEnableVertexAttribArray(car->shader[0].positionID);
	glEnableVertexAttribArray(car->shader[0].colorID);
	glBindVertexArray(0);
	
	// middle window
	car->numOfVertex[1] = 4;
	glGenVertexArrays(1, &car->vao[1]);
	glBindVertexArray(car->vao[1]);

	glGenBuffers(1, &car->vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[1]);

	GLfloat car_mWindow_vertices[] =
	{
		-0.74f, 0.1f, 0.0f,
		-0.74f, 0.3f, 0.0f,
		-0.43f, 0.3f, 0.0f,
		-0.43f, 0.1f, 0.0f
	};
	GLfloat car_mWindow_colors[] =
	{ 
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f
	};

	setupShader(&car->shader[1]);

	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[1] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_mWindow_vertices), car_mWindow_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_mWindow_vertices), sizeof(car_mWindow_colors), car_mWindow_colors);

	car->shader[1].positionID = glGetAttribLocation(car->shader[1].shaderProgramID, "s_vPosition");
	car->shader[1].colorID = glGetAttribLocation(car->shader[1].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[1].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[1].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(car_mWindow_vertices)));
	glUseProgram(car->shader[1].shaderProgramID);
	glEnableVertexAttribArray(car->shader[1].positionID);
	glEnableVertexAttribArray(car->shader[1].colorID);
	glBindVertexArray(0);

	// front window
	car->numOfVertex[2] = 4;
	glGenVertexArrays(1, &car->vao[2]);
	glBindVertexArray(car->vao[2]);

	glGenBuffers(1, &car->vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[2]);

	GLfloat car_fWindow_vertices[] =
	{
		-0.4f, 0.1f, 0.0f,
		-0.4f, 0.3f, 0.0f,
		-0.16f, 0.3f, 0.0f,
		-0.05f, 0.1f, 0.0f
	};
	GLfloat car_fWindow_colors[] =
	{
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f
	};

	setupShader(&car->shader[2]);

	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[2] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_fWindow_vertices), car_fWindow_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_fWindow_vertices), sizeof(car_fWindow_colors), car_fWindow_colors);

	car->shader[2].positionID = glGetAttribLocation(car->shader[2].shaderProgramID, "s_vPosition");
	car->shader[2].colorID = glGetAttribLocation(car->shader[2].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[2].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[2].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(car_fWindow_vertices)));
	glUseProgram(car->shader[2].shaderProgramID);
	glEnableVertexAttribArray(car->shader[2].positionID);
	glEnableVertexAttribArray(car->shader[2].colorID);
	glBindVertexArray(0);

	// back window
	car->numOfVertex[3] = 4;
	glGenVertexArrays(1, &car->vao[3]);
	glBindVertexArray(car->vao[3]);

	glGenBuffers(1, &car->vbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[3]);

	GLfloat car_bWindow_vertices[] =
	{
		-0.77f, 0.3f, 0.0f,
		- 0.77f, 0.1f, 0.0f,
		- 0.95f, 0.1f, 0.0f,
		- 0.84f, 0.3f, 0.0f
	};
	GLfloat car_bWindow_colors[] =
	{
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f,
		0.8f, 0.8f, 0.3f, 1.0f
	};

	setupShader(&car->shader[3]);

	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[3] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_bWindow_vertices), car_bWindow_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_bWindow_vertices), sizeof(car_bWindow_colors), car_bWindow_colors);

	car->shader[3].positionID = glGetAttribLocation(car->shader[3].shaderProgramID, "s_vPosition");
	car->shader[3].colorID = glGetAttribLocation(car->shader[3].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[3].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[3].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(car_bWindow_vertices)));
	glUseProgram(car->shader[3].shaderProgramID);
	glEnableVertexAttribArray(car->shader[3].positionID);
	glEnableVertexAttribArray(car->shader[3].colorID);
	glBindVertexArray(0);

	// headlight
	car->numOfVertex[4] = 4;
	glGenVertexArrays(1, &car->vao[4]);
	glBindVertexArray(car->vao[4]);

	glGenBuffers(1, &car->vbo[4]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[4]);

	GLfloat car_headlight_vertices[] =
	{
		0.22f, 0.083f, 0.0f,
		0.3f, 0.009f, 0.0f,
		0.19f, 0.03f, 0.0f,
		0.14f, 0.085f, 0.0f
	};
	GLfloat car_headlight_colors[] =
	{
		0.8f, 0.8f, 1.0f, 1.0f,
		0.8f, 0.8f, 1.0f, 1.0f,
		0.8f, 0.8f, 1.0f, 1.0f,
		0.8f, 0.8f, 1.0f, 1.0f
	};

	setupShader(&car->shader[4]);

	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[4] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_headlight_vertices), car_headlight_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_headlight_vertices), sizeof(car_headlight_colors), car_headlight_colors);

	car->shader[4].positionID = glGetAttribLocation(car->shader[4].shaderProgramID, "s_vPosition");
	car->shader[4].colorID = glGetAttribLocation(car->shader[4].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[4].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[4].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(car_headlight_vertices)));
	glUseProgram(car->shader[4].shaderProgramID);
	glEnableVertexAttribArray(car->shader[4].positionID);
	glEnableVertexAttribArray(car->shader[4].colorID);
	glBindVertexArray(0);

	// tires
	GLfloat outer_radius = 0.14f;
	GLfloat inner_radius = 0.08f;
	double twicePi = 2.0 * 3.142;

	// back tire
	car->numOfVertex[5] = 22;
	glGenVertexArrays(1, &car->vao[5]);
	glBindVertexArray(car->vao[5]);

	glGenBuffers(1, &car->vbo[5]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[5]);

	GLfloat back_tire[67];
	back_tire[0] = -0.8f;
	back_tire[1] = -0.2f;
	back_tire[2] = 0.0f;
	for (int i = 3; i < 66; i += 3) {
		back_tire[i] = (-0.8f + (GLfloat)(outer_radius * cos(i * twicePi / 20)));
		back_tire[i + 1] = (-0.2f + (GLfloat)(outer_radius * sin(i * twicePi / 20)));
		back_tire[i + 2] = 0.0f;
	}

	GLfloat back_tire_color[88];
	for (int i = 3; i < 84; i += 4) {
		back_tire_color[i] = 1.0f;
		back_tire_color[i + 1] = 1.0f;
		back_tire_color[i + 2] = 1.0f;
		back_tire_color[i + 3] = 1.0f;
	}

	setupShader(&car->shader[5]);
	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[5] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(back_tire), back_tire);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(back_tire), sizeof(back_tire_color), back_tire_color);

	car->shader[5].positionID = glGetAttribLocation(car->shader[5].shaderProgramID, "s_vPosition");
	car->shader[5].colorID = glGetAttribLocation(car->shader[5].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[5].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[5].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(back_tire)));
	glUseProgram(car->shader[5].shaderProgramID);
	glEnableVertexAttribArray(car->shader[5].positionID);
	glEnableVertexAttribArray(car->shader[5].colorID);
	glBindVertexArray(0);

	// front tire
	car->numOfVertex[6] = 22;
	glGenVertexArrays(1, &car->vao[6]);
	glBindVertexArray(car->vao[6]);

	glGenBuffers(1, &car->vbo[6]);
	glBindBuffer(GL_ARRAY_BUFFER, car->vbo[6]);

	GLfloat front_tire[67];
	front_tire[0] = 0.0f;
	front_tire[1] = -0.2f;
	front_tire[2] = 0.0f;
	for (int i = 3; i < 66; i += 3) {
		front_tire[i] = (0.0f + (GLfloat)(outer_radius * cos(i * twicePi / 20)));
		front_tire[i + 1] = (-0.2f + (GLfloat)(outer_radius * sin(i * twicePi / 20)));
		front_tire[i + 2] = 0.0f;
	}

	GLfloat front_tire_color[88];
	for (int i = 3; i < 84; i += 4) {
		front_tire_color[i] = 0.0f;
		front_tire_color[i + 1] = 0.0f;
		front_tire_color[i + 2] = 0.0f;
		front_tire_color[i + 3] = 1.0f;
	}

	setupShader(&car->shader[6]);
	glBufferData(GL_ARRAY_BUFFER, 7 * car->numOfVertex[6] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(front_tire), front_tire);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(front_tire), sizeof(front_tire_color), front_tire_color);

	car->shader[6].positionID = glGetAttribLocation(car->shader[6].shaderProgramID, "s_vPosition");
	car->shader[6].colorID = glGetAttribLocation(car->shader[6].shaderProgramID, "s_vColor");

	glVertexAttribPointer(car->shader[6].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(car->shader[6].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(front_tire)));
	glUseProgram(car->shader[6].shaderProgramID);
	glEnableVertexAttribArray(car->shader[6].positionID);
	glEnableVertexAttribArray(car->shader[6].colorID);
	glBindVertexArray(0);
#pragma endregion CAR_SETUP

	// === ROAD ===
#pragma region ROAD_SETUP
	road = new glObject;
	road->vao = new GLuint[3];
	road->vbo = new GLuint[3];
	road->shader = new shaderProgram[3];
	road->numOfVertex = new int[3];

	// base
	road->numOfVertex[0] = 4;
	glGenVertexArrays(1, &road->vao[0]);
	glBindVertexArray(road->vao[0]);

	glGenBuffers(1, &road->vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, road->vbo[0]);

	GLfloat road_body_vertices[] =
	{
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};
	GLfloat road_body_colors[] =
	{ 
		0.13f, 0.13f, 0.13f, 1.0f,
		0.13f, 0.13f, 0.13f, 1.0f,
		0.13f, 0.13f, 0.13f, 1.0f,
		0.13f, 0.13f, 0.13f, 1.0f
	};

	setupShader(&road->shader[0]);

	glBufferData(GL_ARRAY_BUFFER, 7 * road->numOfVertex[0] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(road_body_vertices), road_body_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(road_body_vertices), sizeof(road_body_colors), road_body_colors);

	road->shader[0].positionID = glGetAttribLocation(road->shader[0].shaderProgramID, "s_vPosition");
	road->shader[0].colorID = glGetAttribLocation(road->shader[0].shaderProgramID, "s_vColor");

	glVertexAttribPointer(road->shader[0].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(road->shader[0].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(road_body_vertices)));
	glUseProgram(road->shader[0].shaderProgramID);
	glEnableVertexAttribArray(road->shader[0].positionID);
	glEnableVertexAttribArray(road->shader[0].colorID);
	glBindVertexArray(0);

	// left white thingy
	road->numOfVertex[1] = 4;
	glGenVertexArrays(1, &road->vao[1]);
	glBindVertexArray(road->vao[1]);

	glGenBuffers(1, &road->vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, road->vbo[1]);

	GLfloat road_left_vertices[] =
	{
		-0.75f, -0.35f, 0.0f,
		-0.15f, -0.35f, 0.0f,
		-0.1f, -0.45f, 0.0f,
		-0.8f, -0.45f, 0.0f
	};
	GLfloat road_left_colors[] =
	{
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f
	};

	setupShader(&road->shader[1]);

	glBufferData(GL_ARRAY_BUFFER, 7 * road->numOfVertex[1] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(road_left_vertices), road_left_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(road_left_vertices), sizeof(road_left_colors), road_left_colors);

	road->shader[1].positionID = glGetAttribLocation(road->shader[1].shaderProgramID, "s_vPosition");
	road->shader[1].colorID = glGetAttribLocation(road->shader[1].shaderProgramID, "s_vColor");

	glVertexAttribPointer(road->shader[1].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(road->shader[1].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(road_left_vertices)));
	glUseProgram(road->shader[1].shaderProgramID);
	glEnableVertexAttribArray(road->shader[1].positionID);
	glEnableVertexAttribArray(road->shader[1].colorID);
	glBindVertexArray(0);

	// right white thingy
	road->numOfVertex[2] = 4;
	glGenVertexArrays(1, &road->vao[2]);
	glBindVertexArray(road->vao[2]);

	glGenBuffers(1, &road->vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, road->vbo[2]);

	GLfloat road_right_vertices[] =
	{
		0.3f, -0.35f, 0.0f,
		0.9f, -0.35f, 0.0f,
		0.95f, -0.45f, 0.0f,
		0.25f, -0.45f, 0.0f
	};
	GLfloat road_right_colors[] =
	{
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f,
		1, 1, 1, 1.0f
	};

	setupShader(&road->shader[2]);

	glBufferData(GL_ARRAY_BUFFER, 7 * road->numOfVertex[2] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(road_right_vertices), road_right_vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(road_right_vertices), sizeof(road_right_colors), road_right_colors);

	road->shader[2].positionID = glGetAttribLocation(road->shader[2].shaderProgramID, "s_vPosition");
	road->shader[2].colorID = glGetAttribLocation(road->shader[2].shaderProgramID, "s_vColor");

	glVertexAttribPointer(road->shader[2].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(road->shader[2].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(road_right_vertices)));
	glUseProgram(road->shader[2].shaderProgramID);
	glEnableVertexAttribArray(road->shader[2].positionID);
	glEnableVertexAttribArray(road->shader[2].colorID);
	glBindVertexArray(0);
#pragma endregion ROAD_SETUP

	// === CITY ===
#pragma region CITY_SETUP
	city = new glObject;
	city->vao = new GLuint[10];
	city->vbo = new GLuint[10];
	city->shader = new shaderProgram[10];
	city->numOfVertex = new int[10];

	GLfloat building_vertex[10][12];
	GLfloat building_colors[10][16];
	for (int i = 0; i < 10; i++) {
		city->numOfVertex[i] = 4;

		GLfloat height = (rand() % 30 + 50) / 100.0f; // 0.5 - 0.8

		int j = 0;
		building_vertex[i][j] = -1.0f + i * 0.3f;
		building_vertex[i][j + 1] = 0.0f;
		building_vertex[i][j + 2] = 0.0f;
		j += 3;

		building_vertex[i][j] = -1.0f + i * 0.3f;
		building_vertex[i][j + 1] = height;
		building_vertex[i][j + 2] = 0.0f;
		j += 3;

		building_vertex[i][j] = -1.0f + i * 0.3f + 0.3f;
		building_vertex[i][j + 1] = height;
		building_vertex[i][j + 2] = 0.0f;
		j += 3;

		building_vertex[i][j] = -1.0f + i * 0.3f + 0.3f;
		building_vertex[i][j + 1] = 0.0f;
		building_vertex[i][j + 2] = 0.0f;
		j += 3;

		for (int k = 0; k < 16; k += 4) {
			building_colors[i][k] = 0.6f;
			building_colors[i][k + 1] = 0.0f;
			building_colors[i][k + 2] = 0.6f;
			building_colors[i][k + 3] = 1.0f;
		}
		glGenVertexArrays(1, &city->vao[i]);
		glBindVertexArray(city->vao[i]);

		glGenBuffers(1, &city->vbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, city->vbo[i]);

		setupShader(&city->shader[i]);

		glBufferData(GL_ARRAY_BUFFER, 7 * city->numOfVertex[i] * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(building_vertex[i]), building_vertex[i]);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(building_vertex[i]), sizeof(building_colors[i]), building_colors[i]);

		city->shader[i].positionID = glGetAttribLocation(city->shader[i].shaderProgramID, "s_vPosition");
		city->shader[i].colorID = glGetAttribLocation(city->shader[i].shaderProgramID, "s_vColor");

		glVertexAttribPointer(city->shader[i].positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(city->shader[i].colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(building_vertex[i])));
		glUseProgram(city->shader[i].shaderProgramID);
		glEnableVertexAttribArray(city->shader[i].positionID);
		glEnableVertexAttribArray(city->shader[i].colorID);
		glBindVertexArray(0);
	}
#pragma endregion CITY_SETUP

	// === MAIN LOOP START ===
	glutMainLoop();
	return 0;
}