#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>

const std::string WINDOW_TITLE = "Tugas 1";

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