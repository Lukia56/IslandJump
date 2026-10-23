#pragma once

#include "../Core/UIObject.h"
#include <functional>

namespace UI
{
	/// <summary>
	/// メニューの一項目
	/// </summary>
	class MenuItem : public UIObject
	{
	public:

		MenuItem();
		~MenuItem() = default;

		void Init() override {};
		void Update() override {};

		/// <summary>
		/// カーソルが自分の場所に来た時のコールバックを呼び出す
		/// </summary>
		void InvokeSelect();

		/// <summary>
		/// カーソルが自分の場所から外れた時のコールバックを呼び出す
		/// </summary>
		void InvokeDeselect();

		/// <summary>
		/// 決定時のコールバックを呼び出す
		/// </summary>
		/// <returns>画面を閉じるならfalseを返す</returns>
		bool InvokeSubmit();

		/// <summary>
		/// キャンセル時のコールバックを呼び出す
		/// </summary>
		/// <returns>画面を閉じるならfalseを返す</returns>
		bool InvokeCancel();

		void InvokePressUp();
		void InvokePressDown();
		void InvokePressLeft();
		void InvokePressRight();

	public:

		void SetSelectCallback(const std::function<void(void)>& onSelect) { mOnSelect = onSelect; }
		void SetDeselectCallback(const std::function<void(void)>& onDeselect) { mOnDeselect = onDeselect; }
		void SetSubmitCallback(const std::function<bool(void)>& onSubmit) { mOnSubmit = onSubmit; }
		void SetCancelCallback(const std::function<bool(void)>& onCancel) { mOnCancel = onCancel; }

		void SetPressUpCallback(const std::function<void(void)>& onPressUp) { mOnPressUp = onPressUp; }
		void SetPressDownCallback(const std::function<void(void)>& onPressDown) { mOnPressDown = onPressDown; }
		void SetPressLeftCallback(const std::function<void(void)>& onPressLeft) { mOnPressLeft = onPressLeft; }
		void SetPressRightCallback(const std::function<void(void)>& onPressRight) { mOnPressRight = onPressRight; }

	private:

		std::function<void(void)> mOnSelect;

		std::function<void(void)> mOnDeselect;

		std::function<bool(void)> mOnSubmit;

		std::function<bool(void)> mOnCancel;

		std::function<void(void)> mOnPressUp;
		std::function<void(void)> mOnPressDown;
		std::function<void(void)> mOnPressLeft;
		std::function<void(void)> mOnPressRight;
	};
}
