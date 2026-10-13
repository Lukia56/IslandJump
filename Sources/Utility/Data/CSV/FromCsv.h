#pragma once

#include "../Data.h"
#include "CsvConvert.h"
#include "Param/Param.h"

namespace Data
{
	namespace Csv
	{
		template <typename T>
		struct FromCsv
		{
			static T Binding(const Row& row)
			{
				static_assert(sizeof(T) == 0, "Data::Csv::FromCsv // Cannot binding an undefined type");

				return T{};
			}
		};

		/// <summary>
		/// 安全な値の取得処理
		/// </summary>
		template <typename T>
		T Get(const Row& row, const std::string& key)
		{
			try
			{
				T value = Convert<T>(row.at(key));

				return value;
			}
			catch (std::out_of_range)
			{
				assert(false && "Data::Csv::Get // 存在しないパラメータ名のため値の取得に失敗しました");

				return T{};
			}
		}

		template <>
		struct FromCsv<WindowConfigs>
		{
			static WindowConfigs Binding(const Row& row)
			{
				WindowConfigs param;
				param.windowText = Get<std::string>(row, "windowText");
				param.width = Get<int>(row, "width");
				param.height = Get<int>(row, "height");
				param.colorBit = Get<int>(row, "colorBit");
				return param;
			}
		};

		template <>
		struct FromCsv<AABBColliderParam>
		{
			static AABBColliderParam Binding(const Row& row)
			{
				AABBColliderParam param;
				param.size.x = Get<float>(row, "sizeX");
				param.size.y = Get<float>(row, "sizeY");
				param.size.z = Get<float>(row, "sizeZ");
				param.offsetPos.x = Get<float>(row, "offsetX");
				param.offsetPos.y = Get<float>(row, "offsetY");
				param.offsetPos.z = Get<float>(row, "offsetZ");
				param.collisionTag = Get<Collision::Tag>(row, "collisionTag");
				return param;
			}
		};

		template <>
		struct FromCsv<AnimationParam>
		{
			static AnimationParam Binding(const Row& row)
			{
				AnimationParam param;
				param.animIndex = Get<int>(row, "animIndex");
				param.isLoop = Get<bool>(row, "isLoop");
				param.isForcePlay = Get<bool>(row, "isForcePlay");
				return param;
			}
		};

		template <>
		struct FromCsv<StageModelData>
		{
			static StageModelData Binding(const Row& row)
			{
				StageModelData param;
				param.objectName = Get<std::string>(row, "objectName");
				param.filePath = Get<std::string>(row, "filePath");
				return param;
			}
		};

		template <>
		struct FromCsv<ItemTextureData>
		{
			static ItemTextureData Binding(const Row& row)
			{
				ItemTextureData param;
				param.itemType = Get<ItemType>(row, "itemID");
				param.filePath = Get<std::string>(row, "filePath");
				return param;
			}
		};

		template <>
		struct FromCsv<ItemEffectParam>
		{
			static ItemEffectParam Binding(const Row& row)
			{
				ItemEffectParam param;
				param.itemType = Get<ItemType>(row, "itemID");

				param.param.emplace_back(Get<float>(row, "param0"));
				param.param.emplace_back(Get<float>(row, "param1"));
				return param;
			}
		};

		template <>
		struct FromCsv<StageDifficultyData>
		{
			static StageDifficultyData Binding(const Row& row)
			{
				StageDifficultyData param;
				param.cloudSpeed = Get<float>(row, "cloudSpeed");
				param.itemNum = Get<int>(row, "itemNum");
				param.goalPosY = Get<float>(row, "goalPosY");
				return param;
			}
		};

		template <>
		struct FromCsv<SoundData>
		{
			static SoundData Binding(const Row& row)
			{
				SoundData param;
				param.id = Get<int>(row, "ID");
				param.filePath = Get<std::string>(row, "filePath");
				return param;
			}
		};
	}
}
