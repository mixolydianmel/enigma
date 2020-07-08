#include "VertexArray.hh"
#include <iostream>

VertexArray::VertexArray() : m_totalSize(0)
{
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

unsigned int VertexArray::getSizeOfAttribute(VertexAttribute& attrib) const
{
    unsigned int typeSize = 0;

    switch (attrib.getType())
    {
    case GL_BYTE:
        typeSize = sizeof(char);
	break;
    case GL_UNSIGNED_BYTE:
	typeSize = sizeof(unsigned char);
	break;
    case GL_SHORT:
	typeSize = sizeof(short int);
	break;
    case GL_UNSIGNED_SHORT:
	typeSize = sizeof(unsigned short int);
	break;
    case GL_INT:
	typeSize = sizeof(int);
	break;
    case GL_UNSIGNED_INT:
	typeSize = sizeof(unsigned int);
	break;
    case GL_FIXED:
	typeSize = 4;
	break;
    case GL_HALF_FLOAT:
	typeSize = sizeof(float) / 2;
	break;
    case GL_FLOAT:
	typeSize = sizeof(float);
	break;
    case GL_DOUBLE:
	typeSize = sizeof(double);
        break;
    default:
        typeSize = 0;
	break;
    }

    return (typeSize * attrib.getCount());
}

void VertexArray::pushAttribute(VertexAttribute& attrib)
{
    m_attributes.push_back(attrib);

    m_totalSize += getSizeOfAttribute(attrib);
}

void VertexArray::setPointers() const
{
    VertexAttribute currentAttrib = m_attributes.at(0);
    size_t currentOffset = 0;
    for (size_t i = 0; i < m_attributes.size(); i++)
    {
	currentAttrib = m_attributes.at(i);

	glVertexAttribPointer(currentAttrib.getLocation(), currentAttrib.getCount(), currentAttrib.getType(), currentAttrib.getNormalized(), m_totalSize, (void*)(currentOffset));
	glEnableVertexAttribArray(currentAttrib.getLocation());

	currentOffset += getSizeOfAttribute(currentAttrib);
    }
}
