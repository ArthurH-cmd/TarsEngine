#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
            Colors::Red,
            Colors::Green,
            Colors::Blue,
            Colors::Yellow,
            Colors::Cyan,
            Colors::Magenta,
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
    }

    
}

MeshPC MeshBuilder::CreateVertexCubePC(float size, const Color& color)
{
    MeshPC mesh;
    const float hs = size * 0.5f;

    mesh.vertices.push_back({ {-hs, -hs, -hs }, { color } });
    mesh.vertices.push_back({ { hs,  hs, -hs }, { color } });
    mesh.vertices.push_back({ { hs, -hs, -hs }, { color } });

    mesh.vertices.push_back({ {-hs, -hs, -hs }, { color } });
    mesh.vertices.push_back({ {-hs,  hs, -hs }, { color } });
    mesh.vertices.push_back({ { hs,  hs, -hs }, { color } });

    return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
    MeshPC mesh;
    const float hs = size * 0.5f;
	int index = rand() % 69;

    mesh.vertices.push_back({ {-hs, -hs, -hs },GetNextColor(index)});
    mesh.vertices.push_back({ {-hs,  hs, -hs },GetNextColor(index)});
    mesh.vertices.push_back({ { hs,  hs, -hs },GetNextColor(index)});
    mesh.vertices.push_back({ { hs, -hs, -hs },GetNextColor(index) });

    mesh.vertices.push_back({ {-hs, -hs,  hs },GetNextColor(index)});
    mesh.vertices.push_back({ {-hs,  hs,  hs },GetNextColor(index)});
    mesh.vertices.push_back({ { hs,  hs,  hs },GetNextColor(index)});
    mesh.vertices.push_back({ { hs, -hs,  hs },GetNextColor(index) });

    mesh.indices = {
        // front
        0,1, 2,
        0,2, 3,
        // back
        7,5,4,
        7,6,5,
        // right
        3,2,6,
        3,6,7,
        // left
        4,5,1,
        4,1,0,
        // top
        1,5,6,
        1,6,2,
        // bottom
        0,3,7,
        0,7,4,
    };
    return mesh;
}