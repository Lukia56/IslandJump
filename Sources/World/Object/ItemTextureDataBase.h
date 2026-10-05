#pragma once

#include <string>
#include <unordered_map>
#include "ItemType.h"

/// <summary>
/// アイテムのテクスチャのファイルパスのデータベース
/// </summary>
class ItemTextureDataBase
{
public:

	ItemTextureDataBase();

	/// <summary>
	/// アイテムの種類からファイルパスを取得する
	/// 取得に失敗した場合は空の文字列を返す
	/// </summary>
	std::string GetFilePath(ItemType itemType);

private:

	std::unordered_map<ItemType, std::string> mData;
};
