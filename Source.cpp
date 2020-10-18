#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

int main() {
	float r = 0.5f;
	float c = 0.5f;

	cout << "Program Start" << endl;

	if (!glfwInit()) {
		cout << "GLFW Init Error" << endl;
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Octopus Sim", NULL, NULL);

	if (window == NULL) {
		cout << "GLFW Window Error" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		glPushMatrix();
		glRotatef(r, 0.0f, 0.0f, 0.01f);
		glColor3f(0.8f, 0.15f, 0.3f);
		drawTriangle(-0.05f, 0.0f, 0.0f, 0.75f, 0.05f, 0.0f);
		glPopMatrix();

		drawQuad(-0.048f, 0.02f, 0.048f, 0.02f, 0.06f, -0.8f, -0.06f, -0.8f);

		if (r >= 30.0f || r <= -30.0f) {
			c *= -1;
		}

		r += c;

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