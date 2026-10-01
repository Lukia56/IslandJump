#pragma once

class Transform;

/// <summary>
/// プレイヤーが着地した地形を記録する
/// </summary>
class LandTerrainRecorder
{
public:

	LandTerrainRecorder();
	~LandTerrainRecorder() = default;

	void UpdateLandTerrain(Transform* currentTerrain);

public:

	Transform* GetCurrentTerrain() const { return mCurrentLandTerrain; }

	Transform* GetPreLandTerrain() const { return mPreLandTerrain; }

private:

	Transform* mCurrentLandTerrain;

	Transform* mPreLandTerrain;
};
