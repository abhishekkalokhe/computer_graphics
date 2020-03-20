#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <utility>
#include"grid.h"
#include "vector"

std::pair<float, float> generateFood();
void drawFood(std::pair<float, float> p);
std::pair<float, float> updateSnakePos(float a, float b, int olddir, int k);
void updateSnake(std::pair<float, float> p);




static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	

}


int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);	//Failed to initialise EXIT
	window = glfwCreateWindow(700, 700, "Snake2D", NULL, NULL);	//Create Window
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);		//Terminate if no window appears
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	drawGrid();

	float index = 0;
	bool eaten = false;
	generateFood();	//Initial Food Position
	std::pair<float, float> foodpos = generateFood();	//Update New food Position
	std::pair<float, float> oldfoodpos; //Define old food position
	
	int olddir = 1;		//Initialise variable for Old Direction of Movement
	int newdir = 1;		//Initialise variable for New Direction of Movement after keypress
	int score = 0;		//Initialise score
	std::pair<float, float> snakepos = { 0, 0 };		//Initial snake head position

	// Array of positions(pairs(x, y))
	std::vector<std::pair<float, float>> arr;
	arr.push_back(std::make_pair(0, 0));		//Initialise the array

	while (!glfwWindowShouldClose(window))		//While Loop
	{	

		glClear(GL_COLOR_BUFFER_BIT);	//clear previous window
		drawGrid();						//Draw Grid
		double lasttime = glfwGetTime();	//Saves current time in seconds
		
		drawFood(foodpos);		// Draw food according to food position

		olddir = newdir;		//Chnaging the old direction after the loop
		//printf("%f => %f\n", foodpos.first, foodpos.second);

		snakepos = arr[0];	//Assigning position of head
		//printf("%f --- %f\n", snakepos.first, snakepos.second);
		
		if (eaten) {
			arr.push_back(oldfoodpos);	//If the food is eaten in previous frame Add the food position to the array
			eaten = false;		//change to false
		}


		//To check if the snake eats the food
		if (((snakepos.first < foodpos.first + 0.0001) && (snakepos.first > foodpos.first - 0.0001)) && ((snakepos.second > foodpos.second - 0.0001) && (snakepos.second < foodpos.second + 0.0001))){
			//printf("OK");

			// Add below
			eaten = true;
			oldfoodpos = foodpos;		//save the food position to add into the snake array
			foodpos = generateFood();	//Generate new food position
			score += 1;		//Increase the score by specific value
		}


		//if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			//foodpos = generateFood();
		//}
		
		
		
		// Move rest of snake
		for (int i = arr.size() - 1; i > 0; --i) {
			arr[i] = arr[i - 1];
		}
		arr[0] = updateSnakePos(arr[0].first, arr[0].second, olddir, newdir);
		


		// Draw the snake
		for (int i = 0; i < arr.size(); ++i) {
			updateSnake(arr[i]);
		}
	
		//glColor3f(0.0f, 0.0f, 0.0f);
		//glRectf(index, 0, index + 0.1, 0.1);


		//if (index >= 1) { index = 0; }
		//index=index+0.01;
		

		/*if (i % 100 == 0) {
			generateFood();
		}

		i++;*/
		

		//Add delay in the frames and take the key inputs during the delay
		// Keys W, A, S and D are used for the movement of the snake
		while (glfwGetTime() < lasttime + 0.2) {
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				newdir = 1;
			}
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				newdir = 2;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				newdir = 3;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				newdir = 4;
			}
		}

	
		
		glfwPollEvents();
		glfwSwapBuffers(window);		//Swap the windows
		//glfwWaitEvents();
		//glfwSetKeyCallback(window, key_callback);
		

	}

	printf("Score: %d", score);		//Print the score in Terminal
	glfwDestroyWindow(window);		//Destroy the window
	glfwTerminate();			//Terminate GLFW
	exit(EXIT_SUCCESS);
}


//Function to generate Food at random places

// Make the random number lie between -1 and +1
std::pair<float, float> generateFood() {
	float xran, yran;
	float ran1 = (rand() % 10) / 10.00;		
	int ran2 = (rand() % 2);
	if (ran2 == 0) {
		xran = ran1;
	}
	if (ran2 == 1) {
		xran = -ran1;
	}

	float ran3 = (rand() % 10) / 10.00;
	int ran4 = (rand() % 2);
	if (ran4 == 0) {
		yran = ran3;
	}
	if (ran4 == 1) {
		yran = -ran3;
	}
	return std::make_pair(xran, yran);		//return random position
}

void drawFood(std::pair<float, float> p)	//Function to draw food by taking the random food position
{
	float xran = p.first;
	float yran = p.second;
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glRectf(xran, yran, xran + 0.1, yran + 0.1);

	//printf("%f\n", yran);

}

std::pair<float, float> updateSnakePos(float a, float b, int olddir, int k)	//Function to update snake position w.r.t prev position, the direction of movement and keypress
{
	

	if (olddir == 1) {
		if (k == 2)
		{
			b = b + 0.1;
		}
		if (k == 4)
		{
			b = b - 0.1;
		}
		
		else { 
			if(a < 1){ a = a + 0.1; }
			else { a = -1; }
			 }
	}

	if (olddir == 2) {
		if (k == 1)
		{
			a = a + 0.1;
		}
		if (k == 3)
		{
			a = a - 0.1;
		}
		else {
			if (b < 1) { b = b + 0.1; }
			else { b = -1; }
		}
	}

	if (olddir == 3) {
		if (k == 2)
		{
			b = b + 0.1;
		}
		if (k == 4)
		{
			b = b - 0.1;
		}
		else {
			if (a > -1) { a = a - 0.1; }
			else { a = 1; }
		}
	}

	if (olddir == 4) {
		if (k == 1)
		{
			a = a + 0.1;
		}
		if (k == 3)
		{
			a = a - 0.1;
		}
		else {
			if (b > -1) { b = b - 0.1; }
			else { b = 1; }
		}
	}


	return std::make_pair(a, b);
}


//Function to draw the snake which needs position of snake

void updateSnake(std::pair<float,float> p)
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(p.first, p.second, p.first + 0.1, p.second + 0.1);

}