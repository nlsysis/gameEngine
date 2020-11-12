#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Engine::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");

	m_SpriteStairs = Engine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, {1, 2});

	m_CameraController.SetZoomlevel(5.0f);
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(float timestep)
{
	EG_PROFILE_FUNCTION();

	//update
	{	
		EG_PROFILE_SCOPE("Sandbox2D::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	//Render
	Engine::Renderer2D::ResetStats();
	{
		EG_PROFILE_SCOPE("Sandbox2D::Render");
		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		EG_PROFILE_SCOPE("Sandbox2D::Begin Render");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Engine::Renderer2D::DrawQuad({ 0.0f,-0.5f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.0f,0.8f }, { 0.6f, 1.0f }, { 0.8f, 0.2f, 0.8f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.6f,0.3f }, { 0.6f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Engine::Renderer2D::DrawRotationQuad({ 0.6f,0.3f }, { 0.6f, 0.5f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.1f,0.3f, -0.1f}, { 0.8f, 0.5f }, m_CheckboardTexture, glm::vec4(1.0f, 0.3f, 0.6f, 1.0f), 1.0f);
		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 2.0f }, m_SpriteStairs, glm::vec4(1.0f, 0.3f, 0.6f, 1.0f), 1.0f);
		Engine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Statistics");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& event)
{
	m_CameraController.OnEvent(event);
}
