#ifndef MOVABLE_PTR_HPP
#define MOVABLE_PTR_HPP

#include <utility>

namespace SDL3pp
{

template <class T>
class movable_ptr final
{
public:
    movable_ptr(T *ptr = nullptr) noexcept : m_ptr(ptr)
    {
    }

    movable_ptr(const movable_ptr &) = delete;

    movable_ptr(movable_ptr &&ptr) noexcept : m_ptr(ptr)
    {
        ptr.m_ptr = nullptr;
    }

    ~movable_ptr() = default;

    T *get() noexcept
    {
        return m_ptr;
    }

    const T *get() const noexcept
    {
        return m_ptr;
    }

    operator T *() noexcept
    {
        return m_ptr;
    }

    operator const T *() const noexcept
    {
        return m_ptr;
    }

    T& operator->()
    {
        return *m_ptr;
    }

    T const& operator->() const
    {
        return *m_ptr;
    }

    movable_ptr &operator=(movable_ptr &&ptr) noexcept
    {
        m_ptr = ptr.m_ptr;
        ptr.m_ptr = nullptr;
        return *this;
    }

private:
    T *m_ptr;

};

}

#endif
