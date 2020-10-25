#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	EG_CORE_WARN("Initial");
	int a = 5;
	EG_INFO("logto! Var = {0}",a);

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif