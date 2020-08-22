#pragma once

#include "Engine/Layer.h"

#include "Engine/Event/ApplicationEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/KeyEvent.h"

namespace Engine
{
	class  EG_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}