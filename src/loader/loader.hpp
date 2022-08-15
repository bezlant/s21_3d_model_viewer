#ifndef LOADER_H_
#define LOADER_H_

#include "../includes/common.h"
bool load_obj(const char *filename, std::vector<glm::vec3> &vertices,
              size_t &faces_count, size_t &vertices_count);

#endif  // LOADER_H_
