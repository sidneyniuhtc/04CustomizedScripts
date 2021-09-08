#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

namespace sn {
	class Window
	{
	public:
		Window();
		~Window();
		bool ShouldClose();
		void swap();
	private:
		int WIDTH;
		int HEIGHT;
		void init();
		GLFWwindow* window;

	};
}
#endif // !WINDOW_HPP