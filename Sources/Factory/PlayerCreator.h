#pragma once

#include "Creator.h"

class Player;
class ItemObjectManager;

/// <summary>
/// プレイヤーに必要なデータを読み込みインスタンスを生成する
/// </summary>
class PlayerCreator : public Creator<Player>
{
public:

	PlayerCreator(ItemObjectManager* itemObjectManager);
	~PlayerCreator() = default;

	std::unique_ptr<Player> CreateInstance() override;

private:

	ItemObjectManager* mItemObjectManager;
};
