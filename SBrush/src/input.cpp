#include "input.h"
#include "draw.h"


bool left_mouse_state = false;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		return;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (xpos > 0 && ypos > 0) {
			addVertice((float)xpos, (float)ypos);
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (xpos > 0 && ypos > 0) {
			changeColor((float)xpos, (float)ypos);
			addVertice((float)xpos, (float)ypos);
		}
	}
}