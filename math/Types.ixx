module;

#include <array>
#include <cmath>

export module Math:Types;

using namespace std;

export namespace Math {

	struct mat4 {
	private:
		array<float, 16> m{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

	public:
		constexpr mat4() = default;

		constexpr const float* data() const noexcept { return m.data(); }
		constexpr		float* data()		noexcept { return m.data(); }


		constexpr mat4(initializer_list<float> values) {
			unsigned char i = 0;
			for (float v : values) {
				m[i++] = v;
			}
		}
		float& operator[](unsigned char i) {
			return m[i];
		}

	};

}