#pragma once
#include <cmath>

#define PI 3.14159265358979323846

namespace rbsim {
	class Position
	{
	public:
		double x;
		double y;

		Position() : x(0), y(0) {}
		Position(double x, double y) : x(x), y(y) {}
		Position(const Position &position) : x(position.x), y(position.y) {}
		~Position() {}

		bool operator==(const Position &position) const {
			return x == position.x && y == position.y;
		}

		bool operator!=(const Position &position) const {
			return x != position.x || y != position.y;
		}

		Position &operator=(const Position &position) {
			x = position.x; y = position.y; return *this;
		}

		Position &operator=(const double value) {
			x = value; y = value; return *this;
		}

		Position operator+(const Position &position) {
			return Position(x + position.x, y + position.y);
		}

		Position &operator+=(const Position &position) {
			x += position.x;
			y += position.y;
			return *this;
		}

		Position operator-() {
			return Position(-x, -y);
		}

		Position operator-(const Position &position) {
			return Position(x - position.x, y - position.y);
		}

		Position &operator-=(const Position &position) {
			x -= position.x;
			y -= position.y;
			return *this;
		}

		Position operator*(double factor) {
			return Position(factor * x, factor * y);
		}

		Position &operator*=(double factor) {
			x *= factor;
			y *= factor;
			return *this;
		}

		Position operator/(double divisor) {
			return Position(x / divisor, y / divisor);
		}

		Position &operator/=(double divisor) {
			x /= divisor;
			y /= divisor;
			return *this;
		}

		void move(double angle, double distance) {
			x += std::cos(angle * PI / 180.0) * distance;
			y += std::sin(angle * PI / 180.0) * distance;
		}
	};
}
