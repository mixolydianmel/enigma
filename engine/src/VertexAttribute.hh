#ifndef VERTEXATTRIBUTE_H
#define VERTEXATTRIBUTE_H

struct VertexAttribute
{
    public:
        VertexAttribute(unsigned int location, unsigned int count, unsigned int type, unsigned int normalized);

        unsigned int getLocation() const;
        unsigned int getCount() const;
        unsigned int getType() const;
        unsigned int getNormalized() const;
    private:
        unsigned int m_location;
        unsigned int m_count;
        unsigned int m_type;
        unsigned int m_normalized;
};

#endif
