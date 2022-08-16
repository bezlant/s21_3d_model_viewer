#ifndef LOADER_H_
#define LOADER_H_

#include "../includes/common.h"
/**
 * @brief Loads the Wavefront obj format into memory
 *
 * @param filename Path to the file
 * @param vertices Vector of vertices that we'll read from the file
 * @param faces_count Faces count
 * @param vertices_count Vertices count
 */
void load_obj(const char *filename, std::vector<glm::vec3> &vertices,
              size_t &faces_count, size_t &vertices_count);

#endif  // LOADER_H_
