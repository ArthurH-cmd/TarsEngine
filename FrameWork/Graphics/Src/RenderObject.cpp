#include "Precompiled.h"
#include "RenderObject.h"

using namespace TarsEngine;
using namespace TarsEngine::Graphics;

void RenderObject::Terminate() 
{
	meshBuffer.Terminate();
	TextureManager* tm = TextureManager::Get();
	tm->ReleaseTexture(diffuseMapId);
	tm->ReleaseTexture(specMapId);
	tm->ReleaseTexture(normMapId);
	tm->ReleaseTexture(bumpMapId);
}