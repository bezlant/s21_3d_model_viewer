#include "gtest/gtest.h"
#include "../utils/utils.hpp"

TEST(test_utils, filename1) {
    std::string s = "file/name/is/long/haha";
    EXPECT_STREQ(get_filename(s).c_str(), "haha");
}

TEST(test_utils, filename2) {
    std::string s = "a/difficult/p/a/t/h/t/o/thisfile";
    EXPECT_STREQ(get_filename(s).c_str(), "thisfile");
}

TEST(test_utils, filename3) {
    std::string s = "I/LOVE/SEXY/FLOPPA";
    EXPECT_STREQ(get_filename(s).c_str(), "FLOPPA");
}

TEST(test_utils, random_colors1) {
    size_t s = 60;
    GLfloat colors[540];

    generate_random_colors(colors, s);

    for (size_t i = 0; i < 180; i++) {
        EXPECT_LE(colors[i], 1.0f);
        EXPECT_GE(colors[i], 0.0f);
    }
}

TEST(test_utils, random_colors2) {
    size_t s = 1024;
    GLfloat colors[9216];

    generate_random_colors(colors, s);

    for (size_t i = 0; i < 180; i++) {
        EXPECT_LE(colors[i], 1.0f);
        EXPECT_GE(colors[i], 0.0f);
    }
}

TEST(test_utils, mvp) {
    float zoom = 45.0f;
    float rotate = 0.0f;
    glm::vec3 init(4, 3, 3);
    float y = 0.0f;
    float z = 0.0f;

    glm::mat4 mvp = compute_mvp(zoom, rotate, init, y, z);
    float expected[][4] = {
        {0, -0.693719, -0.959744, -0.957826},
        {0, 2.3124, -0.287923, -0.287348},
        {-1.358, 0, 0, 0},
        {0, 0, 10.261, 10.4403},
    };

    for (size_t i = 0; i < 4; i++) {
        ASSERT_NEAR(expected[i][0], mvp[i][0], 1e-02);
        ASSERT_NEAR(expected[i][1], mvp[i][1], 1e-02);
        ASSERT_NEAR(expected[i][2], mvp[i][2], 1e-02);
        ASSERT_NEAR(expected[i][3], mvp[i][3], 1e-02);
    }
}

TEST(test_utils, mvp1) {
    float zoom = 69.0f;
    float rotate = 420.0f;
    glm::vec3 init(4, 2, 0);
    float y = 69.0f;
    float z = 420.0f;

    glm::mat4 mvp = compute_mvp(zoom, rotate, init, y, z);
    float expected[][4] = {
        {-0.676698, -0.160504, -0.55266, -0.551556},
        {0, 1.42675, -0.196509, -0.196116},
        {-0.460357, 0.235931, 0.812379, 0.810756},
        {-193.35, 197.537, 337.658, 337.183},
    };

    for (size_t i = 0; i < 4; i++) {
        ASSERT_NEAR(expected[i][0], mvp[i][0], 1e-02);
        ASSERT_NEAR(expected[i][1], mvp[i][1], 1e-02);
        ASSERT_NEAR(expected[i][2], mvp[i][2], 1e-02);
        ASSERT_NEAR(expected[i][3], mvp[i][3], 1e-02);
    }
}
