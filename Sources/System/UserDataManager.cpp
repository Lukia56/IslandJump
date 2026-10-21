#include "UserDataManager.h"
#include <filesystem>
#include "Utility/Data/JSON/JsonExporter.h"
#include "Utility/Data/JSON/JsonLoader.h"

namespace
{
	const char* const kFolderName = "UserData";

	const char* const kSaveDataPath = "UserData\\SaveData.json";
	const char* const kOptionsDataPath = "UserData\\OptionsData.json";
}

void UserDataManager::Initialize()
{
	if (std::filesystem::is_regular_file(kSaveDataPath))
	{
		mSaveData = Data::Json::LoadJsonAs<SaveData>(kSaveDataPath)[0];
		mTempSaveData = mSaveData;
	}

	if (std::filesystem::is_regular_file(kOptionsDataPath))
	{
		mOptionsData = Data::Json::LoadJsonAs<OptionsData>(kOptionsDataPath)[0];
		mTempOptionsData = mOptionsData;
	}
}

void UserDataManager::ApplyTempSaveData()
{
	mSaveData = mTempSaveData;
}

void UserDataManager::ApplyTempOptionsData()
{
	mOptionsData = mTempOptionsData;
}

void UserDataManager::ExportSaveData()
{
	if (!std::filesystem::is_regular_file(kSaveDataPath))
	{
		std::filesystem::create_directory("UserData");
	}

	Data::Json::ExportJsonAs(kSaveDataPath, mTempSaveData);
}

void UserDataManager::ExportOptionsData()
{
	if (!std::filesystem::is_regular_file(kOptionsDataPath))
	{
		std::filesystem::create_directory("UserData");
	}

	Data::Json::ExportJsonAs(kOptionsDataPath, mTempOptionsData);
}

UserDataManager& UserDataManager::GetInstance()
{
	static UserDataManager instance;

	return instance;
}

