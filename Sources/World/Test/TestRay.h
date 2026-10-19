#pragma once

#include "../GameObject.h"

class TestRay : public GameObject
{
public:

	TestRay();
	~TestRay() = default;

	void Init() override;

	void Update() override;

	void DebugDraw() override;
};
