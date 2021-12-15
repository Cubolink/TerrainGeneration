#include "glerrorhandler.h"

#include <iostream>


/**
* Clears the GL error trace.
*/
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
/**
* couts an OpenGL Error hex code in case there's one, indicating the file, function and line where the error was detected.
* @param function The name of the function that contains a code line.
* @param file Name of the file where the line is.
* @param line Number of the code line.
* @return false if there was an error, true is all was right.
*/
bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error 0x" << std::hex << error << std::dec << "]:\n"
            << "\tat line " << line << ": " << function
            << "\n\ton file \"" << file << "\"" << std::endl;
        return false;
    }
    return true;
}