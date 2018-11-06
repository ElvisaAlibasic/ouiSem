#pragma once
#include <string>
#include <vector>
#include "body.h"
#include "robot.h"
#include "canvas.h"
#include "mouse.h"

namespace rbsim {
	class IPlayground
	{
		friend class CPlayground;

	public:
		static double getProtocolVersion();
		static IPlayground *create();
		static IPlayground *create(const std::string &host);
		static IPlayground *create(const std::string &host, const std::string &port);
		static void dispose(IPlayground *iPlayground);
		virtual bool connect() = 0;
		virtual void disconnect() = 0;
		virtual bool connected() const = 0;
		virtual std::string getError() const = 0;
		virtual void stopAllActivities() = 0;
		virtual void waitEvent() = 0;
		virtual bool waitEvent(int time) = 0;
		virtual void waitAllTasks() = 0;
		virtual bool waitAllTasks(int time) = 0;
		virtual bool bodyExists(const std::string &name) const = 0;
		virtual bool robotExists(const std::string &name) const = 0;
		virtual std::vector<std::string> listBodies() const = 0;
		virtual std::vector<std::string> listRobots() const = 0;
		virtual std::vector<std::string> listItems() const = 0;
		virtual IBody *getBody(const std::string &name) const = 0;
		virtual IRobot *getRobot(const std::string &name) const = 0;
		virtual ICanvas *getCanvas(const std::string &name) = 0;
		virtual IMouse *getMouse() const = 0;

	protected:
		int ref_count;
	};


	class CPlayground
	{
	public:
		static double getProtocolVersion() { return IPlayground::getProtocolVersion(); }
		
		CPlayground() { iPlayground = IPlayground::create(); }
		CPlayground(const CPlayground &cPlayground) : iPlayground(cPlayground.iPlayground) {
			iPlayground->ref_count++;
		}
		~CPlayground() {
			if (--iPlayground->ref_count == 0)
				IPlayground::dispose(iPlayground);
		}

		CPlayground &operator=(const CPlayground &cPlayground) {
			if (--iPlayground->ref_count == 0)
				IPlayground::dispose(iPlayground);
			iPlayground = cPlayground.iPlayground;
			iPlayground->ref_count++;
			return *this;
		}

		bool connect() { return iPlayground->connect(); }
		void disconnect() { iPlayground->disconnect(); }
		bool connected() const { return iPlayground->connected(); }
		std::string getError() const { return iPlayground->getError(); }
		void stopAllActivities() { iPlayground->stopAllActivities(); }
		void waitEvent() { iPlayground->waitEvent(); }
		bool waitEvent(int time) { return iPlayground->waitEvent(time); }
		void waitAllTasks() { iPlayground->waitAllTasks(); }
		bool waitAllTasks(int time) { return iPlayground->waitAllTasks(time); }
		std::vector<std::string> listBodies() const { return iPlayground->listBodies(); }
		std::vector<std::string> listRobots() const { return iPlayground->listRobots(); }
		std::vector<std::string> listItems() const { return iPlayground->listItems(); }
		CBody getBody(const std::string &name) const { return CBody(iPlayground->getBody(name)); }
		CRobot getRobot(const std::string &name) const { return CRobot(iPlayground->getRobot(name)); }
		CCanvas getCanvas(const std::string &name) { return CCanvas(iPlayground->getCanvas(name)); }
		CMouse getMouse() const { return CMouse(iPlayground->getMouse()); }

	protected:
		CPlayground(IPlayground *iPlayground) : iPlayground(iPlayground) {
			iPlayground->ref_count++;
		}
		IPlayground *iPlayground;
	};
}
