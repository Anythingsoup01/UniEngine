#include "uepch.h"
#include "Layer.h"


namespace UE {
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}
	Layer::~Layer() {}
}