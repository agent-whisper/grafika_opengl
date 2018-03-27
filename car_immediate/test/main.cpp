#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>

using namespace std;

void changeViewPort(int w, int h);
void renderDrawing();
void drawCircle(float x, float y, float radius);
void drawCity();
void drawCar(GLfloat dx, GLfloat dy);
void drawRoad();

const string WINDOW_TITLE = "Task 1 - Draw car with immediate";
const float DELTA = .003f;

float position = -2.0f;

int main(int argc, char** argv) {
	
	// === GLUT INITIALIZATION ===
	glutInit(&argc, argv); // Initializes GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Set up some memory buffers for our display
	glutInitWindowSize(600, 600); // Set window size
	glutCreateWindow(WINDOW_TITLE.data()); // Create the window with the title "Hello Fariz"

	// Bind the window functions to the actual window
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(renderDrawing);

	// Needed to call OpenGL functions
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error");
		return 1;
	}

	// === MAIN LOOP START ===
	glutMainLoop();
	return 0;
}

// =========================================================================================

// Window Functions: Function for resizing window. Put in "glutReshapeFunc"
void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
}

void renderDrawing() {
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10.0f);
	printf("a\n");
	drawCity();
	drawRoad();
	drawCar(position, .0f);
	glutSwapBuffers();

	position += DELTA;
	if (position > 3)
		position = -2.f;

	glutPostRedisplay();
}

void drawCircle(float x, float y, float radius) {
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

void drawCity() {
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

void drawCar(GLfloat dx, GLfloat dy) {
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
	drawCircle(dx + -0.8f, dy + -0.2f, 0.14f);
	drawCircle(dx + 0.0f, dy + -0.2f, 0.14f);
	glColor3f(0.2f, 0.2f, 0.2f);
	drawCircle(dx + -0.8f, dy + -0.2f, 0.08f);
	drawCircle(dx + 0.0f, dy + -0.2f, 0.08f);
}

void drawRoad() {
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

// =========================================================================================