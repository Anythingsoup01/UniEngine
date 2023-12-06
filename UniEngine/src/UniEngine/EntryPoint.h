#pragma once

#ifdef UE_PLATFORM_WINDOWS

extern UE::Application* UE::CreateApplication();

int main(int argc, char** argv) {

	UE::Log::Init();
	UE_CORE_FATAL("FATAL ERROR HAS OCCURED");
	UE_INFO("Ignore that guy, he's a drama queen");

	auto app = UE::CreateApplication();
	app->Run();
	delete app;
	
	}

#endif