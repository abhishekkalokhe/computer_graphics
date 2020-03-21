#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 1.0f);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.14159265358979f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{

		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		int x = xpos;
		int y = ypos;

		DrawCircle(((x - 320.00) / 320.00), ((-y + 240.00) / 240), 0.2, 1000);
		//DrawCircle(0, 0, 0.2, 1000);
		printf("Cursor Position at x= %d and y= %d \n", x, y);

		/*while (true) {
			if (glfwGetTime() > lasttime + 1) {
				glClear(GL_COLOR_BUFFER_BIT);
				printf("H\n");
				break;
			}
		}*/
	}
}


int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	glClear(GL_COLOR_BUFFER_BIT);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "CircleOnClick", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	while (!glfwWindowShouldClose(window))
	{



		glfwSwapBuffers(window);
		glfwPollEvents();
		//glfwWaitEvents();
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);


	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}