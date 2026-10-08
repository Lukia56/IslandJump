#pragma once

#include "../Core/Screen.h"

class ResultRecorder;

namespace UI
{
    class TextObject;

    class ResultScreen : public Screen
    {
    public:

        ResultScreen(ResultRecorder* resultRecorder);
        ~ResultScreen() = default;

        void Init() override;

        void Update() override;

        void Setup() override;

    private:

        TextObject* mResultText;

        TextObject* mProgressText;

        TextObject* mItemUseCountText;

        TextObject* mPlayTimeText;

        ResultRecorder* mResultRecorder;
    };
}

