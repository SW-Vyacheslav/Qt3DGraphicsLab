#ifndef ZBUFFER_H
#define ZBUFFER_H

class ZBuffer
{
public:
    ZBuffer(const int& width, const int& height);
    ZBuffer(const ZBuffer& buf) = delete;
    ~ZBuffer();

    void Clear();

    float ElementAt(const int& x, const int& y);
    bool CheckAndSet(const int& x, const int& y, const float& depth);

    ZBuffer& operator=(const ZBuffer& buf) = delete;

private:
    float* m_buffer;
    int m_width;
    int m_height;
};

#endif // ZBUFFER_H
