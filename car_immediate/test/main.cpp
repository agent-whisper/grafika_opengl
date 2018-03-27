#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>

using namespace std;

void changeViewPort(int w, int h);
void renderDrawing();
void drawCircle(float x, float y, float radius);
void drawCity(float dx);
void drawCar(GLfloat dx, GLfloat dy);
void drawRoad(float dx);
float getRandomFloat(float Lo, float HI);

const string WINDOW_TITLE = "Task 1 - Draw car with immediate";
const float DELTA = .006f;

float position = -2.0f;
float positionBuilding = 0.0f;
float buildingHeight[11];
float buildingWidth = 0.2;
int hour = 0;

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

	drawCity(positionBuilding);
	drawRoad(-position);
	drawCar(position, .0f);
	glutSwapBuffers();

	position += DELTA;
	if (position > 2)
		position = -2.0f;
	hour++;

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

void drawCity(float dx) {
	glColor3f(0.2f, 0.2f, 1.0f);
	
	if (hour == 0) {
		for (int i = 0; i < 11; i++) {
			buildingHeight[i] = getRandomFloat(0.3f, 0.8f);
		}
	}

	int j = 0;
	for (float i = -1.0f; i < 1.2f; i+=buildingWidth) {
		glBegin(GL_POLYGON);
		glVertex2f(positionBuilding+i, 0.0f);
		glVertex2f(positionBuilding+i, buildingHeight[j]);
		glVertex2f(positionBuilding+i+buildingWidth, buildingHeight[j]);
		glVertex2f(positionBuilding+i+buildingWidth, 0.0f);
		glEnd();
		j++;
	}

	positionBuilding -= DELTA / 3;

	if (positionBuilding < -buildingWidth) {
		for (int i = 0; i < 10; i++) {
			buildingHeight[i] = buildingHeight[i+1];
		}
		buildingHeight[10] = getRandomFloat(0.3f, 0.8f);
		positionBuilding = 0.0f;
	}

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

void drawRoad(float dx) {
	glColor3f(0.13f, 0.13f, 0.13f);

	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();

	glColor3f(1, 1, 1);

	// panjang = 1.0 // tinggi = 0.1 // gradien = 0.05 // margin = 0.4
	float base = dx - 4.0f;
	for (float i = base; i < 1.0f; i += 1.0f) {
		glBegin(GL_POLYGON);
		glVertex2f(i, -0.35f);
		glVertex2f(i + 0.6, -0.35f);
		glVertex2f(i + 0.65f, -0.45f);
		glVertex2f(i + 0.05f, -0.45f);
		glEnd();
	}

}

float getRandomFloat(float LO, float HI) {
	float r = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
	return r;
}

// =========================================================================================