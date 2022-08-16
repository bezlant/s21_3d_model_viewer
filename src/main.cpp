#define GL_SILENCE_DEPRECATION
#include "main.hpp"

static inline void init_imgui(GLFWwindow *window);
static inline void init_glfw();
static inline void init_glew();
static inline void process_input(GLFWwindow *window);
static inline void imgui_postprocess();
static inline void imgui_preprocess();
static inline GLFWwindow *create_window();
static inline ImGui::FileBrowser init_filebrowser();
static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height);
static inline void glfw_error_callback(int error, const char *description);
static inline void generate_random_colors(GLfloat colors[], size_t size);

int main(void) {
    srand(time(0));
    init_glfw();
    GLFWwindow *window = create_window();

    init_glew();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Init VAO (woodoo)
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    init_imgui(window);
    ImGui::FileBrowser fileDialog = init_filebrowser();

    // Imgui Defaults
    ImVec4 bg_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    float zoom = 45.0f;
    int draw_type = GL_TRIANGLES;
    float rotateCamera = 0.0f;
    glm::vec3 init_pos(4, 3, 3);
    float y = 0.0f, z = 0.0f;

    // Load shaders
    GLuint programID =
        LoadShaders("./shader/vshader.glsl", "./shader/fshader.glsl");
    glUseProgram(programID);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Vertices for loading
    std::vector<glm::vec3> vertices;
    std::string path = "./models/pyramid.obj";
    size_t faces_count = 0;
    size_t vertices_count = 0;
    load_obj(path.c_str(), vertices, faces_count, vertices_count);

    // Some woodoo magic to load the vertices
    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);

    GLfloat *color_buffer_data = new GLfloat[vertices.size() * 3 * 3];
    generate_random_colors(color_buffer_data, vertices.size());

    GLuint color_buffer;
    glGenBuffers(1, &color_buffer);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(bg_color.x * bg_color.w, bg_color.y * bg_color.w,
                     bg_color.z * bg_color.w, bg_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        process_input(window);
        imgui_preprocess();

        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * 3,
                     color_buffer_data, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                     &vertices[0], GL_STATIC_DRAW);

        // Projection & View
        glm::mat4 MVP = compute_mvp(zoom, rotateCamera, init_pos, y, z);

        // Send our transformation to the currently bound shader,
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Some woodoo magic
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        // Drawing GL_LINE_STRIP GL_TRIANGLES
        glDrawArrays(draw_type, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        {
            if (ImGui::Begin("Main Menu")) {
                if (ImGui::Button("Open file"))
                    fileDialog.Open();

                ImGui::SameLine();
                ImGui::Text("%s", get_filename(path).c_str());
                ImGui::Text("Vertices: %zu", vertices_count);
                ImGui::SameLine();
                ImGui::Text("Edges: %zu", faces_count);
                ImGui::ColorEdit4("Color", (float *)&bg_color);
                ImGui::RadioButton("GL_TRIANGLES", &draw_type, GL_TRIANGLES);
                ImGui::SameLine();
                ImGui::RadioButton("GL_LINE_STRIP", &draw_type, GL_LINE_STRIP);
                ImGui::SliderFloat("Zoom", &zoom, 69.0f, 4.20f);
                ImGui::SliderFloat("Rotate", &rotateCamera, -5.0f, 5.0f);
                ImGui::SliderFloat("Up/Down", &y, -5.0f, 5.0f);
                ImGui::SliderFloat("Left/Right", &z, -5.0f, 5.0f);
            }
            ImGui::End();

            fileDialog.Display();

            if (fileDialog.HasSelected()) {
                path = fileDialog.GetSelected();

                vertices.clear();
                faces_count = 0;
                vertices_count = 0;

                load_obj(path.c_str(), vertices, faces_count, vertices_count);

                delete[] color_buffer_data;
                color_buffer_data = new GLfloat[vertices.size() * 3 * 3];
                generate_random_colors(color_buffer_data, vertices.size());

                fileDialog.ClearSelected();
            }
        }

        imgui_postprocess();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteBuffers(1, &color_buffer);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();

    delete[] color_buffer_data;
    exit(EXIT_SUCCESS);
}

void generate_random_colors(GLfloat colors[], size_t size) {
    for (size_t v = 0; v < size * 3; v++) {
        colors[3 * v + 0] = float(rand()) / float(RAND_MAX);
        colors[3 * v + 1] = float(rand()) / float(RAND_MAX);
        colors[3 * v + 2] = float(rand()) / float(RAND_MAX);
    }
}

static inline void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static inline void framebuffer_size_callback(GLFWwindow *window, int width,
                                             int height) {
    glViewport(0, 0, width, height);
}

static inline void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static inline void init_glfw() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

static inline void init_imgui(GLFWwindow *window) {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

static inline ImGui::FileBrowser init_filebrowser() {
    ImGui::FileBrowser fileDialog;
    fileDialog.SetTitle("Select a 3d model to view:");
    fileDialog.SetTypeFilters({".obj"});
    return fileDialog;
}

static inline GLFWwindow *create_window() {
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                          PROGRAM_TITLE, NULL, NULL);
    if (!window)
        exit(EXIT_FAILURE);

    // Adjust viewport on resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    // Enable v-sync
    glfwSwapInterval(1);
    return window;
}

static inline void imgui_preprocess() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

static inline void imgui_postprocess() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

std::string get_filename(std::string s) {
    return s.substr(s.find_last_of("/") + 1);
}

static inline void init_glew() {
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
        exit(EXIT_FAILURE);
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
