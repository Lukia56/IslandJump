#pragma once

#include "../Data.h"
#include "Param/Param.h"

inline void to_json(Data::Json::JsonObject& j, const SaveData& val)
{
	j = Data::Json::JsonObject{
		{ "easyHighscore", val.easyHighscore },
		{ "hardHighscore", val.hardHighscore }
	};
}

inline void to_json(Data::Json::JsonObject& j, const OptionsData& val)
{
	j = Data::Json::JsonObject{
		{ "mouseSensitivityX", val.mouseSensitivityX },
		{ "mouseSensitivityY", val.mouseSensitivityY }
	};
}
