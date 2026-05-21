#pragma once

#include"MeshTypes.h"

namespace TarsEngine::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateVertexCubePC(float size, const Color& color);
		static MeshPC CreateCubePC(float size);
	};
}
