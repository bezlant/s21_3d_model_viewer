#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "../includes/common.h"

/**
 * @brief Generates random colors for each vertex
 *
 * @param colors Ptr to the array to write colors to
 * @param size Size of the vertices array
 */
void generate_random_colors(GLfloat colors[], size_t size);

/**
 * @brief Gets filename from an absolute path
 *
 * @param s String (full path to the file)
 */
std::string get_filename(std::string s);

/**
 * @brief Computes the Model View Projection
 *
 * @param zoom Field of View
 * @param rotateCamera Value to rotate the camera
 * @param init_pos Initial position of the camera
 * @param y Y of the translation vector
 * @param z X of the translation vector
 */
glm::mat4 compute_mvp(float &zoom, float &rotateCamera, glm::vec3 &init_pos,
                      float &y, float &z);

#endif  // UTILS_HPP_
