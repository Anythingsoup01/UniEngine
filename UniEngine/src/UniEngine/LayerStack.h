#pragma once

#include "UniEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace UE {

	class UE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return l_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return l_Layers.end(); }
	private:
		std::vector<Layer*> l_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}