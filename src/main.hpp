#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "common.h"
#include "shader/shader.hpp"
#include "loader/loader.hpp"

const char PROGRAM_TITLE[] = "3d Model Viewer";

std::string get_filename(std::string s);
glm::mat4 compute_mvp(float &zoom, float &rotateCamera, glm::vec3 &init_pos,
                      float &y, float &z);
#endif  // MAIN_HPP_
