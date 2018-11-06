#pragma once
#include <string>
#include "position.h"

namespace rbsim {
	class ICanvas
	{
	public:
		enum class Color { none, white, black, red, green, blue, cyan, yellow, magenta };

		virtual void clear() const = 0;
		virtual void drawDot(const Position &p, Color color = Color::white) const = 0;
		virtual void drawLine(const Position &p1, const Position &p2, Color color = Color::white) const = 0;
		virtual void drawCircle(const Position &center, double radius, Color color = Color::white) const = 0;
		virtual void drawArc(const Position &center, double radius, double alpha, double beta, Color color = Color::white) const = 0;
	};


	class CCanvas
	{
		friend class CPlayground;
		friend class CBody;
		friend class CRobot;
		friend class CPath;
		friend class CPathfinder;

	public:
		typedef ICanvas::Color Color;

		CCanvas(const CCanvas &cCanvas) : iCanvas(cCanvas.iCanvas) {}
		~CCanvas() {}

		CCanvas &operator=(const CCanvas &cCanvas) {
			iCanvas = cCanvas.iCanvas;
			return *this;
		}

		void clear() const { iCanvas->clear(); }
		void drawDot(const Position &p, Color color = Color::white) const {
			iCanvas->drawDot(p, color);
		}
		void drawLine(const Position &p1, const Position &p2, Color color = Color::white) const {
			iCanvas->drawLine(p1, p2, color);
		}
		void drawCircle(const Position &center, double radius, Color color = Color::white) const {
			iCanvas->drawCircle(center, radius, color);
		}
		void drawArc(const Position &center, double radius, double alpha, double beta, Color color = Color::white) const {
			iCanvas->drawArc(center, radius, alpha, beta, color);
		}

	protected:
		CCanvas() : iCanvas(nullptr) {}
		CCanvas(ICanvas *iCanvas) : iCanvas(iCanvas) {}
		ICanvas *iCanvas;
	};
}
