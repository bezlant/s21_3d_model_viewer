#include "utils.hpp"

std::string get_filename(std::string s) {
    return s.substr(s.find_last_of("/") + 1);
}

glm::mat4 compute_mvp(float &zoom, float &rotateCamera, glm::vec3 &init_pos,
                      float &y, float &z) {
    glm::mat4 Projection = glm::perspective(
        glm::radians(zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f,
        100.0f);

    glm::vec3 rotate(cos(rotateCamera) * 10.0 - init_pos.x, 0,
                     sin(rotateCamera) * 10.0 - init_pos.z);

    glm::vec position = init_pos + rotate;

    glm::mat4 View =
        glm::lookAt(position,            // Camera is at in World Space
                    glm::vec3(0, 0, 0),  // Camera looking at (origin)
                    glm::vec3(0, 1, 0)   // Head (0,-1,0 to look upside-down)
        );

    glm::mat4 Model = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, y, z));
    glm::mat4 MVP = Projection * View * Model;
    return MVP;
}

void generate_random_colors(GLfloat colors[], size_t size) {
    for (size_t v = 0; v < size * 3; v++) {
        colors[3 * v + 0] = float(rand()) / float(RAND_MAX);
        colors[3 * v + 1] = float(rand()) / float(RAND_MAX);
        colors[3 * v + 2] = float(rand()) / float(RAND_MAX);
    }
}
