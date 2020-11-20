#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Engine::Texture2D::Create("assets/textures/RPGpack_sheet_2X.png");

	m_SpriteStairs = Engine::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, {1, 2});

	m_CameraController.SetZoomlevel(5.0f);

	Engine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Engine::Framebuffer::Create(fbSpec);
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
		m_Framebuffer->Bind();
		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Engine::RenderCommand::Clear();
	}

	{
		EG_PROFILE_SCOPE("Sandbox2D::Begin Render");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Engine::Renderer2D::DrawQuad({ 0.0f,-0.5f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.0f,0.8f }, { 0.6f, 1.0f }, { 0.8f, 0.2f, 0.8f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.6f,0.3f }, { 0.6f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Engine::Renderer2D::DrawRotationQuad({ 0.6f,0.3f }, { 0.6f, 0.5f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		//Engine::Renderer2D::DrawQuad({ 0.1f,0.3f, -0.1f}, { 0.8f, 0.5f }, m_CheckboardTexture, glm::vec4(1.0f, 0.3f, 0.6f, 1.0f), 1.0f);
		Engine::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 2.0f }, m_SpriteStairs, glm::vec4(1.0f, 0.3f, 0.6f, 1.0f), 1.0f);
		Engine::Renderer2D::EndScene();
		m_Framebuffer->UnBind();
	}
}

void Sandbox2D::OnImGuiRender()
{
	static bool dockSpaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

			if (ImGui::MenuItem("Exit")) Engine::Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Settings");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Statistics");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_Viewportsize != *((glm::vec2*)&viewportPanelSize))
	{
		//recreating framebuffer
		m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		m_Viewportsize = { viewportPanelSize.x, viewportPanelSize.y };
		m_CameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
	}
	uint32_t texture = m_Framebuffer->GetColorAttachmentRendererID();
	ImGui::Image((void*)texture, ImVec2{ m_Viewportsize.x, m_Viewportsize.y }, ImVec2{ 0, 1 }, ImVec2{1, 0});

	ImGui::End();
	ImGui::PopStyleVar();

	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& event)
{
	m_CameraController.OnEvent(event);
}
