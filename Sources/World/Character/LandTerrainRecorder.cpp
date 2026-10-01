#include "LandTerrainRecorder.h"
#include "World/Component/Transform.h"

LandTerrainRecorder::LandTerrainRecorder() :
	mCurrentLandTerrain(nullptr),
	mPreLandTerrain(nullptr)
{
}

void LandTerrainRecorder::UpdateLandTerrain(Transform* currentTerrain)
{
	// 違う地形に移動していたら着地した地形を更新する
	if (mCurrentLandTerrain == currentTerrain) return;
	
	mPreLandTerrain = mCurrentLandTerrain;
	mCurrentLandTerrain = currentTerrain;
}
