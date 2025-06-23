#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float FOV = 45.0f;
const float SPEED = 2.5f;
const float Sensivity = 0.5f;



class CameraClass {

public:

	float yaw;
	float pitch;

	float sensivity;
	float movement_speed;

	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Pos;
	glm::vec3 WorldUp;
	glm::vec3 Right;


	CameraClass(glm::vec3 position = glm::vec3(0.0,0.0,0.0),glm::vec3 up = glm::vec3(0.0, 1.0, 0.0),float yaw=YAW, float pitch = PITCH) : Front(glm::vec3(0.0, 0.0, -1.0)), movement_speed(SPEED), sensivity(Sensivity) {
		Pos = position;
		this->yaw = yaw;
		this->pitch = pitch;
		WorldUp = up;
		update_camera_vector();
	}
	glm::mat4 getViewMatrix() {
		return glm::lookAt(Pos, Pos + Front, Up);
	}
	void Porcess_Keyboard_Input(Direction dir, float deltatime) {
		float velocity = movement_speed * deltatime;
		if (dir == FORWARD) {
			Pos += Front * velocity;
		}
		if (dir == BACKWARD) {
			Pos -= Front * velocity;
		}
		if (dir == RIGHT) {
			Pos += Right * velocity;
		}
		if (dir == LEFT) {
			Pos -= Right * velocity;
		}
	}
	void process_mouse_movement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= sensivity;
		yoffset *= sensivity;
		
		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		update_camera_vector();
	}
private:
	void update_camera_vector() {

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));  
		Up = glm::normalize(glm::cross(Right, Front));
	}
};
