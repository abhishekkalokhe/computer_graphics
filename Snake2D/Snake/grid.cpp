#include <iostream>
#include<GLFW/glfw3.h>
#include "grid.h"


void drawGrid()		//Function to draw the complete grid
{
	for (float i = -1; i < 1; i = i + 0.1)
	{
		for (float j = -1; j < 1; j = j + 0.1)
		{
			unit(i, j);
		}
}
	
}

void unit(float x, float y)		//Function to draw unit square
{
	glLineWidth(1);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x+0.1, y);
	glVertex2f(x+0.1, y+0.1);
	glVertex2f(x, y+0.1);

	glEnd();
}