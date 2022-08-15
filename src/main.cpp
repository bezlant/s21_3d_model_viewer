#define GL_SILENCE_DEPRECATION
#include "common.h"
#include "shader/shader.hpp"
#include "loader/loader.hpp"

/*
 The graphical user interface must contain:
 A button to select the model file and a field to output its name.
 A visualisation area for the wireframe model.
 Button/buttons and input fields for translating the model.
 Button/buttons and input fields for rotating the model.
 Button/buttons and input fields for scaling the model.
 Information about the uploaded model - file name, number of vertices and edges.
 https://learnopengl.com/
 https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/

const char PROGRAM_TITLE[] = "3d Model Viewer";

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
std::string get_filename(std::string s);

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

    // Load shaders
    GLuint programID =
        LoadShaders("./shader/vshader.glsl", "./shader/fshader.glsl");
    glUseProgram(programID);

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection & View
    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f,
        100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(8, 4, 3),  // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0),  // and looks at the origin
        glm::vec3(0, -1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;

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
    for (int v = 0; v < vertices.size() * 3; v++) {
        color_buffer_data[3 * v + 0] = float(rand()) / float(RAND_MAX);
        color_buffer_data[3 * v + 1] = float(rand()) / float(RAND_MAX);
        color_buffer_data[3 * v + 2] = float(rand()) / float(RAND_MAX);
    }

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

        // Send our transformation to the currently bound shader,
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Some woodoo magic
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        // Drawing
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        {
            if (ImGui::Begin("Main Menu")) {
                if (ImGui::Button("Open file"))
                    fileDialog.Open();

                ImGui::SameLine();
                ImGui::Text("%s", get_filename(path).c_str());
                ImGui::Text("Vertices: %zu", vertices_count);
                ImGui::Text("Edges: %zu", faces_count);
                ImGui::ColorEdit4("Color", (float *)&bg_color);
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
                for (int v = 0; v < vertices.size() * 3; v++) {
                    color_buffer_data[3 * v + 0] =
                        float(rand()) / float(RAND_MAX);
                    color_buffer_data[3 * v + 1] =
                        float(rand()) / float(RAND_MAX);
                    color_buffer_data[3 * v + 2] =
                        float(rand()) / float(RAND_MAX);
                }

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
