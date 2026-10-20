#include "PlayerCreator.h"
#include "System/ResourceManager.h"
#include "System/Resource/Model.h"
#include "System/Resource/Texture.h"
#include "Utility/Data/CSV/CsvLoader.h"
#include "World/Character/Player.h"
#include "World/Other/ItemObjectManager.h"

namespace
{
	const char* const kModelPath = "Resources\\Model\\Player.mv1";
	const char* const kAnimationParamPath = "Resources\\MasterData\\PlayerAnimationParam.csv";

	const char* const kBlobShadowTexturePath = "Resources\\Sprite\\BlobShadow.png";
}

PlayerCreator::PlayerCreator(ItemObjectManager* itemObjectManager) :
	mItemObjectManager(itemObjectManager)
{
}

std::unique_ptr<Player> PlayerCreator::CreateInstance()
{
	std::shared_ptr<Resource::ResourceBase> playerModel = ResourceManager::GetInstance().GetResource<Resource::Model>(kModelPath);
	std::vector<AnimationParam> playerAnimParams = Data::Csv::LoadCsvAs<AnimationParam>(kAnimationParamPath);

	std::shared_ptr<Resource::ResourceBase> blobShadowTexture = ResourceManager::GetInstance().GetResource<Resource::Texture>(kBlobShadowTexturePath);

	auto instance = std::make_unique<Player>(playerModel, blobShadowTexture, playerAnimParams, mItemObjectManager);

	return instance;
}
