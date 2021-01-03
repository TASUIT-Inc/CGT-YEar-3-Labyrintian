#include "Light.h"

Light::Light(LoaderParams* Params, /*Renderer* renderer,*/ glm::vec3 Direction) : Object(*Params), m_Direction(Direction), m_Colour(Params->GetColour()), type(0) {}  //Directional Light
								   /*					*/
Light::Light(LoaderParams* Params, /*Renderer* renderer,*/ float Linear, float Quadratic) : Object(*Params), m_Pos(Params->GetPos()), m_Linear(Linear), m_Quadratic(Quadratic), m_Colour(Params->GetColour()), type(1) {} //Point Light
								   /*					*/
Light::Light(LoaderParams* Params, /*Renderer* renderer,*/ glm::vec3 direction, float CTheta) : Object(*Params), m_Pos(Params->GetPos()), m_Direction(direction), m_Theta(CTheta), m_Colour(Params->GetColour()), type(2) {} //Spot Light

