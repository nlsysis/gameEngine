#pragma once

#include "Engine.h"

class Sandbox2D : public Engine::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float timestep) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Engine::Event& event) override;
private:
	Engine::OrthographicCameraController m_CameraController;
	
	Engine::Ref<Engine::Texture2D> m_CheckboardTexture;
	Engine::Ref<Engine::Texture2D> m_SpriteSheet;
	Engine::Ref<Engine::SubTexture2D> m_SpriteStairs;
	Engine::Ref<Engine::VertexArray> m_SquareVA;
	Engine::Ref<Engine::Shader> m_FlatColorShader;

	Engine::Ref<Engine::Framebuffer> m_Framebuffer;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec2 m_Viewportsize = {0.0f, 0.0f};
};