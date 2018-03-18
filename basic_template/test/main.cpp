#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

const std::string WINDOW_TITLE = "BASIC TEMPLATE";

// Static utility function for reading files and returns string. Used for reading .vsh and .vsf
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
		contents[i] = 0;
	}

	fread(contents, 1, file_length, fp);

	contents[file_length + 1] = '\0';
	fclose(fp);

	return contents;
}

// Function for resizing window. Put in "glutReshapeFunc"
void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
}

// the "paint" method
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	// Initializes GLUT
	glutInit(&argc, argv);

	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Set window size
	glutInitWindowSize(800, 600);

	// Create the window with the title "Hello Fariz"
	glutCreateWindow(WINDOW_TITLE.data());

	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	// Needed to call OpenGL functions
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error");
		return 1;
	}

	// Start up the loop
	glutMainLoop();
	return 0;
}