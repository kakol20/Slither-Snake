#pragma once


#include <string>
#include <glm.hpp>

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() = 0 { };

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;

	void SetTag(const std::string & tag) { m_tag = tag; };
	void SetAngle(const float angle) { m_angle = angle; };
	void SetAlive(const bool isAlive) { m_isAlive = isAlive; };
	void SetActive(const bool isActive) { m_isActive = isActive; };
	void SetVisible(const bool isVisible) { m_isVisible = isVisible; };
	void SetPosition(const float x, const float y, float z = 0) { m_position = glm::vec3(x, y, z); };

	const float GetLayer() const { return m_layer; };
	const std::string GetTag() const { return m_tag; };
	const glm::vec3 GetPosition() const { return m_position; };
	
	bool isAlive() const { return m_isAlive; };
	bool isActive() const { return m_isActive; };
	bool isVisible() const { return m_isVisible; };

private:


protected:
	// https://www.browserling.com/tools/line-length-sort

	float m_angle = 0.0f;
	std::string m_tag = "N/A";
	glm::vec3 m_position = glm::vec3(0.0f);

	float m_layer = 0.0f;
	
	bool m_isAlive = false;
	bool m_isActive = false;
	bool m_isVisible = false;
};
