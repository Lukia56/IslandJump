#pragma once

#include "../Core/Screen.h"

namespace UI
{
    class ResultScreen : public Screen
    {
    public:

        ResultScreen();
        ~ResultScreen() = default;

        void Init() override;

        void Update() override;
    };
}

