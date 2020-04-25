#include <Engine.h>

class Sandbox : public Engine::Application 
{
public:
	Sandbox() {}
	~Sandbox() {}
};

///Create new class instance.
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}