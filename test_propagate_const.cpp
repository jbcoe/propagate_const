#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "propagate_const.h"

using std::experimental::propagate_const;

enum { CONST_METHOD, NON_CONST_METHOD };

struct A {
  auto method() const { return CONST_METHOD; }
  auto method() { return NON_CONST_METHOD; }
};

#define REQUIRE_RETURN_TYPE_MATCH(expr, type)                          \
  static_assert((std::is_same<decltype(expr), type>::value), #expr "-" \
                                                                   ">" #type);

//
// plain pointer
//
TEST_CASE("Plain pointer operator ->", "[ptr->]") {
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const Plain pointer operator ->", "[cptr->]") {
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("Plain pointer get", "[ptr.get]") {
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const Plain pointer get", "[cptr.get]") {
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("Plain pointer operator *", "[ptr_op_*]") {
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const Plain pointer operator *", "[cptr_op_*]") {
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

//
// unique_ptr
//
TEST_CASE("unique_ptr operator ->", "[uptr->]") {
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const unique_ptr operator ->", "[cuptr->]") {
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("unique_ptr get", "[uptr.get]") {
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const unique_ptr get", "[cuptr.get]") {
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("unique_ptr operator *", "[uptr_op_*]") {
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const unique_ptr operator *", "[cuptr_op_*]") {
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

//
// shared_ptr
//
TEST_CASE("shared_ptr operator ->", "[sptr->]") {
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const shared_ptr operator ->", "[csptr->]") {
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("shared_ptr get", "[sptr.get]") {
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const shared_ptr get", "[csptr.get]") {
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("shared_ptr operator *", "[sptr_op_*]") {
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const shared_ptr operator *", "[csptr_op_*]") {
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

size_t a_hash_calls = 0;

namespace std {
template <>
struct hash<A*> {
  size_t operator()(const A*) const {
    ++a_hash_calls;
    return 0;
  }
};
} // namespace std

TEST_CASE("hash", "[hash]") {
  A a;
  propagate_const<A*> pa(&a);
  a_hash_calls = 0;
  std::hash<propagate_const<A*>>()(pa);
  REQUIRE(a_hash_calls == 1);
}

size_t a_equal_to_calls = 0;
namespace std {
template <>
struct equal_to<A*> {
  bool operator()(const A*, const A*) const {
    ++a_equal_to_calls;
    return false;
  }
};
} // namespace std

TEST_CASE("equal_to", "[equal_to]") {
  A a;
  propagate_const<A*> pa(&a);
  a_equal_to_calls = 0;
  std::equal_to<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_equal_to_calls == 1);
}

size_t a_not_equal_to_calls = 0;
namespace std {
template <>
struct not_equal_to<A*> {
  bool operator()(const A*, const A*) const {
    ++a_not_equal_to_calls;
    return false;
  }
};
} // namespace std
TEST_CASE("not_equal_to", "[not_equal_to]") {
  A a;
  propagate_const<A*> pa(&a);
  a_not_equal_to_calls = 0;
  std::not_equal_to<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_not_equal_to_calls == 1);
}

size_t a_greater_calls = 0;
namespace std {
template <>
struct greater<A*> {
  bool operator()(const A*, const A*) const {
    ++a_greater_calls;
    return false;
  }
};
} // namespace std
TEST_CASE("greater", "[greater]") {
  A a;
  propagate_const<A*> pa(&a);
  a_greater_calls = 0;
  std::greater<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_greater_calls == 1);
}

size_t a_less_calls = 0;
namespace std {
template <>
struct less<A*> {
  bool operator()(const A*, const A*) const {
    ++a_less_calls;
    return false;
  }
};
} // namespace std
TEST_CASE("less", "[less]") {
  A a;
  propagate_const<A*> pa(&a);
  a_less_calls = 0;
  std::less<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_less_calls == 1);
}

size_t a_greater_equal_calls = 0;
namespace std {
template <>
struct greater_equal<A*> {
  bool operator()(const A*, const A*) const {
    ++a_greater_equal_calls;
    return false;
  }
};
} // namespace std
TEST_CASE("greater_equal", "[greater_equal]") {
  A a;
  propagate_const<A*> pa(&a);
  a_greater_equal_calls = 0;
  std::greater_equal<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_greater_equal_calls == 1);
}

size_t a_less_equal_calls = 0;
namespace std {
template <>
struct less_equal<A*> {
  bool operator()(const A*, const A*) const {
    ++a_less_equal_calls;
    return false;
  }
};
} // namespace std
TEST_CASE("less_equal", "[less_equal]") {
  A a;
  propagate_const<A*> pa(&a);
  a_less_equal_calls = 0;
  std::less_equal<propagate_const<A*>>()(pa, pa);
  REQUIRE(a_less_equal_calls == 1);
}

class FakePtr {
 public:
  auto operator-> () const { return this; }
  auto get() const { return this; }
  auto operator*() const { return *this; }
};

size_t fPtr_equals_fPtr_calls = 0;
bool operator==(const FakePtr& f, const FakePtr& g) {
  ++fPtr_equals_fPtr_calls;
  return false;
}
TEST_CASE("equals function", "[free ==]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_equals_fPtr_calls = 0;
  auto r = (f == g);
  REQUIRE(fPtr_equals_fPtr_calls == 1);
}

size_t fPtr_not_equals_fPtr_calls = 0;
bool operator!=(const FakePtr& f, const FakePtr& g) {
  ++fPtr_not_equals_fPtr_calls;
  return false;
}
TEST_CASE("not equals function", "[free !=]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_not_equals_fPtr_calls = 0;
  auto r = (f != g);
  REQUIRE(fPtr_not_equals_fPtr_calls == 1);
}

size_t fPtr_less_fPtr_calls = 0;
bool operator<(const FakePtr& f, const FakePtr& g) {
  ++fPtr_less_fPtr_calls;
  return false;
}
TEST_CASE("less function", "[free <]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_less_fPtr_calls = 0;
  auto r = (f < g);
  REQUIRE(fPtr_less_fPtr_calls == 1);
}

size_t fPtr_greater_fPtr_calls = 0;
bool operator>(const FakePtr& f, const FakePtr& g) {
  ++fPtr_greater_fPtr_calls;
  return false;
}
TEST_CASE("greater function", "[free >]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_greater_fPtr_calls = 0;
  auto r = (f > g);
  REQUIRE(fPtr_greater_fPtr_calls == 1);
}

size_t fPtr_less_or_equal_fPtr_calls = 0;
bool operator<=(const FakePtr& f, const FakePtr& g) {
  ++fPtr_less_or_equal_fPtr_calls;
  return false;
}
TEST_CASE("less or equal function", "[free <=]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_less_or_equal_fPtr_calls = 0;
  auto r = (f <= g);
  REQUIRE(fPtr_less_or_equal_fPtr_calls == 1);
}

size_t fPtr_greater_or_equal_fPtr_calls = 0;
bool operator>=(const FakePtr& f, const FakePtr& g) {
  ++fPtr_greater_or_equal_fPtr_calls;
  return false;
}
TEST_CASE("greater or equal function", "[free >=]") {
  propagate_const<FakePtr> f;
  propagate_const<FakePtr> g;
  fPtr_greater_or_equal_fPtr_calls = 0;
  auto r = (f >= g);
  REQUIRE(fPtr_greater_or_equal_fPtr_calls == 1);
}
