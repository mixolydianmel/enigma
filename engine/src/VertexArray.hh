#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include <vector>
#include "VertexAttribute.hh"

class VertexArray
{
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        unsigned int getSizeOfAttribute(VertexAttribute& attrib) const;
        void pushAttribute(VertexAttribute& attrib);

        void setPointers() const;
    private:
        std::vector<VertexAttribute> m_attributes;
        unsigned int m_rendererID;
        unsigned int m_totalSize;
};

#endif
