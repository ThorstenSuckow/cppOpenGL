module;

#include <cmath>
#include <iostream>

export module Math:Transforms;

import :Types;

using namespace std;


export namespace Math {


	mat4 rotateZ(float degree) {
		return mat4 {
			cos(degree), sin(degree), 0, 0,
				-sin(degree), cos(degree), 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
		};
	}

	mat4 rotateY(float degree) {

		return mat4{
			cos(degree), 0, -sin(degree), 0,
				0, 1, 0, 0,
				sin(degree), 0, cos(degree), 0,
				0, 0, 0, 1
		};
	}


}
