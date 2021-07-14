
#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<cmath>
#include <iostream>

using namespace std;
namespace roml {
	glm::mat4 translate(glm::mat4 matrix, glm::vec3 camera);
	glm::mat4 scale(glm::mat4 mat, glm::vec3 scalar);
	glm::mat4 createPerspective(float FOV, float screenAspect, float nearClip, float farClip);
	glm::mat4 rotate(glm::mat4 oldMat, float rotation, glm::vec3 normal);
	glm::mat4 rotate(glm::mat4 oldMat, float rotation, char axis);
	glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 normal);
	float inversesqrt(float x);
	glm::vec3 negateV3(glm::vec3 vec);
	glm::vec3 normalize(glm::vec3 vector);
	float angle(glm::vec3 VecA, glm::vec3 VecB);
	float dot(glm::vec3 vecA, glm::vec3 vecB);
	glm::vec3 cross(glm::vec3 a, glm::vec3 b);
	glm::mat4 lookAt(glm::vec3 eye, glm::vec3 look, glm::vec3 up);
	float radians(float deg);

#ifdef ROML_IMPLEMENTATION
	//Translating the mat4
	glm::mat4 translate(glm::mat4 oldMat, glm::vec3 translateV) {

		// Creates and initizializes result matrix
		glm::mat4 result = glm::mat4(1.0f);
		// Replaces 4th row with out multiplication results
		result[3] = oldMat[0] * translateV[0] + oldMat[1] * translateV[1] + oldMat[2] * translateV[2] + oldMat[3];

		return result;
	}

	glm::mat4 scale(glm::mat4 mat, glm::vec3 scalar) {
		glm::mat4 result = glm::mat4(1.0f);

		result[0][0] = scalar.x * mat[0][0];
		result[1][1] = scalar.y * mat[1][1];
		result[2][2] = scalar.z * mat[2][2];
		return result;

	}
	//Create Perspective Matrix
	glm::mat4 createPerspective(float FOV, float screenAspect, float nearClip, float farClip) {
		//Making it a zero matrix
		glm::mat4 perspectiveM = glm::mat4(0.0f);
		//Making variables needed to complete the perspective matrix
		float top = nearClip * tan(FOV / 2);
		float bottom = -top;
		float right = top * screenAspect;
		float left = -right;

		//Making the proj matrix
		perspectiveM[0][0] = (2 * nearClip) / (right - left);
		perspectiveM[0][2] = (right + left) / (right - left);
		perspectiveM[1][1] = (2 * nearClip) / (top - bottom);
		perspectiveM[1][2] = (top + bottom) / (top - bottom);
		perspectiveM[2][2] = -(farClip + nearClip) / (farClip - nearClip);
		perspectiveM[2][3] = -1;
		perspectiveM[3][2] = -(2 * farClip * nearClip) / (farClip - nearClip);
		//Took me 3 hours to find out that GLM swaps the Z axis because OpenGL renders right hand side

		return perspectiveM;
	}


	//Rotates matrices
	glm::mat4 rotate(glm::mat4 oldMat, float rotation, char axis) {

		//GLM does it right handed, so i'm doing right-handed rotation matrices
		glm::mat4 result = glm::mat4(1.0f);
		glm::mat4 rotMat = glm::mat4(1.0f);
		if (axis == 'X') {
			//X Axis Rotational Matrix
			rotMat[1][1] = cos(rotation);
			rotMat[1][2] = sin(rotation);
			rotMat[2][1] = -sin(rotation);
			rotMat[2][2] = cos(rotation);

			return oldMat * rotMat;
		}

		else if (axis == 'Y') {
			//Y Axis Rotational Matrix
			rotMat[0][0] = cos(rotation);
			rotMat[0][2] = -sin(rotation);
			rotMat[2][0] = sin(rotation);
			rotMat[2][2] = cos(rotation);

			return oldMat * rotMat;
		}

		if (axis == 'Z') {
			//Z Axis Rotational Matrix
			rotMat[0][0] = cos(rotation);
			rotMat[0][1] = sin(rotation);
			rotMat[1][0] = -sin(rotation);
			rotMat[1][1] = cos(rotation);

			return oldMat * rotMat;
		}

		throw new exception("Not a valid axis");
	}

	//Dynamic mat4 rotation
	glm::mat4 rotate(glm::mat4 oldMat, float rotation, glm::vec3 normal) {
		//result matrix
		glm::mat4 result = glm::mat4(1.0f);

		//finding axis we're gonna rotate on
		glm::vec3 axis = roml::normalize(normal);
		glm::vec3 temp = glm::vec3((1 - cos(rotation)) * axis);

		//Quaternian-ish dynamic rotate matrix
		glm::mat4 rotMat = glm::mat4(1.0f);
		rotMat[0] = glm::vec4(cos(rotation) + temp.x * axis.x, temp.x * axis.y + sin(rotation) * axis.z, temp.x * axis.z - sin(rotation) * axis.y, 0);
		rotMat[1] = glm::vec4(temp.y * axis.x - sin(rotation) * axis.z, cos(rotation) + temp.y * axis.y, temp.y * axis.z + sin(rotation) * axis.x, 0);
		rotMat[2] = glm::vec4(temp.z * axis.x + sin(rotation) * axis.y, temp.z * axis.y - sin(rotation) * axis.x, cos(rotation) + temp.z * axis.z, 0);
		//No need to fill in the 4th row since the initialization of the result matrix takes care of that

		result = rotMat * oldMat;
		return result;
	}

	//Gives the vec3 a length of 1
	glm::vec3 normalize(glm::vec3 vector) {
		//vector * the magnitude of the vector
		return vector * inversesqrt(roml::dot(vector, vector));
	}


	//rotates vec3's
	glm::vec3 rotate(glm::vec3 vector, float angle, glm::vec3 normal) {
		//result vector
		glm::vec3 result;

		//finding axis we're gonna rotate on
		glm::vec3 axis = roml::normalize(normal);
		glm::vec3 temp = glm::vec3((1 - cos(angle)) * axis);

		//brief explanation; The OpenGL 'rotate' function uses a quaternian way of calculating and outputting (which outputs a mat4 in this case). Meanwhile, this rotate uses a eular way of calculating and outputting which uses a mat3 and outputs a mat3 or a mat4.
		glm::mat3 rotMat = glm::mat3(1.0f);
		rotMat[0] = glm::vec3(cos(angle) + temp.x * axis.x, temp.x * axis.y + sin(angle) * axis.z, temp.x * axis.z - sin(angle) * axis.y);
		rotMat[1] = glm::vec3(temp.y * axis.x - sin(angle) * axis.z, cos(angle) + temp.y * axis.y, temp.y * axis.z + sin(angle) * axis.x);
		rotMat[2] = glm::vec3(temp.z * axis.x + sin(angle) * axis.y, temp.z * axis.y - sin(angle) * axis.x, cos(angle) + temp.z * axis.z);

		result = rotMat * vector;
		return result;
	}

	//The inverse of a square root
	float inversesqrt(float x) {
		float result = 1 / sqrt(x);
		return result;
	}

	//This isn't in glm but in one of CPP's native libraries, I couldnt find it so I just made one (yes i could just set the reverse value but oh well)
	glm::vec3 negateV3(glm::vec3 vec) {
		vec * -1.0f;
		return vec;
	}


	float angle(glm::vec3 VecA, glm::vec3 VecB) {
		//Calculate the magnitude of VecA & VecB
		float newA = sqrt(VecA.x + VecA.y + VecA.z);
		float newB = sqrt(VecB.x + VecB.y + VecB.z);

		//Multiply newA and newB and get the angle back
		float result = newA * newB;
		return result;
	}


	glm::vec3 cross(glm::vec3 a, glm::vec3 b) {
		glm::vec3 result;

		//Finding the cross product between two vectors.
		result[0] = a.y * b.z - b.y * a.z;
		result[1] = a.z * b.x - b.z * a.x;
		result[2] = a.x* b.y - b.x * a.y;

		return result;
	}
	//Calculate vector dot product
	float dot(glm::vec3 vecA, glm::vec3 vecB) {
		float result = (vecA.x * vecB.x) + (vecA.y * vecB.y) + (vecA.z * vecB.z);
		return result;
	}

	glm::mat4 lookAt(glm::vec3 eye, glm::vec3 look, glm::vec3 up) { //eye defines position, look defines what you are looking at, and up specifies the direction of the camera

		//This took much longer than i'd like to admit

		//Setting up axis's
		glm::vec3 zaxis = roml::normalize(look - eye); //giving it a length 1 with normalize, (making it a unit vector)
		glm::vec3 xaxis = roml::normalize(glm::cross(zaxis, up));
		glm::vec3 yaxis = roml::cross(xaxis, zaxis);

		roml::negateV3(zaxis);

		//Creating the matrix
		glm::mat4 result = glm::mat4(1.0f);

		//technically this is also called a view matrix but its layouut is different for a static view matrix 
		result[0][0] = xaxis.x;
		result[1][0] = xaxis.y;
		result[2][0] = xaxis.z;
		result[0][1] = yaxis.x;
		result[1][1] = yaxis.y;
		result[2][1] = yaxis.z;
		result[0][2] = -zaxis.x;
		result[1][2] = -zaxis.y;
		result[2][2] = -zaxis.z;
		result[3][0] = -roml::dot(xaxis, eye);
		result[3][1] = -roml::dot(yaxis, eye);
		result[3][2] = roml::dot(zaxis, eye);

		return result;

	}

	// Translates degrees to radians
	float radians(float deg) {
		return deg * (M_PI / 180.0);
	}
#endif
}