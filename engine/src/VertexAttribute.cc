#include "VertexAttribute.hh"

VertexAttribute::VertexAttribute(unsigned int location, unsigned int count, unsigned int type, unsigned int normalized) :
    m_location(location),
    m_count(count),
    m_type(type),
    m_normalized(normalized)
{}

unsigned int VertexAttribute::getLocation() const
{
    return m_location;
}

unsigned int VertexAttribute::getCount() const
{
    return m_count;
}

unsigned int VertexAttribute::getType() const
{
    return m_type;
}

unsigned int VertexAttribute::getNormalized() const
{
    return m_normalized;
}
