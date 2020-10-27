#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Engine 
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		//Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintcolor, float tillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintcolor, float tillingFactor = 1.0f);

		static void DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotationQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintcolor, float tillingFactor = 1.0f);
		static void DrawRotationQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintcolor, float tillingFactor = 1.0f);
	};
}