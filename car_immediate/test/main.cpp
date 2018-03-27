#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const std::string WINDOW_TITLE = "BASIC TEMPLATE";

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLuint shaderProgramID;
GLuint vao = 0;
GLuint vbo;
GLuint positionID, colorID;

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

// Window Functions
void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
} // Function for resizing window. Put in "glutReshapeFunc"

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

// reference : https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
void DrawCircle(float x, float y, float radius)
{
	double twicePi = 2.0 * 3.142;
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glVertex2f(x, y); // center of circle
	for (int i = 0; i <= 20; i++) {
		glVertex2f(
			(x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
		);
	}
	glEnd(); //END
}

void draw_city() {
	glColor3f(0.2f, 0.2f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, 0.5f);
	glVertex2f(-0.8f, 0.5f);
	glVertex2f(-0.8f, 0.0f);
	glVertex2f(-1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.8f, 0.6f);
	glVertex2f(-0.6f, 0.64f);
	glVertex2f(-0.6f, 0.0f);
	glVertex2f(-0.8f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.6f, 0.4f);
	glVertex2f(-0.34f, 0.4f);
	glVertex2f(-0.34f, 0.0f);
	glVertex2f(-0.6f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.34f, 0.53f);
	glVertex2f(-0.1f, 0.53f);
	glVertex2f(-0.1f, 0.0f);
	glVertex2f(-0.34f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.07f, 0.48f);
	glVertex2f(-0.07f, 0.6f);
	glVertex2f(-0.07f, 0.0f);
	glVertex2f(-0.07f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(-0.1f, 0.6f);
	glVertex2f(0.15f, 0.4f);
	glVertex2f(0.15f, 0.0f);
	glVertex2f(-0.1f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.15f, 0.8f);
	glVertex2f(0.35f, 0.8f);
	glVertex2f(0.35f, 0.0f);
	glVertex2f(0.15f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.35f, 0.63f);
	glVertex2f(0.43f, 0.63f);
	glVertex2f(0.43f, 0.0f);
	glVertex2f(0.35f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.43f, 0.48f);
	glVertex2f(0.63f, 0.48f);
	glVertex2f(0.63f, 0.0f);
	glVertex2f(0.43f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.63f, 0.53f);
	glVertex2f(0.75f, 0.53f);
	glVertex2f(0.75f, 0.0f);
	glVertex2f(0.63f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.75f, 0.67f);
	glVertex2f(0.83f, 0.74f);
	glVertex2f(0.83f, 0.0f);
	glVertex2f(0.75f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.83f, 0.74f);
	glVertex2f(1.0f, 0.5f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.83f, 0.0f);
	glEnd();
}

void draw_car(GLfloat dx, GLfloat dy) {
	//glTranslatef(dx, dy, 0.0f);//move forward 4 units
	
	// car body
	glColor3f(1.0f, 0.0f, 0.0f); //red fill color
	glBegin(GL_POLYGON);
		glVertex3f(dx + -1.0f, dy + 0.1f, 0.0f);
		glVertex3f(dx + -0.85f, dy + 0.35f, 0.0f);
		glVertex3f(dx + -0.15f, dy + 0.35f, 0.0f);
		glVertex3f(dx + 0.0f, dy + 0.1f, 0.0f);
		glVertex3f(dx + 0.2f, dy + 0.1f, 0.0f);
		glVertex3f(dx + 0.3f, dy + 0.0f, 0.0f);
		glVertex3f(dx + 0.3f, dy + -0.2f, 0.0f);
		glVertex3f(dx + -1.0f, dy + -0.2f, 0.0f);
	glEnd();

	//middle window
	glColor3f(0.8f, 0.8f, 0.3f); //pale yellow fill color
	glBegin(GL_POLYGON);
		glVertex3f(dx + -0.74f, dy + 0.1f, 0.0f);
		glVertex3f(dx + -0.74f, dy + 0.3f, 0.0f);
		glVertex3f(dx + -0.43f, dy + 0.3f, 0.0f);
		glVertex3f(dx + -0.43f, dy + 0.1f, 0.0f);
	glEnd();

	// front window
	glBegin(GL_POLYGON);
		glVertex3f(dx + -0.4f, dy + 0.1f, 0.0f);
		glVertex3f(dx + -0.4f, dy + 0.3f, 0.0f);
		glVertex3f(dx + -0.16f, dy + 0.3f, 0.0f);
		glVertex3f(dx + -0.05f, dy + 0.1f, 0.0f);
	glEnd();

	// back window
	glBegin(GL_POLYGON);
		glVertex3f(dx + -0.77f, dy + 0.3f, 0.0f);
		glVertex3f(dx + -0.77f, dy + 0.1f, 0.0f);
		glVertex3f(dx + -0.95f, dy + 0.1f, 0.0f);
		glVertex3f(dx + -0.84f, dy + 0.3f, 0.0f);
	glEnd();

	// Headlight
	glColor3f(0.8f, 0.8f, 1.0f); //pale yellow fill color
	glBegin(GL_POLYGON);
		glVertex3f(dx + 0.22f, dy + 0.083f, 0.0f);
		glVertex3f(dx + 0.3f, dy + 0.009f, 0.0f);
		glVertex3f(dx + 0.19f, dy + 0.03f, 0.0f);
		glVertex3f(dx + 0.14f, dy + 0.085f, 0.0f);
	glEnd();

	// tires
	glColor3f(0.0f, 0.0f, 0.0f);
	DrawCircle(dx + -0.8f, dy + -0.2f, 0.14f);
	DrawCircle(dx + 0.0f, dy + -0.2f, 0.14f);
	glColor3f(0.2f, 0.2f, 0.2f);
	DrawCircle(dx + -0.8f, dy + -0.2f, 0.08f);
	DrawCircle(dx + 0.0f, dy + -0.2f, 0.08f);
}

void draw_road() {
	glColor3f(0.13f, 0.13f, 0.13f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(-0.75f, -0.35f);
	glVertex2f(-0.15f, -0.35f);
	glVertex2f(-0.1f, -0.45f);
	glVertex2f(-0.8f, -0.45f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.3f, -0.35f);
	glVertex2f(0.9f, -0.35f);
	glVertex2f(0.95f, -0.45f);
	glVertex2f(0.25f, -0.45f);
	glEnd();
}

void render2() {
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0f);
	draw_city();
	draw_road();
	draw_car(0.4f, -0.2f);
	glutSwapBuffers();
}
// =========================================================================================

int main(int argc, char** argv) {
	
	// === GLUT INITIALIZATION ===
	glutInit(&argc, argv); // Initializes GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Set up some memory buffers for our display
	glutInitWindowSize(600, 600); // Set window size
	glutCreateWindow(WINDOW_TITLE.data()); // Create the window with the title "Hello Fariz"

	// Bind the window functions to the actual window
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render2);

	// Needed to call OpenGL functions
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error");
		return 1;
	}

	/*
	// === VERTICES AND COLOR CONFIGURATIONS ===
	GLfloat vertices[] = { -0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.0f, 0.5f, 0.0f };
	GLfloat colors[] = { 1.0f, 0.0f, 0.0f, 1.0f,
						 1.0f, 0.0f, 0.0f, 1.0f,
						 1.0f, 0.0f, 0.0f, 1.0f };

	// === SHADER INITIALIZATION ===
	char *vertexShaderSourceCode = readFile("vertexShader.vsh"); // Loads the vertex shader source file
	char *fragmentShaderSourceCode = readFile("fragmentShader.fsh"); // Loads the fragment shader source file
	GLuint vertShaderID = makeVertexShader(vertexShaderSourceCode); // Generate the vertex shader ID
	GLuint fragShaderID = makeFragmentShader(fragmentShaderSourceCode); // Generate the fragment shader ID
	shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID); // Generate the shader program ID
	
	printf("vertexShaderID is %d\n", vertShaderID);
	printf("fragShaderID is %d\n", fragShaderID);
	printf("shaderProgramID is %d\n", shaderProgramID);
	printf("s_vPosition is %d\n", positionID);


	// === BUFFERS ===
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Create the buffer, but don't load anything yet
	glBufferData(GL_ARRAY_BUFFER, (7 * 3) * sizeof(GLfloat), NULL, GL_STATIC_DRAW); // 7 => one set of vertices (3 vertex + 4 color); 3 => number of vertices; Both forms a triangle

	// Load the vertex points
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * 3 * sizeof(GLfloat), vertices); // (type, starting address, length, the array)
	// Load the colors
	glBufferSubData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), 3 * 4 * sizeof(GLfloat), colors); // (type, starting address, length, the array)

	// Find the position of the variables in the shader
	positionID = glGetAttribLocation(shaderProgramID, "s_vPosition");
	colorID = glGetAttribLocation(shaderProgramID, "s_vColor");

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * 3 * sizeof(GLfloat)));
	glUseProgram(shaderProgramID);
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	*/
	// === MAIN LOOP START ===
	glutMainLoop();
	return 0;
}