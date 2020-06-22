#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <GL/glew.h>

class ElementBuffer
{
    public:
        ElementBuffer(const unsigned int* data, unsigned int count);
        ~ElementBuffer();

        void bind() const;
        void unbind() const;

        unsigned int getCount() const;
    private:
        unsigned int m_rendererID;
        unsigned int m_count;
};

#endif
