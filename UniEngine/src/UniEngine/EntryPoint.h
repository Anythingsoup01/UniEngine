#pragma once

#ifdef UE_PLATFORM_WINDOWS

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv) {

	UE::Log::Init();

	auto app = UE::CreateApplication();
	app->Run();
	delete app;
	
	}

#endif