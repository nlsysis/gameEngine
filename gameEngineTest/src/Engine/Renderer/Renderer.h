#pragma once

namespace Engine
{
	enum RendererAPI
	{
		None = 0, OpenGL = 1, DirectX3D11 = 2};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RenderAPI; }
	private:
		static RendererAPI s_RenderAPI;
	};
}
