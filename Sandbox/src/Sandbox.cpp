#include <Engine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Engine::Layer 
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera( -2.0f, 2.0f, -2.0f, 2.0f ), m_CameraPosition(0.0f), m_ModelPosition(0.0f)
	{
		m_VertexArray.reset(Engine::VertexArray::Create());

		float vertices[3 * 7]
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
		};
		Engine::Ref<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "a_Position"},
			{ Engine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Engine::Ref<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;;
			
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Engine::Shader::Create(vertexSrc, fragmentSrc));
	}
	 
	void OnUpdate(float ts) override
	{
		if (Engine::Input::IsKeyPressed(EG_KEY_LEFT))
		{
			m_CameraPosition.x += m_MoveSpeed * ts;
		}
		else if (Engine::Input::IsKeyPressed(EG_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_MoveSpeed * ts;
		}

		if (Engine::Input::IsKeyPressed(EG_KEY_UP))
		{
			m_CameraPosition.y -= m_MoveSpeed * ts;
		}
		else if (Engine::Input::IsKeyPressed(EG_KEY_DOWN))
		{
			m_CameraPosition.y += m_MoveSpeed * ts;
		}

		if (Engine::Input::IsKeyPressed(EG_KEY_A))
			m_Rotation += 180.0f * ts;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_Rotation);

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Engine::RenderCommand::Clear();

		Engine::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_ModelPosition);
		Engine::Renderer::Submit(m_Shader, m_VertexArray, transform);

		Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender()
	{
	}

	void OnEvent(Engine::Event& event) override
	{
	//	EG_TRACE("{0}", event);
	}

private:
	Engine::Ref<Engine::Shader> m_Shader;
	Engine::Ref<Engine::VertexArray> m_VertexArray;

	Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_MoveSpeed = 2.0f;

	float m_Rotation = 0.0f;

	glm::vec3 m_ModelPosition;

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