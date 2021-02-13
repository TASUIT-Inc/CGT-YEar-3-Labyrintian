#include "Light.h"

Light::Light(glm::vec3 color, glm::vec3 Direction) : m_Direction(Direction), m_Colour(color), type(0) {}  //Directional Light

Light::Light(glm::vec3 pos, glm::vec3 color, float Linear, float Quadratic) : m_Pos(pos), m_Linear(Linear), m_Quadratic(Quadratic), m_Colour(color), type(1) {} //Point Light

Light::Light(glm::vec3 pos, glm::vec3 color, glm::vec3 direction, float CTheta) : m_Pos(pos), m_Direction(direction), m_Theta(CTheta), m_Colour(color), type(2) {} //Spot Light

