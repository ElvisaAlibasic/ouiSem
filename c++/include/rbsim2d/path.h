#pragma once
#include "canvas.h"
#include "position.h"

namespace rbsim {
	class IPath
	{
	public:
		static IPath *create();
		static IPath *clone(IPath *iPath);
		static void dispose(IPath *iPath);
		virtual void clear() = 0;
		virtual void appendStart(const Position &position) = 0;
		virtual void appendGoal(const Position &position) = 0;
		virtual void appendStartSmooth(const Position &position) = 0;
		virtual void appendGoalSmooth(const Position &position) = 0;
		virtual bool empty() const = 0;
		virtual double length() const = 0;
		virtual Position startPosition() const = 0;
		virtual Position goalPosition() const = 0;
		virtual Position position(double distance) const = 0;
		virtual Position position(double distance, const Position &reference) const = 0;
		virtual double travelDistance(const Position &position) const = 0;
		virtual void draw(
			ICanvas *canvas,
			ICanvas::Color lineColor = ICanvas::Color::yellow,
			ICanvas::Color dotColor = ICanvas::Color::red) const = 0;
	};


	class CPath
	{
		friend class CRobot;
		friend class CPathfinder;

	public:
		CPath() { iPath = IPath::create(); }
		CPath(const CPath &cPath) { iPath = IPath::clone(cPath.iPath); }
		~CPath() { IPath::dispose(iPath); }
		
		CPath &operator=(const CPath &cPath) {
			IPath::dispose(iPath);
			iPath = IPath::clone(cPath.iPath);
			return *this;
		}

		void clear() { iPath->clear(); }
		void appendStart(const Position &position) { iPath->appendStart(position); }
		void appendGoal(const Position &position) { iPath->appendGoal(position); }
		void appendStartSmooth(const Position &position) { iPath->appendStartSmooth(position); }
		void appendGoalSmooth(const Position &position) { iPath->appendGoalSmooth(position); }
		bool empty() const { return iPath->empty(); }
		double length() const { return iPath->length(); }
		Position startPosition() const { return iPath->startPosition(); }
		Position goalPosition() const { return iPath->goalPosition(); }
		Position position(double distance) const { return iPath->position(distance); }
		Position position(double distance, const Position &reference) const { return iPath->position(distance, reference);  }
		void draw(
			CCanvas &canvas,
			CCanvas::Color lineColor = CCanvas::Color::yellow,
			CCanvas::Color dotColor = CCanvas::Color::red) const
		{
			iPath->draw(canvas.iCanvas, lineColor, dotColor);
		}

	protected:
		CPath(IPath *iPath) : iPath(iPath) {}
		IPath *iPath;
	};
}