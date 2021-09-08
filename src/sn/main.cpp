#ifndef MAIN_CPP
#define MAIN_CPP

#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //!_CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <cstdlib>

#include <iostream>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <glm/glm.hpp>
#include <sn/window.hpp>

int main(int argc, char **argv)
{
	std::vector<glm::vec4> teapot_vertice{};

	sn::Window window;


	while (!window.ShouldClose())// Game loop
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear the colorbuffer
														   // Render & Draw the triangles

		window.swap();// Swap the screen buffers
	}
	// Properly de-allocate all resources once they've outlived their purpose

	
	boost::numeric::ublas::matrix<float> m1(4, 3), m2(3, 2);
	for (unsigned i = 0; i < m1.size1(); ++i)
		for (unsigned j = 0; j < m1.size2(); ++j)
			m1(i, j) = 2 * i + j;
	std::cout << "m1 = " << m1 << '\n';

	for (unsigned i = 0; i < m2.size1(); ++i)
		for (unsigned j = 0; j < m2.size2(); ++j)
			m2(i, j) = i + j + 1;
	std::cout << "m2 = " << m2 << '\n';

	std::cout << "prod(m1, m2) = " << prod(m1, m2) << '\n';
	auto directory_path = "./";
	boost::filesystem::path dir_path(directory_path);
	auto is_path = boost::filesystem::is_directory(dir_path);
	if (!is_path) {
		std::cout << dir_path << "is not a path\n";
	}
	else {
		std::string temp_chars;
		for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(dir_path), {})) {
			auto temp_path = entry.path();
			std::cout << temp_path.string() << '\n';
		}
	}
	system("PAUSE");

}

#endif //!MAIN_CPP
