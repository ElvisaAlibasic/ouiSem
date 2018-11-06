#pragma once
#include "body.h"
#include "robot.h"
#include "path.h"
#include "canvas.h"

namespace rbsim {
	class IPathfinder
	{
	public:
		static IPathfinder *create();
		static IPathfinder *clone(IPathfinder *iPathfinder);
		static void dispose(IPathfinder *pathfinder);
		virtual void clearObstacles() = 0;
		virtual void addObstacle(IBody *body) = 0;
		virtual void removeObstacle(IBody *body) = 0;
		virtual void setSpacing(double spacing) = 0;

		virtual IPath *find(
			const Position &startPosition,
			double startOrientation,
			const Position &goalPosition,
			double goalOrientation) = 0;

		virtual IPath *find(
			const Position &startPosition,
			double startOrientation,
			const Position &goalPosition) = 0;

		virtual IPath *find(
			IRobot *robot,
			const Position &goalPosition,
			double goalOrientation) = 0;

		virtual IPath *find(
			IRobot *robot,
			const Position &goalPosition) = 0;

		virtual void enableVisualization(
			ICanvas *canvas,
			ICanvas::Color lineColor = ICanvas::Color::white,
			ICanvas::Color dotColor = ICanvas::Color::red) = 0;
		virtual void disableVisualization() = 0;
	};


	class CPathfinder
	{
	public:
		CPathfinder() { iPathfinder = IPathfinder::create(); }
		CPathfinder(const CPathfinder &cPathfinder) { iPathfinder = IPathfinder::clone(cPathfinder.iPathfinder); }
		~CPathfinder() { IPathfinder::dispose(iPathfinder); }

		CPathfinder &operator=(const CPathfinder &cPathfinder) {
			IPathfinder::dispose(iPathfinder);
			iPathfinder = IPathfinder::clone(cPathfinder.iPathfinder);
			return *this;
		}

		void clearObstacles() { iPathfinder->clearObstacles(); }
		void addObstacle(CBody &body) { iPathfinder->addObstacle(body.iBody); }
		void removeObstacle(CBody &body) { iPathfinder->removeObstacle(body.iBody); }
		void setSpacing(double spacing) { iPathfinder->setSpacing(spacing); }

		CPath find(
			const Position &startPosition,
			double startOrientation,
			const Position &goalPosition,
			double goalOrientation)
		{
			return CPath(iPathfinder->find(startPosition, startOrientation, goalPosition, goalOrientation));
		}

		CPath find(
			const Position &startPosition,
			double startOrientation,
			const Position &goalPosition)
		{
			return CPath(iPathfinder->find(startPosition, startOrientation, goalPosition));
		}

		CPath find(
			CRobot &robot,
			const Position &goalPosition,
			double goalOrientation)
		{
			return CPath(iPathfinder->find(robot.iRobot, goalPosition, goalOrientation));
		}

		CPath find(
			CRobot robot,
			const Position &goalPosition)
		{
			return CPath(iPathfinder->find(robot.iRobot, goalPosition));
		}

		void enableVisualization(
			CCanvas &canvas,
			CCanvas::Color lineColor = CCanvas::Color::white,
			CCanvas::Color dotColor = CCanvas::Color::red)
		{
			iPathfinder->enableVisualization(canvas.iCanvas, lineColor, dotColor);
		}
		virtual void disableVisualization() { iPathfinder->disableVisualization(); }

	protected:
		IPathfinder *iPathfinder;
	};
}
