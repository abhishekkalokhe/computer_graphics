#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

// Acknowldgement: 
// This code is an adapted version of the original source code
// published on the LearnOpenGL.com (Downloaded date - 5th April 2020)


using namespace std::chrono;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int N_CURVE_PTS = 3;  // change N_CURVE_PTS= 1001 for actual implementation
float controlPts[] = { -0.50f, 0.25f, 0.0f, -0.25f, 0.75f, 0.0f, 0.25f, 0.50f, 0.0f, 0.50, 0.00f, 0.0f };
// Note that it is normalized coordinate space; ideally control polygon can come from user clicks.

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void getVertices_bez3DeCasteljau(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter deCasteljau code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	vertices[0] = -0.5f;   //vertex#1 x value
	vertices[1] = -0.5f;   //vertex#1 y value
	vertices[2] = 0.0f;    //vertex#1 z value
	vertices[3] = 0.5f;    //vertex#2 x value
	vertices[4] = -0.5f;   //vertex#2 y value
	vertices[5] = 0.0f;    //vertex#2 z value  ... and so on
	vertices[6] = 0.0f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;

}
void getVertices_bez3Mat(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter debez3Mat code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	vertices[0] = -0.5f;   //vertex#1 x value
	vertices[1] = -0.5f;   //vertex#1 y value
	vertices[2] = 0.0f;    //vertex#1 z value
	vertices[3] = 0.5f;    //vertex#2 x value
	vertices[4] = -0.5f;   //vertex#2 y value
	vertices[5] = 0.0f;    //vertex#2 z value  ... and so on
	vertices[6] = 0.0f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;

}
void getVertices_bez3Horner(unsigned int N_CURVE_PTS, float* vertices) {
	// Enter deHorner code here in place of hardcoded values with N_CURVE_PTS 1001 or greater
	vertices[0] = -0.5f;   //vertex#1 x value
	vertices[1] = -0.5f;   //vertex#1 y value
	vertices[2] = 0.0f;    //vertex#1 z value
	vertices[3] = 0.5f;    //vertex#2 x value
	vertices[4] = -0.5f;   //vertex#2 y value
	vertices[5] = 0.0f;    //vertex#2 z value  ... and so on
	vertices[6] = 0.0f;
	vertices[7] = 0.5f;
	vertices[8] = 0.0f;

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	/*
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
	};
	*/

	//Set up geometry inputs
	unsigned int chunkSzBytes = N_CURVE_PTS * 3 * sizeof(float);
	float *vertices = (float*)malloc(chunkSzBytes);   //note that malloc always should come with corresponding free() at the end

	auto start = high_resolution_clock::now();  //Note need C++11 and #include <chrono> using namespace std::chrono

	getVertices_bez3DeCasteljau(N_CURVE_PTS, vertices);

	auto stop_1 = high_resolution_clock::now();

	getVertices_bez3Mat(N_CURVE_PTS, vertices);

	auto stop_2 = high_resolution_clock::now();

	getVertices_bez3Horner(N_CURVE_PTS, vertices);

	auto stop_3 = high_resolution_clock::now();

	auto duration_bez3DeCasteljau = duration_cast<microseconds>(stop_1 - start);
	std::cout << "de Casteljau time (ms)=  " << duration_bez3DeCasteljau.count() << std::endl;

	auto duration_bez3Mat = duration_cast<microseconds>(stop_2 - stop_1);
	std::cout << "bezMat time (ms)=  " << duration_bez3Mat.count() << std::endl;

	auto duration_bez3Horner = duration_cast<microseconds>(stop_3 - stop_2);
	std::cout << "Horner time (ms)=  " << duration_bez3Horner.count() << std::endl;

	//std::cout << vertices[0] << " " << vertices[1] << " " << vertices[2] << "\n" << vertices[3] << " " << vertices[4] << " " << vertices[5] << " " << std::endl;


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, chunkSzBytes, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_LINE_STRIP, 0, 3);
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	//free(vertices);
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}