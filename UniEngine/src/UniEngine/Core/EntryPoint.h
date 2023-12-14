#pragma once

#ifdef UE_PLATFORM_WINDOWS

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv)
{
	UE::Log::Init();
	UE_CORE_WARN("Initialized Log!");
	int a = 5;
	UE_INFO("Hello! Var={0}", a);

	auto app = UE::CreateApplication();
	app->Run();
	delete app;
}

#endif