import rbsim2d
import random
import math

def position_at_box(playground, robot, box, edge, tau):
    # Check input parameters.
    if edge < 0 or edge >= box.count_edges() or tau < 0 or tau > 1:
        return

    # Compute where the center of the robot should be.
    (x, y) = box.border_point(edge, tau)
    angle = box.edge_direction(edge)
    x += math.cos((angle - 180.0) * math.pi / 180.0) * robot.radius()
    y += math.sin((angle - 180.0) * math.pi / 180.0) * robot.radius()

    # Find a path.
    pathfinder = rbsim2d.Pathfinder()
    pathfinder.add_obstacle(box)
    pathfinder.set_spacing(1.1 * robot.radius())
    path = pathfinder.find(robot, (x, y), angle);

    # Draw the path.
    canvas_path = playground.get_canvas("path");
    path.draw(canvas_path);

    # Follow the path.
    canvas_follow = playground.get_canvas("follow");
    robot.enable_visualization(canvas_follow);
    robot.follow(path, 10);

    # Wait until task finished or user clicks the mouse.
    while (robot.busy() and not playground.get_mouse().click_events_pending()):
        pass

    # Clear all drawings.
    canvas_path.clear();
    canvas_follow.clear();
    robot.disable_visualization();


def push_by(robot, distance):
    # Move forward by the given distance.
    pathfinder = rbsim2d.Pathfinder()
    (x, y) = robot.position();
    x += math.cos(robot.heading_angle() * math.pi / 180.0) * distance
    y += math.sin(robot.heading_angle() * math.pi / 180.0) * distance
    path = pathfinder.find(robot, (x, y));
    robot.follow(path);

    # Wait until finished. Because of short duration we don't check the mouse.
    robot.wait_task();
    

def main():
    # Connect to simulator.
    playground = rbsim2d.Playground()
    if not playground.connect():
        print(playground.get_error())
        exit()

    # Get the robot and other objects.
    robot = playground.get_robot("robot")
    box = playground.get_body("box")
    goal = playground.get_body("goal")

    # Get the mouse.
    mouse = playground.get_mouse()

    # Push randomly until user clicks the mouse.
    run = True
    while run:
        # Choose randomly where and how to push.
        edge = random.randint(0, 3)
        tau = random.uniform(0, 1)
        dist = random.uniform(0, 5)
        print("edge =", edge, "tau =", tau, "distance =", dist)

        # Move there.
        position_at_box(playground, robot, box, edge, tau)

        # If mouse was not clicked during positioning, proceed with pushing.
        if not mouse.click_events_pending():
            push_by(robot, dist);

        # If user clicked, stop.
        if mouse.click_events_pending():
            mouse.flush_click_events(); # Remove all click events from queue.
            run = False;

    # Stop the robot.
    robot.stop();

    # Disconnect from simulator
    playground.disconnect()
    print("Goodbye!")

if __name__ == "__main__":
    main()
