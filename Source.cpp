#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

using namespace std;

#define PI 3.14159265f


void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void drawTentacle(float rotation, float len, float width, float x, float y, float orientation);
void drawCircle(float radius, int steps, float circleIncrement, float x, float y);

int main() {
	float rotation = 0.5f;
	float rotationIncrement = 0.5f;
	int steps = 100;
	float circleIncrement = 2.0f * PI / steps;

	cout << "Program Start" << endl;

	if (!glfwInit()) {
		cout << "GLFW Init Error" << endl;
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 800, "Octopus Sim", NULL, NULL);

	if (window == NULL) {
		cout << "GLFW Window Error" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.8f, 0.15f, 0.3f);
		drawCircle(0.35f, steps, circleIncrement, 0.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);
		drawCircle(0.05f, steps, circleIncrement, -0.15, 0.15);
		drawCircle(0.05f, steps, circleIncrement, 0.15, 0.15);

		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.025f, steps, circleIncrement, -0.15, 0.15);
		drawCircle(0.025f, steps, circleIncrement, 0.15, 0.15);

		drawTentacle(rotation, 0.55f, 0.08f, 0.133f, 0.322f, -22.5f);
		drawTentacle(rotation, 0.55f, 0.08f, 0.322f, 0.133f, -67.5f);
		drawTentacle(rotation, 0.55f, 0.08f, 0.322f, -0.133f, -112.5f);
		drawTentacle(rotation, 0.55f, 0.08f, 0.133f, -0.322f, -157.5f);
		drawTentacle(rotation, 0.55f, 0.08f, -0.133f, -0.322f, -202.5f);
		drawTentacle(rotation, 0.55f, 0.08f, -0.322f, -0.133f, -247.5f);
		drawTentacle(rotation, 0.55f, 0.08f, -0.322f, 0.133f, -292.5f);
		drawTentacle(rotation, 0.55f, 0.08f, -0.133f, 0.322f, -337.5f);

		if (rotation >= 30.0f || rotation <= -30.0f) {
			rotationIncrement *= -1;
		}

		rotation += rotationIncrement;

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void drawTentacle(float rotation, float len, float width, float x, float y, float orientation) {
	float side = len / 2;
	float z2 = (2 * pow(side, 2)) - 2 * (pow(side, 2) * cos(rotation * PI / 180));
	float z = sqrt(z2);
	float alpha = 90 - (180 - rotation) / 2;
	float xd = z * cos(alpha * PI / 180);
	float yd = z * sin(alpha * PI / 180);
	//cout << z2 << endl << alpha << endl << x << endl << y << endl;

	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(orientation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x, -y, 0.0f);
	glPushMatrix();
	glTranslatef(x, y+side, 0.0f);

	if (rotation > 0) {
		glTranslatef(-xd, -yd, 0.0f);
	}
	else {
		glTranslatef(xd, yd, 0.0f);
	}
	glRotatef((-2 * rotation), 0.0f, 0.0f, 1.f);

	glTranslatef(-x, -(y+side), 0.0f);

	glColor3f(0.8f, 0.15f, 0.3f);
	drawTriangle((x - width / 2), (y + side), x, y+len, (x + width / 2), (y + side));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.f);
	glTranslatef(-x, -y, 0.0f);
	drawQuad((x - width / 2), (y + side), (x + width / 2), (y + side), (x + width / 2), y, (x - width / 2), y);
	glPopMatrix();
	glPopMatrix();
}

void drawCircle(float radius, int steps, float circleIncrement, float x, float y) {
	float newX, newY;
	float prevX = 0;
	float prevY = 0;

	for (int i = 0; i <= steps; i++) {
		newX = radius * sin(circleIncrement * i);
		newY = radius * cos(circleIncrement * i);

		glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(prevX, prevY);
		glVertex2f(newX, newY);
		glEnd();
		glPopMatrix();

		prevX = newX;
		prevY = newY;
	}
}