#pragma once

#include "../Screen/MenuScreen.h"

class ResultRecorder;

namespace UI
{
    class TextObject;

    class ResultScreen : public MenuScreen
    {
    public:

        ResultScreen(ResultRecorder* resultRecorder);
        ~ResultScreen() = default;

        void Init() override;

        void Update() override;

        void Setup() override;

        bool ProcessInput(const Input::UIInputState& input);

    private:

        TextObject* mResultText;

        TextObject* mProgressText;

        TextObject* mItemUseCountText;

        TextObject* mPlayTimeText;

        TextObject* mExitText;

        ResultRecorder* mResultRecorder;
    };
}

