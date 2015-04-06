#include <Dungeon/OpenGL.hpp>
#include <Dungeon/Common.hpp>
#include <Dungeon/ShaderProgram.hpp>
#include <Dungeon/Texture.hpp>
#include <Dungeon/Clock.hpp>
#include <Dungeon/TickCounter.hpp>
#include <Dungeon/Math.hpp>
#include <Dungeon/Color.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Vertex
{
	Dungeon::Vector2 position;
	Dungeon::Color color;
	Dungeon::Vector2 texCoord;
};

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;
GLOBAL const char* g_windowTitle = "Dungeon";

INTERNAL void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

INTERNAL void render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(0));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid *)(sizeof(Dungeon::Vector2)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(sizeof(Dungeon::Vector2) + sizeof(float)));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

INTERNAL void handleInput(GLFWwindow *window, bool *running, bool *fullscreen)
{
	if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
		*running = false;

	/*if (glfwGetKey(window, GLFW_KEY_F11))
	{
		GLFWwindow *newWindow;
		glfwHints();

		*fullscreen = !*fullscreen;
		if (*fullscreen)
		{
			const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			newWindow = glfwCreateWindow(mode->width, mode->height, g_windowTitle, glfwGetPrimaryMonitor(), window);
		}
		else
			newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowTitle, nullptr, window);

		glfwDestroyWindow(window);
		window = newWindow;
		glfwMakeContextCurrent(window);
	}*/
}

int main(int argc, char** argv)
{
	GLFWwindow *window;

	if (!glfwInit())
		return EXIT_FAILURE;

	window = glfwCreateWindow(g_windowWidth, g_windowHeight, g_windowTitle, nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwHints();

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit())
		return EXIT_FAILURE;

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Vertex vertices[] = {
		{ { +0.5f, +0.5f }, { 255, 255, 255, 255 }, { 1.0f, 0.0f } }, // Vertex 0
		{ { -0.5f, +0.5f }, { 255,   0,   0, 255 }, { 0.0f, 0.0f } }, // Vertex 1
		{ { +0.5f, -0.5f }, {   0, 255,   0, 255 }, { 1.0f, 1.0f } }, // Vertex 2
		{ { -0.5f, -0.5f }, {   0,   0, 255, 255 }, { 0.0f, 1.0f } }, // Vertex 3
	};

	GLuint vbo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Dungeon::ShaderProgram shaderProgram;
	if (!shaderProgram.attachShaderFromFile(Dungeon::ShaderType::Vertex, "data/shaders/default.vert.glsl"))
		throw std::runtime_error(shaderProgram.getErrorLog());
	if (!shaderProgram.attachShaderFromFile(Dungeon::ShaderType::Fragment, "data/shaders/default.frag.glsl"))
		throw std::runtime_error(shaderProgram.getErrorLog());
	shaderProgram.bindAttribLocation(0, "vertPosition");
	shaderProgram.bindAttribLocation(1, "vertColor");
	shaderProgram.bindAttribLocation(2, "vertTexCoord");
	if (!shaderProgram.link())
		throw std::runtime_error(shaderProgram.getErrorLog());
	shaderProgram.use();

	Dungeon::Texture texture;
	texture.loadFromFile("data/textures/kitten.jpg");
	texture.bind(0);

	shaderProgram.setUniform("uniTex", 0);

	bool running = true;
	bool fullscreen = false;

	Dungeon::TickCounter tc;

	while (running)
	{
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}
		
		if (tc.update(1))
		{
			std::cout << tc.getTickRate() << std::endl;
			std::stringstream ss;
			ss << g_windowTitle << " - ms/frame: " << 1000.0 / tc.getTickRate() << "ms";
			glfwSetWindowTitle(window, ss.str().c_str());
		}

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		handleInput(window, &running, &fullscreen);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}