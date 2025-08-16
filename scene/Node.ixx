module;

#include <span>
#include <vector>
#include <array>

export module Scene;

import helios.math;

namespace math = helios::math;


export namespace Scene {


	class Node {
	private:
		std::vector<float> vertices;
		float rotX;
		float rotY;
		float rotZ;
                math::mat4 model = math::mat4(1.0f);

	public:

		Node(std::span<const float> vertices)
			: vertices(vertices.begin(), vertices.end())
		{
		}

		const float* getVertices() const {
			return this->vertices.data();
		}
		const size_t& getVerticesSize() const {
			return this->vertices.size() * sizeof(float);
		}

		const float& rotateX() {
			return this->rotX;
		}
		const float& rotateY() {
			return this->rotY;
		}
		const float& rotateZ() {
			return this->rotZ;
		}

		const Node* rotateX(const float& amount) {
			this->rotX = amount;
			model = math::rotateX(this->rotX) * model;
			return this;
		}

		const Node* rotateY(const float& amount) {
			this->rotY += amount;
			this->model = math::rotateY(amount) * model;
			return this;
		}
		
		const Node* rotateZ(const float& amount) {
			this->rotZ = amount;
			model = math::rotateZ(this->rotZ) * model;
			return this;
		}

		const math::mat4& getModelMatrix() const {
			return model;
		}
	};

}
