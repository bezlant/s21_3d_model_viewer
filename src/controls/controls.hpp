#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "common.h"

void computeMatricesFromInputs(GLFWwindow *window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif  // CONTROLS_HPP
