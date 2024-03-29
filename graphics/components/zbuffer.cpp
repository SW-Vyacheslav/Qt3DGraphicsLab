#include "zbuffer.h"
#include <limits>

ZBuffer::ZBuffer(const int &width, const int &height) :
    m_buffer(new float[static_cast<unsigned int>(width * height)]),
    m_width(width),
    m_height(height)
{}

ZBuffer::~ZBuffer()
{
    delete[] m_buffer;
    m_buffer = nullptr;
}

void ZBuffer::Clear()
{
    const int length = m_width * m_height;
    for (int i = 0; i < length; ++i)
    {
        m_buffer[i] = std::numeric_limits<float>::infinity();
    }
}

float ZBuffer::ElementAt(const int &x, const int &y)
{
    if (x < 0 || x > m_width - 1) return 0.0f;
    if (y < 0 || y > m_height - 1) return 0.0f;
    return m_buffer[y * m_width + x];
}

bool ZBuffer::CheckAndSet(const int &x, const int &y, const float &depth)
{
    if (x < 0 || x > m_width - 1) return false;
    if (y < 0 || y > m_height - 1) return false;

    if (depth < ElementAt(x, y))
    {
        m_buffer[y * m_width + x] = depth;
        return true;
    }
    return false;
}
