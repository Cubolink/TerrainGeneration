#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glerrorhandler.h"

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "texture.h"
#include "renderer.h"

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
    window = glfwCreateWindow(w_width, w_height, "Haro wado", NULL, NULL);
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


    float triangle_vertex_positions[] = {
        // x,      y,   tx,   ty
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));  // enable blending (transparency)

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  // define how openGL will blend alpha. Takes the source alpha ans use 1 - that when rendering somthing in the top.
    // Nex line is GL_ADD by default, we don't have to explicitely write it, but I want to write it.
    GLCall(glBlendEquation(GL_FUNC_ADD));  // set How we want to mix transparency.
    // So the resulting equation is:
    // (R,G,B,A) = (r_{src} * alpha_{src} + r_{dest} * (1 - alpha_{src}), ..., ...) = (r_{dest}, ..., ..., ...)

    VertexArray vao;
    VertexBuffer vbo = VertexBuffer(triangle_vertex_positions, sizeof(triangle_vertex_positions));
    VertexBufferLayout vblayout;
    vblayout.Push<float>(2);
    vblayout.Push<float>(2);
    vao.AddBuffer(vbo, vblayout);

    IndexBuffer ibo = IndexBuffer(indices, 6);

    float w_proportion = ((float) w_height)/w_width;
    //glm::mat4 projection_m = glm::ortho(-1/w_proportion, 1/w_proportion, -1.0f, 1.0f, -1.0f, 1.0f);  // projection left, right, top, bottom, near, far
    glm::mat4 projection_m = glm::perspective(glm::radians(50.0f), (float) 1/w_proportion, 0.1f, 100.0f);

    glm::vec3 position;// = glm::vec3(0, 0, 0);
    glm::vec3 look_at;// = glm::vec3(0, 0, -1);
    glm::mat4 view_m;// = glm::lookAt(position, look_at, glm::vec3(0, 1, 0));
    //glm::mat4 view_m = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));  // glm translate creates a transformation matrix from a vector, in this case goes from v3 to m4

    glm::vec3 translation = glm::vec3(0, 0, -2.f);
    glm::mat4 model_m;// = glm::translate(glm::mat4(1.0f), translation);

    glm::mat4 mvp_m; // = projection_m * view_m * model_m;

    Shader shaderProgram = Shader("resources/shaders/basic_texture_transform_shader.shader");
    shaderProgram.Bind();
    //shaderProgram.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
    shaderProgram.SetUniformMat4f("u_MVP", mvp_m);

    Texture texture = Texture("resources/textures/red_yoshi.png");
    texture.Bind(0);
    shaderProgram.SetUniform1i("u_texture", 0);  // we pass the slot, the same as in Bind(). By default is 0, I explicitely wrote 0 here to clarify.

    /*We're going to unbind all here, to test the correct binding in the loop*/
    shaderProgram.Unbind();
    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
    texture.Unbind();

    Renderer renderer = Renderer();

    // Setup ImGUI context
    ImGui::CreateContext();
    // Setup ImGui Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Some ImgGui variable states
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float red = 0.0f;
    float increment = 0.01f;
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

        mvp_m = projection_m * view_m * model_m;

        shaderProgram.Bind();
        texture.Bind();

        // Updating camera data
        position = glm::vec3(0, 0, 0);
        look_at = glm::vec3(0, 0, -1);
        view_m = glm::lookAt(position, look_at, glm::vec3(0, 1, 0));

        // Updating model data

        model_m = glm::translate(glm::mat4(1.0f), translation);

        //shaderProgram.SetUniform4f("u_color", red, 0.3f, 0.8f, 1.0f);
        shaderProgram.SetUniformMat4f("u_MVP", mvp_m);
        shaderProgram.SetUniform1i("u_texture", 0);

        renderer.Draw(vao, ibo, shaderProgram);

        if (red < 0.0f || red > 1.0f) increment = -increment;
        red += increment;

        {

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("Translation");               // Display some text (you can use a format strings too)

            ImGui::SliderFloat("x", &translation.x, -1.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("y", &translation.y, -1.0f, 1.0f);
            ImGui::SliderFloat("z", &translation.z, -100.0f, -1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
;

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

    std::cout << "Terminating glfw" << std::endl;

    glfwTerminate();

    std::cout << "Closing program" << std::endl;
    return 0;
}