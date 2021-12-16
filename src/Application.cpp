#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glerrorhandler.h"

#include "shader.h"
#include "texture.h"
#include "renderer.h"
#include "shape.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


int w_width = 800;
int w_height = 600;


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

    if (glewInit() != GLEW_OK) std::cout << "Error! glew is not ok." << std::endl;
    std::cout << "Current GL Version: " << glGetString(GL_VERSION) << std::endl;


    /* Starting main program */


    GLCall(glEnable(GL_BLEND));  // enable blending (transparency)

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // define how openGL will blend alpha. Takes the source alpha ans use 1 - that when rendering somthing in the top.
    // Nex line is GL_ADD by default, we don't have to explicitely write it, but I want to write it.
    GLCall(glBlendEquation(GL_FUNC_ADD));  // set How we want to mix transparency.
    // So the resulting equation is:
    // (R,G,B,A) = (r_{src} * alpha_{src} + r_{dest} * (1 - alpha_{src}), ..., ...) = (r_{dest}, ..., ..., ...)

    float w_proportion = ((float) w_height)/((float) w_width);
    //glm::mat4 projection_m = glm::ortho(-1/w_proportion, 1/w_proportion, -1.0f, 1.0f, -1.0f, 1.0f);  // projection left, right, top, bottom, near, far
    glm::mat4 projection_m = glm::perspective(glm::radians(50.0f), (float) 1/w_proportion, 0.1f, 100.0f);

    glm::vec3 position;// = glm::vec3(0, 0, 0);
    glm::vec3 look_at;// = glm::vec3(0, 0, -1);
    glm::mat4 view_m;// = glm::lookAt(position, look_at, glm::vec3(0, 1, 0));
    //glm::mat4 view_m = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));  // glm translate creates a transformation matrix from a vector, in this case goes from v3 to m4

    glm::vec3 translation = glm::vec3(0, 0, -2.f);
    glm::mat4 model_m;// = glm::translate(glm::mat4(1.0f), translation);

    Shader shaderProgram = Shader("resources/shaders/texture_mpv_shader.shader");
    Texture texture = Texture("resources/textures/red_yoshi.png");
    Shape square_shape = createTextureQuad();

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        // Start ImGui new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Updating camera data
        position = glm::vec3(0, 0, 0);
        look_at = glm::vec3(0, 0, -1);
        view_m = glm::lookAt(position, look_at, glm::vec3(0, 1, 0));

        // Updating model data

        model_m = glm::translate(glm::mat4(1.0f), translation);

        // Updating uniforms

        shaderProgram.Bind();
        shaderProgram.SetUniformMat4f("u_projection", projection_m);
        shaderProgram.SetUniformMat4f("u_view", view_m);
        shaderProgram.SetUniformMat4f("u_model", model_m);
        shaderProgram.SetUniform1i("u_texture", 0);  // we pass the slot, the same as in texture.Bind(0). By default is 0, I explicitely wrote 0 here to clarify.

        renderer.Draw(square_shape, texture, shaderProgram);

        {

            ImGui::Begin("Variables");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Translation");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("x", &translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("y", &translation.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &translation.z, -100.0f, -1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

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


    std::cout << "Destroying window" << std::endl;

    glfwDestroyWindow(window);
    glfwPollEvents();

    std::cout << "Terminating glfw" << std::endl;

    glfwTerminate();

    std::cout << "Closing program" << std::endl;
    return 0;
}