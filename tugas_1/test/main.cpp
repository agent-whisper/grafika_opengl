#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const std::string WINDOW_TITLE = "BASIC TEMPLATE";

// =========================================================================================

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

// Window Functions
void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
} // Function for resizing window. Put in "glutReshapeFunc"

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	// === SHADER INITIALIZATION ===
	/*

	The standard code structure is as follow:

	char *vertexShaderSourceCode = readFile("vertex.vsh"); // Loads the vertex shader source file
	char *fragmentShaderSourceCode = readFile("fragment.vsh"); // Loads the fragment shader source file
	GLuint vertShaderID = makeVertexShader(vertexShaderSourceCode); // Generate the vertex shader ID
	GLuint fragShaderID = makeFragmentShader(fragmentShaderSourceCode); // Generate the fragment shader ID
	GLuint shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID); // Generate the shader program ID
	glUseProgram(shaderProgramID); // Use the shader program in the main program
	glDeleteProgram(shaderProgramID); // Free the shader program resources

	*/
	// === MAIN LOOP START ===
	glutMainLoop();
	return 0;
}