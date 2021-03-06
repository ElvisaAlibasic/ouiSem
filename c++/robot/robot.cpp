#include <cstdlib>
#include <iostream>
#include <vector>
#include "rbsim2d/playground.h"
#include "rbsim2d/pathfinder.h"

using namespace std;
using namespace rbsim;

void positionAtBox(CPlayground &playground, CRobot &robot, CBody &box, int edge, double tau)
{
	/* Check input parameters. */
	if (edge < 0 || edge >= box.countEdges() || tau < 0 || tau > 1)
		return;

	/* Compute where the center of the robot should be. */
	Position pos = box.borderPoint(edge, tau);
	double angle = box.edgeDirection(edge);
	pos.move(angle - 180, robot.radius());

	/* Find a path. */
	CPathfinder pathfinder;
	pathfinder.addObstacle(box);
	pathfinder.setSpacing(1.1 * robot.radius());
	CPath path = pathfinder.find(robot, pos, angle);

	/* Draw the path. */
	CCanvas canvasPath = playground.getCanvas("path");
	path.draw(canvasPath);

	/* Follow the path. */
	CCanvas canvasFollow = playground.getCanvas("follow");
	robot.enableVisualization(canvasFollow);
	robot.follow(path, 10);

	/* Wait until task finished or user clicks the mouse. */
	while (robot.busy() && !playground.getMouse().clickEventsPending());

	/* Clear all drawings. */
	canvasPath.clear();
	canvasFollow.clear();
	robot.disableVisualization();
}

void pushBy(CRobot &robot, double distance)
{
	/* Move forward by the given distance. */
	CPathfinder pathfinder;
	Position pos = robot.position();
	pos.move(robot.headingAngle(), distance);
	CPath path = pathfinder.find(robot, pos);
	robot.follow(path);

	/* Wait until finished. Because of short duration we don't check the mouse. */
	robot.waitTask();
}

int main()
{
	/* Connect to simulator. */
	CPlayground playground;
	if (!playground.connect()) {
		cout << "Simulator not running!" << endl;
		return -1;
	}

	/* List all robots and check if our robot exists. */
	vector<string> robots = playground.listRobots();
	if (find(robots.begin(), robots.end(), "robot") == robots.end()) {
		cout << "Robot named 'robot' does not exist!" << endl;
		return -1;
	}

	/* Get the robot and the box. */
	CRobot robot = playground.getRobot("robot");
	CBody box = playground.getBody("box");

	/* Get mouse. */
	CMouse mouse = playground.getMouse();

	/* Push randomly until user clicks the mouse. */
	bool run = true;
	while (run) {
		/* Choose randomly where and how to push. */
		int edge = rand() % 4; // 0 .. 3
		double tau = (rand() % 100) / 100.0; // 0 .. 1.0
		double dist = (rand() % 500) / 100.0 ; // 0.0 .. 5.0
		cout << "edge = " << edge << ", tau = " << tau << ", distance = " << dist << endl;

		/* Move there. */
		positionAtBox(playground, robot, box, edge, tau);

		/* If mouse was not clicked during positioning, proceed with pushing. */
		if (!mouse.clickEventsPending())
			pushBy(robot, dist);

		/* If user clicked, stop. */
		if (mouse.clickEventsPending()) {
			mouse.flushClickEvents(); // Remove all click events from queue.
			run = false;
		}
	}

	/* Stop the robot. */
	robot.stop();

	/* Disconnect from simulator. */
	playground.disconnect();
	cout << "Goodbye!" << endl;

	return 0;
}
