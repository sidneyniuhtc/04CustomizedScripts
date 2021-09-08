#ifndef WINDOW_CPP
#define WINDOW_CPP

#include <sn/window.hpp>



#include <GLFW/glfw3.h>

sn::Window::Window(): WIDTH(800), HEIGHT(600)
{
	
	init();
	
	

}


void sn::Window::init()
{
	glfwInit();  // Init glfw
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(800, 600, "GLEW_glfw", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwMakeContextCurrent(window);

	// Set the required callback functions
	//glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	glViewport(0, 0, WIDTH, HEIGHT);  // Define the viewport dimensions
	glEnable(GL_DEPTH_TEST);

}

sn::Window::~Window()
{
	glfwTerminate();// Terminate GLFW, clearing any resources allocated by GLFW.
}

bool sn::Window::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void sn::Window::swap()
{
	glfwSwapBuffers(window);
}

#endif // !WINDOW_CPP