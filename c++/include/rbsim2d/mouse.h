#pragma once
#include "position.h"

namespace rbsim {
	class IMouse
	{
	public:
		enum class ButtonType { undefined, left, right };
		enum class ButtonState { released, pressed };

		class ClickEvent {
		public:
			ClickEvent() :
				mousePosition(Position(0, 0)),
				mouseButtonType(IMouse::ButtonType::undefined),
				mouseButtonState(IMouse::ButtonState::released) {}
			ClickEvent(const ClickEvent &clickEvent) :
				mousePosition(clickEvent.mousePosition),
				mouseButtonType(clickEvent.mouseButtonType),
				mouseButtonState(clickEvent.mouseButtonState) {}
			~ClickEvent() {}

			ClickEvent &operator=(const ClickEvent &clickEvent) {
				mousePosition = clickEvent.mousePosition;
				mouseButtonType = clickEvent.mouseButtonType;
				mouseButtonState = clickEvent.mouseButtonState;
				return *this;
			}

			Position position() const { return mousePosition; }
			ButtonType buttonType() const { return mouseButtonType; }
			ButtonState buttonState() const { return mouseButtonState; }

		protected:
			Position mousePosition;
			ButtonType mouseButtonType;
			ButtonState mouseButtonState;
		};

		virtual Position position() const = 0;
		virtual ButtonState buttonState(ButtonType buttonType) const = 0;
		virtual int wheelPosition() const = 0;
		virtual void resetWheelPosition() = 0;
		virtual bool clickEventsPending() const = 0;
		virtual ClickEvent popClickEvent() = 0;
		virtual void flushClickEvents() = 0;
		virtual void waitEvent() = 0;
		virtual bool waitEvent(int time) = 0;
		virtual ClickEvent waitClickEvent(int time) = 0;
		virtual ClickEvent waitClickEvent(ButtonState buttonState = ButtonState::released, int time = 0) = 0;
	};


	class CMouse
	{
		friend class CPlayground;

	public:
		typedef IMouse::ButtonType ButtonType;
		typedef IMouse::ButtonState ButtonState;
		typedef IMouse::ClickEvent ClickEvent;
		
		CMouse(const CMouse &cMouse) : iMouse(cMouse.iMouse) {}
		~CMouse() {}

		CMouse &operator=(const CMouse &cMouse) {
			iMouse = cMouse.iMouse;
			return *this;
		}

		Position position() const { return iMouse->position(); }
		ButtonState buttonState(ButtonType buttonType) const { return iMouse->buttonState(buttonType); }
		int wheelPosition() const { return iMouse->wheelPosition(); }
		void resetWheelPosition() { iMouse->resetWheelPosition(); }
		bool clickEventsPending() const { return iMouse->clickEventsPending(); }
		ClickEvent popClickEvent() { return iMouse->popClickEvent(); }
		void flushClickEvents() { iMouse->flushClickEvents(); }
		void waitEvent() { iMouse->waitEvent(); }
		bool waitEvent(int time) { return iMouse->waitEvent(time); }
		ClickEvent waitClickEvent(int time) { return iMouse->waitClickEvent(time); }
		ClickEvent waitClickEvent(ButtonState buttonState = ButtonState::released, int time = 0) {
			return iMouse->waitClickEvent(buttonState, time);
		}

	protected:
		CMouse() : iMouse(nullptr) {}
		CMouse(IMouse *iMouse) : iMouse(iMouse) {}
		IMouse *iMouse;
	};
}
