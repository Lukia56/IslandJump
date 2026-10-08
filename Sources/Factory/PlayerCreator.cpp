#include "PlayerCreator.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "World/Character/Player.h"
#include "World/Other/ItemObjectManager.h"

namespace
{
	const char* const kModelPath = "Resources\\Model\\Player.mv1";
	const char* const kAnimationParamPath = "Resources\\MasterData\\PlayerAnimationParam.csv";
}

PlayerCreator::PlayerCreator(ItemObjectManager* itemObjectManager) :
	mItemObjectManager(itemObjectManager)
{
}

std::unique_ptr<Player> PlayerCreator::CreateInstance()
{
	std::shared_ptr<Resource::ResourceBase> playerModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath);
	std::vector<AnimationParam> playerAnimParams = Data::Csv::LoadCsvAs<AnimationParam>(kAnimationParamPath);

	auto instance = std::make_unique<Player>(playerModel, playerAnimParams, mItemObjectManager);

	return instance;
}
