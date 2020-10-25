#include <Engine.h>

#include <Engine/Core/EntryPoint.h>
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"

class Sandbox : public Engine::Application 
{
public:
	Sandbox()
	{ 
		//PushLayer(new ExampleLayer()); 
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {}
};

///Create new class instance.
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}