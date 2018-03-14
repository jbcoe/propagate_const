#pragma once

#include <type_traits>
#include <utility>
#include <functional>

namespace std
{
namespace experimental
{
inline namespace fundamentals_v2
{

template <class T>
class propagate_const
{

public:
  typedef remove_reference_t<decltype(*declval<T&>())> element_type;

private:
  template <class U>
  static element_type* get_pointer(U* u)
  {
    return u;
  }

  template <class U>
  static element_type* get_pointer(U& u)
  {
    return get_pointer(u.get());
  }

  template <class U>
  static const element_type* get_pointer(const U* u)
  {
    return u;
  }

  template <class U>
  static const element_type* get_pointer(const U& u)
  {
    return get_pointer(u.get());
  }
  
  template <class U>
  struct is_propagate_const : false_type
  {
  };

  template <class U>
  struct is_propagate_const<propagate_const<U>> : true_type
  {
  };

public:
  // [propagate_const.ctor], constructors
  constexpr propagate_const() = default;

  propagate_const(const propagate_const& p) = delete;

  constexpr propagate_const(propagate_const&& p) = default;

  template <class U, enable_if_t<!is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value,bool> = true>
  explicit constexpr propagate_const(propagate_const<U>&& pu)
      : t_(std::move(get_underlying(pu)))
  {
  }

  template <class U, enable_if_t<is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value,bool> = false>
  constexpr propagate_const(propagate_const<U>&& pu)
      : t_(std::move(get_underlying(pu)))
  {
  }

  template <class U, enable_if_t<!is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value &&
                                 !is_propagate_const<decay_t<U>>::value,bool> = true>
  explicit constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }

  template <class U, enable_if_t<is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value &&
                                 !is_propagate_const<decay_t<U>>::value,bool> = false>
  constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }
  
  // [propagate_const.assignment], assignment
  propagate_const& operator=(const propagate_const& p) = delete;

  constexpr propagate_const& operator=(propagate_const&& p) = default;

  template <class U>
  constexpr propagate_const& operator=(propagate_const<U>&& pu)
  {
    t_ = std::move(pu.t_);
    return *this;
  }

  template <class U, class V = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  constexpr propagate_const& operator=(U&& u)
  {
    t_ = std::move(u);
    return *this;
  }

  // [propagate_const.const_observers], const observers
  explicit constexpr operator bool() const
  {
    return get() != nullptr;
  }
  constexpr const element_type* operator->() const
  {
    return get();
  }

  template<class T_=T, class U=enable_if_t<is_convertible<const T_, const element_type*>::value>>
  constexpr operator const element_type*() const // Not always defined
  {
    return get();
  }

  constexpr const element_type& operator*() const
  {
    return *get();
  }

  constexpr const element_type* get() const
  {
    return get_pointer(t_);
  }

  // [propagate_const.non_const_observers], non-const observers
  constexpr element_type* operator->()
  {
    return get();
  }

  template<class T_=T, class U=enable_if_t<is_convertible<T_, element_type*>::value>>
  constexpr operator element_type*() // Not always defined
  {
    return get();
  }

  constexpr element_type& operator*()
  {
    return *get();
  }
  
  constexpr element_type* get()
  {
    return get_pointer(t_);
  }

  // [propagate_const.modifiers], modifiers
  constexpr void swap(propagate_const& pt) noexcept(noexcept(swap(declval<T&>(),declval<T&>())))
  {
    swap(t_, pt.t_);
  }

private:
  T t_;

friend constexpr const T& get_underlying(const propagate_const<T>& pt) noexcept { return pt.t_; }
friend constexpr T& get_underlying(propagate_const<T>& pt) noexcept { return pt.t_; }

};

// [propagate_const.underlying], underlying pointer access
// defined inline in the class

// [propagate_const.relational], relational operators
template <class T>
constexpr bool operator==(const propagate_const<T>& pt, nullptr_t)
{
  return get_underlying(pt) == nullptr;
}

template <class T>
constexpr bool operator==(nullptr_t, const propagate_const<T>& pu)
{
  return nullptr == get_underlying(pu);
}

template <class T>
constexpr bool operator!=(const propagate_const<T>& pt, nullptr_t)
{
  return get_underlying(pt) != nullptr;
}

template <class T>
constexpr bool operator!=(nullptr_t, const propagate_const<T>& pu)
{
  return nullptr != get_underlying(pu);
}

template <class T, class U>
constexpr bool operator==(const propagate_const<T>& pt,
                          const propagate_const<U>& pu)
{
  return get_underlying(pt) == get_underlying(pu);
}

template <class T, class U>
constexpr bool operator!=(const propagate_const<T>& pt,
                          const propagate_const<U>& pu)
{
  return get_underlying(pt) != get_underlying(pu);
}

template <class T, class U>
constexpr bool operator<(const propagate_const<T>& pt,
                         const propagate_const<U>& pu)
{
  return get_underlying(pt) < get_underlying(pu);
}

template <class T, class U>
constexpr bool operator>(const propagate_const<T>& pt,
                         const propagate_const<U>& pu)
{
  return get_underlying(pt) > get_underlying(pu);
}

template <class T, class U>
constexpr bool operator<=(const propagate_const<T>& pt,
                          const propagate_const<U>& pu)
{
  return get_underlying(pt) <= get_underlying(pu);
}

template <class T, class U>
constexpr bool operator>=(const propagate_const<T>& pt,
                          const propagate_const<U>& pu)
{
  return get_underlying(pt) >= get_underlying(pu);
}

template <class T, class U>
constexpr bool operator==(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) == u;
}

template <class T, class U>
constexpr bool operator!=(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) != u;
}

template <class T, class U>
constexpr bool operator<(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) < u;
}

template <class T, class U>
constexpr bool operator>(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) > u;
}

template <class T, class U>
constexpr bool operator<=(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) <= u;
}

template <class T, class U>
constexpr bool operator>=(const propagate_const<T>& pt, const U& u)
{
  return get_underlying(pt) >= u;
}


template <class T, class U>
constexpr bool operator==(const T& t, const propagate_const<U>& pu)
{
  return t == get_underlying(pu);
}

template <class T, class U>
constexpr bool operator!=(const T& t, const propagate_const<U>& pu)
{
  return t != get_underlying(pu);
}

template <class T, class U>
constexpr bool operator<(const T& t, const propagate_const<U>& pu)
{
  return t < get_underlying(pu);
}

template <class T, class U>
constexpr bool operator>(const T& t, const propagate_const<U>& pu)
{
  return t > get_underlying(pu);
}

template <class T, class U>
constexpr bool operator<=(const T& t, const propagate_const<U>& pu)
{
  return t <= get_underlying(pu);
}

template <class T, class U>
constexpr bool operator>=(const T& t, const propagate_const<U>& pu)
{
  return t >= get_underlying(pu);
}


// [propagate_const.algorithms], specialized algorithms
template <class T>
constexpr void swap(propagate_const<T>& pt, propagate_const<T>& pu) noexcept(
    noexcept(swap(declval<T&>(), declval<T&>())))
{
  swap(get_underlying(pt), get_underlying(pu));
}


} //  end namespace fundamentals_v2
} //  end namespace experimental


// [propagate_const.hash], hash support
template <class T>
struct hash<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef size_t result_type;
  typedef experimental::fundamentals_v2::propagate_const<T> argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1) const
  {
    return std::hash<T>()(get_underlying(pc1));
  }
};

// [propagate_const.comparison_function_objects], comparison function objects
template <class T>
struct equal_to<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::equal_to<T>()(get_underlying(pc1), get_underlying(pc2));
  }
};

template <class T>
struct not_equal_to<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::not_equal_to<T>()(get_underlying(pc1), get_underlying(pc2));
  }
};

template <class T>
struct less<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::less<T>()(get_underlying(pc1), get_underlying(pc2)); 
  }
};

template <class T>
struct greater<experimental::fundamentals_v2::propagate_const<T>> 
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::greater<T>()(get_underlying(pc1), get_underlying(pc2));
  }
};

template <class T>
struct less_equal<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::less_equal<T>()(get_underlying(pc1), get_underlying(pc2));
  }
};

template <class T>
struct greater_equal<experimental::fundamentals_v2::propagate_const<T>>
{
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T> second_argument_type;

  bool operator()(const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const
  {
    return std::greater_equal<T>()(get_underlying(pc1), get_underlying(pc2));
  }
};

} // end namespace std

