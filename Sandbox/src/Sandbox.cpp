#include <Engine.h>

#include "imgui/imgui.h"

class ExampleLayer : public Engine::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")
	{}
	 
	void OnUpdate() override
	{
	//	EG_INFO("ExampleLayer::Update");

		if (Engine::Input::IsKeyPressed(EG_KEY_TAB))
			EG_TRACE("Key is pressed!!!!");
	}

	virtual void OnImGuiRender()
	{
	//	ImGui::NewFrame();
		ImGui::Begin("Test");
		
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Engine::Event& event) override
	{
	//	EG_TRACE("{0}", event);
	}

};
class Sandbox : public Engine::Application 
{
public:
	Sandbox()
	{ 
		PushLayer(new ExampleLayer()); 
	}
	~Sandbox() {}
};

///Create new class instance.
Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}