#include "loader.hpp"

void load_obj(const char *filename, std::vector<glm::vec3> &vertices,
              size_t &faces_count, size_t &vertices_count) {
    FILE *file = fopen(filename, "r");

    std::vector<size_t> vertex_idx;
    std::vector<glm::vec3> tmp_vertices;

    char *line = NULL;
    size_t linecap = 0;

    while (getline(&line, &linecap, file) > 0) {
        if (line[0] == 'v') {
            vertices_count++;
            glm::vec3 vertex;
            sscanf(line + 1, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
            tmp_vertices.push_back(vertex);
        }
        if (line[0] == 'f') {
            faces_count++;
            size_t v_index[3];
            sscanf(line + 1, "%zu %zu %zu", &v_index[0], &v_index[1],
                   &v_index[2]);
            vertex_idx.push_back(v_index[0]);
            vertex_idx.push_back(v_index[1]);
            vertex_idx.push_back(v_index[2]);
        }
    }

    for (size_t i = 0; i < vertex_idx.size(); i++) {
        glm::vec3 vertex = tmp_vertices[vertex_idx[i] - 1];
        vertices.push_back(vertex);
    }

    free(line);
    fclose(file);
}
