#pragma once

#include <functional>
#include <type_traits>
#include <utility>

namespace std {
namespace experimental {
inline namespace fundamentals_v2 {
template <class T>
class propagate_const {
 public:
  typedef remove_reference_t<decltype(*declval<T&>())> element_type;

 private:
  template <class U>
  static element_type* get_pointer(U* u) {
    return u;
  }

  template <class U>
  static element_type* get_pointer(U& u) {
    return get_pointer(u.get());
  }

  template <class U>
  static const element_type* get_pointer(const U* u) {
    return u;
  }

  template <class U>
  static const element_type* get_pointer(const U& u) {
    return get_pointer(u.get());
  }

  template <class U>
  struct is_propagate_const : false_type {};

  template <class U>
  struct is_propagate_const<propagate_const<U>> : true_type {};

 public:
  // [propagate_const.ctor], constructors
  propagate_const() = default;

  propagate_const(const propagate_const& p) = delete;

  propagate_const(propagate_const&& p) = default;

  template <class U, class = enable_if_t<is_constructible<T, U&&>::value>>
  explicit propagate_const(propagate_const<U>&& pu)
      : t_(std::move(pu.t_)) {}

  template <class U, class = enable_if_t<is_constructible<T, U&&>::value>>
  explicit propagate_const(U&& u) : t_(std::forward<U>(u)) {}

  // [propagate_const.assignment], assignment
  propagate_const& operator=(const propagate_const& p) = delete;

  propagate_const& operator=(propagate_const&& p) = default;

  template <class U>
  propagate_const& operator=(propagate_const<U>&& pu) {
    t_ = std::move(pu.t_);
    return *this;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  propagate_const& operator=(U&& u) {
    t_ = std::move(u);
    return *this;
  }

  // [propagate_const.const_observers], const observers
  explicit operator bool() const { return get() != nullptr; }
  const element_type* operator->() const { return get(); }

  template <class T_ = T, class = enable_if_t<is_convertible<
                              const T_, const element_type*>::value>>
  operator const element_type*() const  // Not always defined
  {
    return get();
  }

  const element_type& operator*() const { return *get(); }

  const element_type* get() const { return get_pointer(t_); }

  // [propagate_const.non_const_observers], non-const observers
  element_type* operator->() { return get(); }

  template <class T_ = T,
            class = enable_if_t<is_convertible<T_, element_type*>::value>>
  operator element_type*()  // Not always defined
  {
    return get();
  }

  element_type& operator*() { return *get(); }

  element_type* get() { return get_pointer(t_); }

  // [propagate_const.modifiers], modifiers
  void swap(propagate_const& pt) noexcept(
      noexcept(swap(declval<T&>(), declval<T&>()))) {
    swap(t_, pt.t_);
  }

 private:
  T t_;

  friend struct std::hash<propagate_const<T>>;
  friend struct std::equal_to<propagate_const<T>>;
  friend struct std::not_equal_to<propagate_const<T>>;
  friend struct std::greater<propagate_const<T>>;
  friend struct std::less<propagate_const<T>>;
  friend struct std::greater_equal<propagate_const<T>>;
  friend struct std::less_equal<propagate_const<T>>;

  // [propagate_const.relational], relational operators
  friend bool operator==(const propagate_const& pt, nullptr_t) {
    return pt.t_ == nullptr;
  }

  friend bool operator==(nullptr_t, const propagate_const& pu) {
    return nullptr == pu.t_;
  }

  friend bool operator!=(const propagate_const& pt, nullptr_t) {
    return pt.t_ != nullptr;
  }

  friend bool operator!=(nullptr_t, const propagate_const& pu) {
    return nullptr != pu.t_;
  }

  template <class U>
  friend bool operator==(const propagate_const& pt,
                                   const propagate_const<U>& pu) {
    return pt.t_ == pu.t_;
  }

  template <class U>
  friend bool operator!=(const propagate_const& pt,
                                   const propagate_const<U>& pu) {
    return pt.t_ != pu.t_;
  }

  template <class U>
  friend bool operator<(const propagate_const& pt,
                                  const propagate_const<U>& pu) {
    return pt.t_ < pu.t_;
  }

  template <class U>
  friend bool operator>(const propagate_const& pt,
                                  const propagate_const<U>& pu) {
    return pt.t_ > pu.t_;
  }

  template <class U>
  friend bool operator<=(const propagate_const& pt,
                                   const propagate_const<U>& pu) {
    return pt.t_ <= pu.t_;
  }

  template <class U>
  friend bool operator>=(const propagate_const& pt,
                                   const propagate_const<U>& pu) {
    return pt.t_ >= pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator==(const propagate_const& pt, const U& u) {
    return pt.t_ == u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator!=(const propagate_const& pt, const U& u) {
    return pt.t_ != u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator<(const propagate_const& pt, const U& u) {
    return pt.t_ < u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator>(const propagate_const& pt, const U& u) {
    return pt.t_ > u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator<=(const propagate_const& pt, const U& u) {
    return pt.t_ <= u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator>=(const propagate_const& pt, const U& u) {
    return pt.t_ >= u;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator==(const U& u, const propagate_const& pu) {
    return u == pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator!=(const U& u, const propagate_const& pu) {
    return u != pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator<(const U& u, const propagate_const& pu) {
    return u < pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator>(const U& u, const propagate_const& pu) {
    return u > pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator<=(const U& u, const propagate_const& pu) {
    return u <= pu.t_;
  }

  template <class U,
            class = enable_if_t<!is_propagate_const<decay_t<U>>::value>>
  friend bool operator>=(const U& u, const propagate_const& pu) {
    return u >= pu.t_;
  }
};


// [propagate_const.algorithms], specialized algorithms
template <class T>
void swap(propagate_const<T>& pt, propagate_const<T>& pu) noexcept(
    noexcept(swap(declval<T&>(), declval<T&>()))) {
  swap(get_underlying(pt), get_underlying(pu));
}

}  //  end namespace fundamentals_v2
}  //  end namespace experimental

// [propagate_const.hash], hash support
template <class T>
struct hash<experimental::fundamentals_v2::propagate_const<T>> {
  typedef size_t result_type;
  typedef experimental::fundamentals_v2::propagate_const<T> argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc) const {
    return std::hash<T>()(pc.t_);
  }
};

// [propagate_const.comparison_function_objects], comparison function objects
template <class T>
struct equal_to<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::equal_to<T>()(pc1.t_, pc2.t_);
  }
};

template <class T>
struct not_equal_to<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::not_equal_to<T>()(pc1.t_, pc2.t_);
  }
};

template <class T>
struct less<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::less<T>()(pc1.t_, pc2.t_);
  }
};

template <class T>
struct greater<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::greater<T>()(pc1.t_, pc2.t_);
  }
};

template <class T>
struct less_equal<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::less_equal<T>()(pc1.t_, pc2.t_);
  }
};

template <class T>
struct greater_equal<experimental::fundamentals_v2::propagate_const<T>> {
  typedef experimental::fundamentals_v2::propagate_const<T> first_argument_type;
  typedef experimental::fundamentals_v2::propagate_const<T>
      second_argument_type;

  bool operator()(
      const experimental::fundamentals_v2::propagate_const<T>& pc1,
      const experimental::fundamentals_v2::propagate_const<T>& pc2) const {
    return std::greater_equal<T>()(pc1.t_, pc2.t_);
  }
};

}  // end namespace std
