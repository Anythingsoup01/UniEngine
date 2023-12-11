#pragma once

#include <UniHeaders.h>

namespace UE {
	class SandboxApp{
	public:
	std::shared_ptr<VertexArray> vertexArray;
	std::shared_ptr<Shader> as_Shader;
	std::shared_ptr<Shader> as_BlueShader;
	std::shared_ptr<VertexArray> aa_SquareVA;
	};

}