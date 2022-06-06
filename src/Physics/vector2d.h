#ifndef vector2d_H
#define vector2d_H
#include <iostream>

class vector2d {
	public:
		float X, Y;
	public:
		vector2d(float x = 0, float y = 0) : X(x), Y(y) {}

	public:
		inline vector2d operator + (const vector2d &other) const {
			return vector2d (X + other.X, Y + other.Y);
		}

		inline vector2d operator - (const vector2d &other) const {
			return vector2d (X - other.X, Y - other.Y);
		}

		inline vector2d operator * (const float scalar) const {
			return vector2d (X * scalar, Y * scalar);
		}

		void Log(std::string mess = "") {
			std::cout << mess << "(x, y) : (" << X << ", " << Y << ")" << '\n';
		}

};

#endif // vector2d_H
