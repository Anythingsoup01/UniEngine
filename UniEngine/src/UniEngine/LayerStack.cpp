#include "uepch.h"
#include "LayerStack.h"

namespace UE {

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : l_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		l_Layers.emplace(l_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		l_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(l_Layers.begin(), l_Layers.end(), layer);
		if (it != l_Layers.end())
		{
			l_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(l_Layers.begin(), l_Layers.end(), overlay);
		if (it != l_Layers.end())
			l_Layers.erase(it);
	}

}