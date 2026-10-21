#pragma once

#include "Param/Param.h"

/// <summary>
/// セーブデータと設定データを管理する
/// </summary>
class UserDataManager
{
private:

	UserDataManager() = default;
	UserDataManager(const UserDataManager&) = delete;
	UserDataManager& operator=(const UserDataManager&) = delete;
	UserDataManager(UserDataManager&&) = delete;
	UserDataManager& operator=(UserDataManager&&) = delete;

public:

	~UserDataManager() = default;

	void Initialize();

	void ApplyTempSaveData();

	void ApplyTempOptionsData();

	void ExportSaveData();

	void ExportOptionsData();

	static UserDataManager& GetInstance();

public:

	const SaveData& GetSaveData() const { return mSaveData; }

	const OptionsData& GetOptionsData() const { return mOptionsData; }

	/// <summary>
	/// 書き込みを行えるセーブデータを取得
	/// 値を書き換えてファイルを出力するために使用
	/// </summary>
	SaveData& GetTempSaveData() { return mTempSaveData; }
	/// <summary>
	/// 書き込みを行える設定データを取得
	/// 値を書き換えてファイルを出力するために使用
	/// </summary>
	OptionsData& GetTempOptionsData() { return mTempOptionsData; }

private:

	SaveData mSaveData;
	OptionsData mOptionsData;

	SaveData mTempSaveData;
	OptionsData mTempOptionsData;
};
