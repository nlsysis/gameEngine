#pragma once

#ifdef EG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	EG_PROFILE_BEGIN_SESSION("Startup", "Startup.json");
	auto app = Engine::CreateApplication();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Runtime", "Runtime.json");
	app->Run();
	EG_PROFILE_END_SESSION();

	EG_PROFILE_BEGIN_SESSION("Startup","Shutdown.json");
	delete app;
	EG_PROFILE_END_SESSION();
}

#endif