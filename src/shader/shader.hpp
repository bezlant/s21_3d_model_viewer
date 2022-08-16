#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "common.h"

/**
 * @brief Loads a Vertex & Fragment shaders
 *
 * @param vertex_file_path Filepath to vertex shader
 * @param fragment_file_path Filepath to fragment shader
 * @return Returns the ID of the program to load
 */
GLuint LoadShaders(const char *vertex_file_path,
                   const char *fragment_file_path);

#endif  // SHADER_HPP_
