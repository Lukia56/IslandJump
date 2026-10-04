#pragma once

#include <string>
#include <memory>
#include <vector>

class GameObject;

namespace Stage
{
	class StageGenerator
	{
	public:

		static std::vector<std::unique_ptr<GameObject>> Generate();
	};
}
