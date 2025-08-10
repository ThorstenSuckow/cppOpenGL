module;

#include <span>
#include <vector>
#include <array>

export module Scene;

import Math;

export namespace Scene {


	class Node {
	private:
		std::vector<float> vertices;
		float rotX;
		float rotY;
		float rotZ;

	public:

		Node(std::span<const float> vertices)
			: vertices(vertices.begin(), vertices.end())
		{
		}

		const float* getVertices() const {
			return this->vertices.data();
		}
		const int getVerticesSize() const {
			return this->vertices.size() * sizeof(float);
		}

		Node* setRotateX(const float& amount) {
			this->rotX = amount;
			return this;
		}
		Node* setRotateY(const float& amount) {
			this->rotY = amount;
			return this;
		}
		
		const float getRotateY() const {
			return this->rotY;
		}

		Node* setRotateZ(const float& amount) {
			this->rotZ = amount;
			return this;
		}

		const Math::mat4 getModelMatrix() const {
			return Math::rotateY(this->rotY);
		}
	};

}
