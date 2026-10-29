#include "ItemTextureDataBase.h"
#include <cassert>
#include "Utility/Data/CSV/CsvLoader.h"

namespace
{
	const char* const kDataPath = "Resources\\MasterData\\Item\\ItemTextureData.csv";
}

ItemTextureDataBase::ItemTextureDataBase()
{
	auto dataList = Data::Csv::LoadCsvAs<ItemTextureData>(kDataPath);

	for (const auto& data : dataList)
	{
		mData.try_emplace(data.itemType, data.filePath);
	}
}

std::string ItemTextureDataBase::GetFilePath(ItemType itemType)
{
	if (!mData.contains(itemType))
	{
		assert(false && "ItemTextureDataBase // 指定されたアイテムIDが存在しないため、ファイルパスを取得できませんでした");
		return "";
	}

	return mData.at(itemType);
}
