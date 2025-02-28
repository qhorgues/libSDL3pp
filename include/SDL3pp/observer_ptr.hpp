#ifndef SDL3PP_OBSERVER_PTR_HPP
#define SDL3PP_OBSERVER_PTR_HPP

#include <bitset>
#include <cstddef>
#include <type_traits>

namespace SDL3pp {

template<typename T>
class observer_ptr
{
public:
  using element_type = T;
  using type_pointer = std::add_pointer_t<T>;
  using type_reference = std::add_lvalue_reference_t<T>;

  constexpr observer_ptr() noexcept
    : m_ptr()
  {
  }

  constexpr observer_ptr(std::nullptr_t) noexcept
    : m_ptr()
  {
  }

  constexpr explicit observer_ptr(type_pointer ptr) noexcept
    : m_ptr(ptr)
  {
  }

  template<typename U,
           typename = typename std::enable_if<
             std::is_convertible<typename std::add_pointer<U>::type,
                                 type_pointer>::value>::type>
  constexpr observer_ptr(observer_ptr<U> ptr) noexcept
    : m_ptr(ptr.get())
  {
  }

  // 3.2.3, observer_ptr observers
  constexpr type_pointer get() const noexcept { return m_ptr; }

  constexpr type_reference operator*() const { return *get(); }

  constexpr type_pointer operator->() const noexcept { return get(); }

  constexpr explicit operator bool() const noexcept { return get() != nullptr; }

  // 3.2.4, observer_ptr conversions
  constexpr explicit operator type_pointer() const noexcept { return get(); }

  // 3.2.5, observer_ptr modifiers
  constexpr type_pointer release() noexcept
  {
    type_pointer tmp = get();
    reset();
    return tmp;
  }

  constexpr void reset(type_pointer ptr = nullptr) noexcept { m_ptr = ptr; }

  constexpr void swap(observer_ptr& ptr) noexcept
  {
    std::swap(m_ptr, ptr.m_ptr);
  }

private:
  type_pointer m_ptr;
};

template<typename T>
void
swap(observer_ptr<T>& ptr1, observer_ptr<T>& ptr2) noexcept
{
  ptr1.swap(ptr2);
}

template<typename T>
observer_ptr<T>
make_observer(T* ptr) noexcept
{
  return observer_ptr<T>(ptr);
}

template<typename T, typename U>
bool
operator==(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return ptr1.get() == ptr2.get();
}

template<typename T, typename U>
bool
operator!=(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return !(ptr1 == ptr2);
}

template<typename T>
bool
operator==(observer_ptr<T> ptr, std::nullptr_t) noexcept
{
  return !ptr;
}

template<typename T>
bool
operator==(std::nullptr_t, observer_ptr<T> ptr) noexcept
{
  return !ptr;
}

template<typename T>
bool
operator!=(observer_ptr<T> ptr, std::nullptr_t) noexcept
{
  return bool(ptr);
}

template<typename T>
bool
operator!=(std::nullptr_t, observer_ptr<T> ptr) noexcept
{
  return bool(ptr);
}

template<typename T, typename U>
bool
operator<(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return std::less<
    typename std::common_type<typename std::add_pointer<T>::type,
                              typename std::add_pointer<U>::type>::type>{}(
    ptr1.get(), ptr2.get());
}

template<typename T, typename U>
bool
operator>(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return ptr2 < ptr1;
}

template<typename T, typename U>
bool
operator<=(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return !(ptr2 < ptr1);
}

template<typename T, typename U>
bool
operator>=(observer_ptr<T> ptr1, observer_ptr<U> ptr2)
{
  return !(ptr1 < ptr2);
}
}

template<typename T>
struct std::hash<SDL3pp::observer_ptr<T>>
{
  using result_type = std::size_t;
  using argument_type = SDL3pp::observer_ptr<T>;

  std::size_t operator()(const SDL3pp::observer_ptr<T>& m_ptr) const
  noexcept(noexcept(std::hash<typename std::add_pointer<T>::type> {}(m_ptr.get())))
  {
    return std::hash<typename std::add_pointer<T>::type>{}(m_ptr.get());
  }
};

#include <experimental/memory>

#endif