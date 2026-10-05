#pragma once

#include <memory>
#include <vector>
#include "Utility/Vector.h"

class GameObject;

namespace Stage
{
	class StageGenerator
	{
	public:

		static std::vector<std::unique_ptr<GameObject>> Generate(Vector3& goalPos);
	};
}
