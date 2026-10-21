#pragma once

#include "CameraProperty.h"

class ICamera
{
public:

	ICamera() = default;
	virtual ~ICamera() = default;

	virtual void Setup() {};

	virtual void Update(Camera::View& view) = 0;

	virtual void DebugDraw() {}
};
