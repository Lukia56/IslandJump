#include "BoxObject.h"
#include <DxLib.h>

namespace UI
{
	BoxObject::BoxObject(const Color& color) :
		mColor(color)
	{
	}

	void BoxObject::Init()
	{
	}

	void BoxObject::Update()
	{
	}

	void BoxObject::Draw()
	{
		Rect rect = mRectTransform->CalculateRect();

		DrawBox(rect.xMin, rect.yMin, rect.xMin + rect.width, rect.yMin + rect.height, mColor.GetAsHexRGB(), true);
	}
}
