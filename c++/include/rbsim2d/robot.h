#pragma once
#include "body.h"
#include "path.h"

namespace rbsim {
	class IRobot : public IBody
	{
	public:
		class PIDProfile
		{
		public:
			PIDProfile(double kp, double ki, double kd) : kp(kp), ki(ki), kd(kd) {}
			~PIDProfile() {}
			double kp, ki, kd;
		};

		virtual Position frontPoint() const = 0;
		virtual double headingAngle() const = 0;
		virtual double angleTo(Position position) const = 0;
		virtual double angleTo(IBody *body) const = 0;
		virtual double steeringRadius() const = 0;
		virtual Position steeringGrip() const = 0;
		virtual void setWheels(double left, double right) = 0;
		virtual void moveTo(Position position, double tolerance, PIDProfile &pidProfile) = 0;
		virtual void rotateTo(double angle, double tolerance, PIDProfile &pidProfile) = 0;
        virtual void rotateBy(double angle, double tolerance, PIDProfile &pidProfile) = 0;
		virtual void follow(IPath *path, double trackWidth = 1) = 0;
		virtual double findTrackWidth() = 0;
		virtual bool busy() = 0;
		virtual void stop() = 0;
		virtual void waitTask() = 0;
		virtual bool waitTask(int time) = 0;
		virtual void enableVisualization(
			ICanvas *canvas,
			ICanvas::Color lineColor = ICanvas::Color::white,
			ICanvas::Color dotColor = ICanvas::Color::red) = 0;
		virtual void disableVisualization() = 0;
	};


	class CRobot : public CBody
	{
		friend class CPlayground;
		friend class CPathfinder;

	public:
		typedef IRobot::PIDProfile PIDProfile;

		CRobot(const CRobot &cRobot) : iRobot(cRobot.iRobot) {}
		~CRobot() {}

		CRobot &operator=(const CRobot &cRobot) {
			iRobot = cRobot.iRobot;
			return *this;
		}

		Position frontPoint() const { return iRobot->frontPoint(); }
		double headingAngle() const { return iRobot->headingAngle(); }
		double angleTo(Position position) const { return iRobot->angleTo(position); }
		double angleTo(const CBody &body) const { return iRobot->angleTo(body.iBody); }
		double steeringRadius() const { return iRobot->steeringRadius(); }
		Position steeringGrip() const { return iRobot->steeringGrip(); }
		void setWheels(double left, double right) { iRobot->setWheels(left, right); }
		void moveTo(Position position, double tolerance, PIDProfile &pidProfile) {
			iRobot->moveTo(position, tolerance, pidProfile);
		}
		void rotateTo(double angle, double tolerance, PIDProfile &pidProfile) {
			iRobot->rotateTo(angle, tolerance, pidProfile);
		}
        void rotateBy(double angle, double tolerance, PIDProfile &pidProfile) {
			iRobot->rotateBy(angle, tolerance, pidProfile);
		}
		void follow(const CPath &path, double trackWidth = 1) {
			iRobot->follow(path.iPath, trackWidth);
		}
		double findTrackWidth() { return iRobot->findTrackWidth(); }
		bool busy() { return iRobot->busy(); }
		void stop() { iRobot->stop(); }
		void waitTask() { iRobot->waitTask(); }
		bool waitTask(int time) { return iRobot->waitTask(time); }
		void enableVisualization(
			CCanvas canvas,
			CCanvas::Color lineColor = CCanvas::Color::white,
			CCanvas::Color dotColor = CCanvas::Color::red)
		{
			iRobot->enableVisualization(canvas.iCanvas, lineColor, dotColor);
		}
		void disableVisualization() { iRobot->disableVisualization(); }

	protected:
		IRobot *iRobot;
		CRobot() : CBody(), iRobot(nullptr) {}
		CRobot(IRobot *iRobot) : CBody(iRobot), iRobot(iRobot) {}
	};
}
