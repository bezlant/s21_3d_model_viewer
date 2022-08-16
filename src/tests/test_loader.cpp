#include "gtest/gtest.h"
#include "../loader/loader.hpp"

TEST(test_loader, simple_loader) {
    std::vector<glm::vec3> vertices;
    size_t fc = 0, vc = 0;
    load_obj("./models/pyramid.obj", vertices, fc, vc);

    float vals[][3] = {
        {0, 1, 0},   {-1, 0, -1}, {1, 0, -1}, {0, 1, 0},   {1, 0, -1},
        {1, 0, 1},   {0, 1, 0},   {1, 0, 1},  {-1, 0, 1},  {0, 1, 0},
        {-1, 0, 1},  {-1, 0, -1}, {1, 0, -1}, {-1, 0, -1}, {1, 0, 1},
        {-1, 0, -1}, {-1, 0, 1},  {1, 0, 1},

    };

    for (size_t i = 0; i < vertices.size(); i++) {
        ASSERT_NEAR(vals[i][0], vertices[i][0], 1e-02);
        ASSERT_NEAR(vals[i][1], vertices[i][1], 1e-02);
        ASSERT_NEAR(vals[i][2], vertices[i][2], 1e-02);
    }
}

TEST(test_loader, simple_loader1) {
    std::vector<glm::vec3> vertices;
    size_t fc = 0, vc = 0;
    load_obj("./models/box.obj", vertices, fc, vc);

    float vals[][3] = {
        {1, 1, -1},   {1, -1, -1},  {-1, -1, -1}, {1, 1, -1},  {-1, -1, -1},
        {-1, 1, -1},  {-1, -1, 1},  {-1, 1, 1},   {-1, 1, -1}, {-1, -1, 1},
        {-1, 1, -1},  {-1, -1, -1}, {1, -1, 1},   {1, 1, 1},   {-1, -1, 1},
        {1, 1, 1},    {-1, 1, 1},   {-1, -1, 1},  {1, -1, -1}, {1, 1, -1},
        {1, -1, 1},   {1, 1, -1},   {1, 1, 1},    {1, -1, 1},  {1, 1, -1},
        {-1, 1, -1},  {1, 1, 1},    {-1, 1, -1},  {-1, 1, 1},  {1, 1, 1},
        {1, -1, -1},  {1, -1, 1},   {-1, -1, 1},  {1, -1, -1}, {-1, -1, 1},
        {-1, -1, -1},

    };

    for (size_t i = 0; i < vertices.size(); i++) {
        ASSERT_NEAR(vals[i][0], vertices[i][0], 1e-02);
        ASSERT_NEAR(vals[i][1], vertices[i][1], 1e-02);
        ASSERT_NEAR(vals[i][2], vertices[i][2], 1e-02);
    }
}

TEST(test_loader, simple_loader2) {
    std::vector<glm::vec3> vertices;
    size_t fc = 0, vc = 0;
    load_obj("./models/octahedron.obj", vertices, fc, vc);

    float vals[][3] = {
        {0, -1, 0}, {1, 0, 0},  {0, 0, 1},  {-1, 0, 0}, {0, -1, 0}, {0, 0, 1},
        {0, 1, 0},  {-1, 0, 0}, {0, 0, 1},  {1, 0, 0},  {0, 1, 0},  {0, 0, 1},
        {1, 0, 0},  {0, -1, 0}, {0, 0, -1}, {0, -1, 0}, {-1, 0, 0}, {0, 0, -1},
        {-1, 0, 0}, {0, 1, 0},  {0, 0, -1}, {0, 1, 0},  {1, 0, 0},  {0, 0, -1},
    };

    for (size_t i = 0; i < vertices.size(); i++) {
        ASSERT_NEAR(vals[i][0], vertices[i][0], 1e-02);
        ASSERT_NEAR(vals[i][1], vertices[i][1], 1e-02);
        ASSERT_NEAR(vals[i][2], vertices[i][2], 1e-02);
    }
}

TEST(test_loader, simple_loader3) {
    std::vector<glm::vec3> vertices;
    size_t fc = 0, vc = 0;
    load_obj("./models/tetrahedron.obj", vertices, fc, vc);

    float vals[][3] = {
        {1, 1, 1}, {1, 2, 1}, {2, 1, 1}, {1, 1, 1}, {1, 1, 2}, {1, 2, 1},
        {1, 1, 1}, {2, 1, 1}, {1, 1, 2}, {2, 1, 1}, {1, 2, 1}, {1, 1, 2},
    };

    for (size_t i = 0; i < vertices.size(); i++) {
        ASSERT_NEAR(vals[i][0], vertices[i][0], 1e-02);
        ASSERT_NEAR(vals[i][1], vertices[i][1], 1e-02);
        ASSERT_NEAR(vals[i][2], vertices[i][2], 1e-02);
    }
}
