#include "SceneInit.h"
#include "SceneTitle.h"
#include "Test/SceneSelectDebug.h"

void SceneInit::OnInit()
{
}

std::unique_ptr<SceneBase> SceneInit::OnUpdate()
{
#ifdef _DEBUG
	return std::make_unique<SceneSelectDebug>();
#else
	return std::make_unique<SceneTitle>();
#endif
}
