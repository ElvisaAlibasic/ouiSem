#pragma once
#include <string>
#include "canvas.h"
#include "position.h"

namespace rbsim {
	class IBody
	{
	public:
		virtual std::string name() const = 0;
		virtual double radius() const = 0;
		virtual Position position() const = 0;
		virtual double orientation() const = 0;
		virtual double speed() const = 0;
		virtual double rotationalSpeed() const = 0;
		virtual bool occupies(Position position) const = 0;
		virtual int countEdges() const = 0;
		virtual double edgeLength(int edge) const = 0;
		virtual double edgeDirection(int edge) const = 0;
		virtual Position borderPoint(int edge, double tau) const = 0;
		virtual Position borderPoint(double direction) const = 0;
		virtual double distanceByCenter(Position position) const = 0;
		virtual double distanceByCenter(IBody *body) const = 0;
		virtual double distanceByBorder(Position position) const = 0;
		virtual double distanceByBorder(IBody *body) const = 0;
		virtual bool project(const Position position, double direction,
			Position &projection, int &edge, double &tau) const = 0;
		virtual void place(Position position, double orientation) = 0;
		virtual void waitEvent() = 0;
		virtual bool waitEvent(int time) = 0;
		virtual void drawBorder(
			ICanvas *canvas,
			ICanvas::Color lineColor = ICanvas::Color::white,
			ICanvas::Color dotColor = ICanvas::Color::red) const = 0;
	};


	class CBody
	{
		friend class CPlayground;
		friend class CRobot;
		friend class CPathfinder;

	public:
		CBody(const CBody &cBody) : iBody(cBody.iBody) {}
		~CBody() {}

		CBody &operator=(const CBody &cBody) {
			iBody = cBody.iBody;
			return *this;
		}

		std::string name() const { return iBody->name(); }
		double radius() const { return iBody->radius(); }
		Position position() const { return iBody->position(); }
		double orientation() const { return iBody->orientation(); }
		double speed() const { return iBody->speed(); }
		double rotationalSpeed() const { return iBody->rotationalSpeed(); }
		bool occupies(Position position) const { return iBody->occupies(position); }
		int countEdges() const { return iBody->countEdges(); }
		double edgeLength(int edge) const { return iBody->edgeLength(edge); }
		double edgeDirection(int edge) const { return iBody->edgeDirection(edge); }
		Position borderPoint(int edge, double tau) const { return iBody->borderPoint(edge, tau); }
		Position borderPoint(double direction) const { return iBody->borderPoint(direction); }
		double distanceByCenter(Position position) const { return iBody->distanceByCenter(position); }
		double distanceByCenter(CBody &body) const { return iBody->distanceByCenter(body.iBody); }
		double distanceByBorder(Position position) const { return iBody->distanceByBorder(position); }
		double distanceByBorder(CBody &body) const { return iBody->distanceByBorder(body.iBody); }
		bool project(const Position position, double direction, Position &projection, int &edge, double &tau) const
		{
			return iBody->project(position, direction, projection, edge, tau);
		}
		void place(Position position, double orientation) { iBody->place(position, orientation); }
		void waitEvent() { iBody->waitEvent(); }
		bool waitEvent(int time) { return iBody->waitEvent(time); }
		void drawBorder(
			CCanvas canvas,
			CCanvas::Color lineColor = CCanvas::Color::white,
			CCanvas::Color dotColor = CCanvas::Color::red) const
		{
			iBody->drawBorder(canvas.iCanvas, lineColor, dotColor);
		}

	protected:
		CBody() : iBody(nullptr) {}
		CBody(IBody *iBody) : iBody(iBody) {}
		IBody *iBody;
	};
}
