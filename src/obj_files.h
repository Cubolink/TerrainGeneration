//
// Created by major on 28-12-2021.
//

#ifndef TERRAINGEN_OBJ_FILES_H
#define TERRAINGEN_OBJ_FILES_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "shape.h"

namespace Obj
{
    void storeShape(Shape &shape, const std::string &filepath)
    {
        std::ofstream f_stream(filepath);

        auto vertices = shape.getVertices();
        auto indices = shape.getIndices();

        for (unsigned int i = 0; i < vertices.size(); i += 9)
            f_stream << "v " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << "\n";
        for (unsigned int i = 6; i < vertices.size(); i += 9)
            f_stream << "vn " << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << "\n";

        for (unsigned int i = 0; i < indices.size(); i += 3)
        {
            f_stream << "f ";
            f_stream << indices[i] + 1 << "//" << indices[i] + 1 << " ";
            f_stream << indices[i+1] + 1 << "//" << indices[i+1] + 1 << " ";
            f_stream << indices[i+2] + 1 << "//" << indices[i+2] + 1 << " ";
            f_stream << "\n";
        }
    }
}

#endif //TERRAINGEN_OBJ_FILES_H
