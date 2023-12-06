#include <UniHeaders.h>

class Sandbox : public UE::Application {
public:
	Sandbox() {}
	~Sandbox() {}

};

UE::Application* UE::CreateApplication() {
	return new Sandbox();
}