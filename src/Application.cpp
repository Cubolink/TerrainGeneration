#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glerrorhandler.h"

#include "light.h"
#include "material.h"
#include "texture.h"
#include "shape.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "controler.h"
#include "noise.h"
#include "obj_files.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


int w_width = 1024;
int w_height = 576;
CameraController cameraController;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
        case GLFW_KEY_W:
            cameraController.m_forth = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;

        case GLFW_KEY_S:
            cameraController.m_back = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;

        case GLFW_KEY_A:
            cameraController.m_left = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;

        case GLFW_KEY_D:
            cameraController.m_right = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_SPACE:
            cameraController.m_up = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            cameraController.m_down = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_LEFT:
            cameraController.rot_left = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_RIGHT:
            cameraController.rot_right = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_UP:
            cameraController.rot_up = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        case GLFW_KEY_DOWN:
            cameraController.rot_down = (action == GLFW_PRESS || action == GLFW_REPEAT) ? 1: 0;
            break;
        default:
            break;
    }


}


int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(w_width, w_height, "Haro wado", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Make a key callback for the window */
    glfwSetKeyCallback(window, key_callback);

    if (glewInit() != GLEW_OK) std::cout << "Error! glew is not ok." << std::endl;
    std::cout << "Current GL Version: " << glGetString(GL_VERSION) << std::endl;


    /* Starting main program */

    /* Configuring GL */
    GLCall(glClearColor(0.43f, 0.39f, 0.48f, 1.0f));
    GLCall(glEnable(GL_DEPTH_TEST));  // enable depth buffer
    GLCall(glEnable(GL_CLIP_DISTANCE0));  // clipping distance
    GLCall(glFrontFace(GL_CCW));  // set ccw mode, useful in particular for culling, but we don't want culling here
    /*
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    */
    GLCall(glEnable(GL_BLEND));  // enable transparency
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // set blending function
    GLCall(glBlendEquation(GL_FUNC_ADD));  // set blending results mixer function

    /* Creating model */

    float w_proportion = ((float) w_height)/((float) w_width);
    //glm::mat4 projection_m = glm::ortho(-1/w_proportion, 1/w_proportion, -1.0f, 1.0f, -1.0f, 1.0f);  // projection left, right, top, bottom, near, far
    glm::mat4 projection_m = glm::perspective(glm::radians(50.0f), (float) 1/w_proportion, 0.1f, 100.0f);

    Camera camera = Camera();
    camera.setEye(0, 0, 0);
    camera.setCenter(0, 0, -1);
    cameraController.setCamera(&camera);

    glm::vec3 translation = glm::vec3(0, 0, -2.f);
    glm::mat4 model_m;// = glm::translate(glm::mat4(1.0f), translation);

    Shader c_mpv_shaderProgram = Shader("resources/shaders/color_mpv_shader.shader");
    Shader t_mpv_shaderProgram = Shader("resources/shaders/texture_mpv_shader.shader");
    Shader gouraurd_c_shaderProgram = Shader("resources/shaders/gouraud_color_mpv.shader");

    Texture texture = Texture("resources/textures/red_yoshi.png");
    Shape square_shape = createTextureQuad();
    Shape axis_shape = createColorAxis(1);
    Shape normal_color_cube_shape = createColorNormalCube(0.2, 0.3, 0.7);
    std::vector<std::vector<float>> grid_map(100, std::vector<float>(100, 0));

    Material cube_material = Material(0.3f, 0.2f, 0.6f, 100, texture);
    Light light = Light(1.0f, 1.0f, 1.0f, glm::vec3(-5, -5, 5),
                        0.0001f, 0.03f, 0.01f);
    /*The binding goes on the loop*/

    Renderer renderer = Renderer();

    // Setup ImGUI context
    ImGui::CreateContext();
    // Setup ImGui Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Some ImgGui variable states
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glfwSwapInterval(1); // enables vsync
    float scale = 1, persistance = 1.7, lacunarity = 0.2;
    int seed = 314, octaves = 4;
    float offset_x = 0, offset_y = 0;
    float amplitude = 5;
    float water_level = 0.45;
    bool outdated = false;
    NoiseGenerator::generatePerlinNoiseMap(grid_map, seed, scale, octaves, persistance, lacunarity, offset_x, offset_y, amplitude);
    Shape terrain = createColorNoiseMap(grid_map, amplitude*water_level);

    double t0 = glfwGetTime();
    double t1, dt;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        t1 = glfwGetTime();
        dt = t1 - t0;
        t0 = t1;

        /* Render here */
        renderer.Clear();

        // Start ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Updating camera data
        /*view_m = camera.getViewMatrix();*/
        cameraController.updateCameraProperties();
        camera.updateCoords((float) dt);

        // Updating model data

        model_m = glm::translate(glm::mat4(1.0f), translation);

        if (outdated)
        {
            NoiseGenerator::generatePerlinNoiseMap(grid_map, seed, scale, octaves, persistance, lacunarity, offset_x, offset_y, amplitude);
            terrain = createColorNoiseMap(grid_map, amplitude*water_level);
            outdated = false;
        }

        // Updating uniforms

        t_mpv_shaderProgram.Bind();
        t_mpv_shaderProgram.SetUniformMat4f("u_projection", projection_m);
        t_mpv_shaderProgram.SetUniformMat4f("u_view", camera.getViewMatrix());//view_m);
        t_mpv_shaderProgram.SetUniformMat4f("u_model", model_m);
        t_mpv_shaderProgram.SetUniform1i("u_texture", 0);  // we pass the slot, the same as in texture.Bind(0). By default is 0, I explicitely wrote 0 here to clarify.

        c_mpv_shaderProgram.Bind();
        c_mpv_shaderProgram.SetUniformMat4f("u_projection", projection_m);
        c_mpv_shaderProgram.SetUniformMat4f("u_view", camera.getViewMatrix());
        c_mpv_shaderProgram.SetUniformMat4f("u_model", model_m);

        gouraurd_c_shaderProgram.Bind();
        gouraurd_c_shaderProgram.SetUniformMat4f("u_projection", projection_m);
        gouraurd_c_shaderProgram.SetUniformMat4f("u_view", camera.getViewMatrix());
        gouraurd_c_shaderProgram.SetUniformMat4f("u_model", model_m);
        glm::vec3 cam_pos = camera.getEyeVec3();
        gouraurd_c_shaderProgram.SetUniform3f("u_viewPosition", cam_pos.x, cam_pos.y, cam_pos.z);

        renderer.Draw(square_shape, texture, t_mpv_shaderProgram, GL_TRIANGLES);
        renderer.Draw(normal_color_cube_shape, cube_material, light, gouraurd_c_shaderProgram, GL_TRIANGLES);
        renderer.Draw(terrain, cube_material, light, gouraurd_c_shaderProgram, GL_TRIANGLES);
        renderer.Draw(axis_shape, texture, c_mpv_shaderProgram, GL_LINES);

        {
            ImGui::Begin("Variables");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Translation");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("x", &translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("y", &translation.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &translation.z, -100.0f, -1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Camera");
            ImGui::Text("-> center: (%.3f, %.3f, %.3f)", camera.getCX(), camera.getCY(), camera.getCZ());
            ImGui::Text("-> phi: %.3f, theta: %.3f", camera.getPhi(), camera.getTheta());

            ImGui::Text("Perlin Terrain Parameters");
            if (ImGui::SliderInt("seed", &seed, 1, 400))
                outdated = true;
            if (ImGui::SliderFloat("scale", &scale, 0.01f, 10.f))
                outdated = true;

//            ImGui::SliderFloat("offset x", &offset_x, -100.f, 100.f);
//            ImGui::SliderFloat("offset y", &offset_y, -100.f, 100.f);
            if(ImGui::SliderInt("octaves", &octaves, 1, 8))
                outdated = true;
            if(ImGui::SliderFloat("persistance", &persistance, 1.f, 50.f))
                outdated = true;
            if(ImGui::SliderFloat("lacunarity", &lacunarity, 0.01f, 1.f))
                outdated = true;
            if(ImGui::SliderFloat("amplitude", &amplitude, 1.f, 20.f))
                outdated = true;
            if(ImGui::SliderFloat("water level", &water_level, 0.f, 1.f))
                outdated = true;

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }



        // ImGui Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    std::cout << "Window should close" << std::endl;
    std::cout << "Cleaning up ImGui" << std::endl;
    // ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    /* End of the program */
    std::cout << "Storing shape" << std::endl;
    Obj::storeShape(terrain, "terrain.obj");

    std::cout << "Destroying window" << std::endl;

    glfwDestroyWindow(window);
    glfwPollEvents();

    std::cout << "Terminating glfw" << std::endl;

    glfwTerminate();

    std::cout << "Closing program" << std::endl;
    return 0;
}