// Include standard headers
#include "..\stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "loadShader.hpp"
#include "input.h"
#include "common.h"

std::vector <GLfloat> g_vertex_buffer_data;
int point_count;
color_palette color_toggle;
GLfloat color_object[3] = {1.0, 1.0, 0};
std::vector <GLfloat> color_vector;

int main()
{
	point_count = 0;
	color_toggle = red;
	glewExperimental = true; // Needed for core profile
	GLfloat color_pick_square[36] = {
		-0.98, 0.9, 0,
		-0.95, 0.9, 0,
		-0.98, 0.85, 0,
		-0.95, 0.85, 0,
		-0.98, 0.83, 0,
		-0.95, 0.83, 0,
		-0.98, 0.78, 0,
		-0.95, 0.78, 0,
		-0.98, 0.76, 0,
		-0.95, 0.76, 0,
		-0.98, 0.71, 0,
		-0.95, 0.71, 0
	};

	int color_pick_square_size = *(&color_pick_square + 1) - color_pick_square;

	for (int i = 0; i < color_pick_square_size; i++)
	{
		g_vertex_buffer_data.push_back(color_pick_square[i]);
	}

	if (!glfwInit()) 
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(1920, 1080, "SBrush", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW

	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("C:\\code\\SBrush\\SBrush\\src\\SimpleVertexShader.vertexshader", "C:\\code\\SBrush\\SBrush\\src\\SimpleFragmentShader.fragmentshader");

	do {
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Give vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(float), &g_vertex_buffer_data[0], GL_STATIC_DRAW);

		// Use shader.
		glUseProgram(programID);
		GLint uniform = glGetUniformLocation(programID, "color");

		//Set mouse callback
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		//Draw the color pick squares.
		//Red.
		glUniform3f(uniform, 1.0, 0.0, 0.0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 3);
		//Green.
		glUniform3f(uniform, 0.0, 1.0, 0.0);
		glDrawArrays(GL_TRIANGLES, 4, 3);
		glDrawArrays(GL_TRIANGLES, 5, 3);
		//Blue.
		glUniform3f(uniform, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLES, 8, 3);
		glDrawArrays(GL_TRIANGLES, 9, 3);

		// Draw the points.
		if (point_count > 0)
		{
			for (int i = 0; i < point_count; i++)
			{
				glUniform3f(uniform, color_vector.at(i*3), color_vector.at(i * 3 +1), color_vector.at(i * 3+2));
				glDrawArrays(GL_POINTS, i + color_pick_square_size, 1);
			}
		}

		glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
