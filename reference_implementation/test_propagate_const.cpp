#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "propagate_const.hpp"

using std::experimental::propagate_const;

enum { CONST_METHOD, NON_CONST_METHOD };

struct A 
{
  auto method() const { return CONST_METHOD; }  
  auto method() { return NON_CONST_METHOD; }  
};

#define REQUIRE_RETURN_TYPE_MATCH(expr,type) \
  static_assert((std::is_same<decltype(expr), type>::value), #expr"->"#type); 

//
// plain pointer
//
TEST_CASE("Plain pointer operator ->", "[ptr->]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const Plain pointer operator ->", "[cptr->]")
{
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("Plain pointer get", "[ptr.get]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const Plain pointer get", "[cptr.get]")
{
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("Plain pointer operator *", "[ptr_op_*]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const Plain pointer operator *", "[cptr_op_*]")
{
  A a;
  const propagate_const<A*> cpc_a(&a);
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}


//
// unique_ptr
//
TEST_CASE("unique_ptr operator ->", "[uptr->]")
{
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const unique_ptr operator ->", "[cuptr->]")
{
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("unique_ptr get", "[uptr.get]")
{
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const unique_ptr get", "[cuptr.get]")
{
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("unique_ptr operator *", "[uptr_op_*]")
{
  propagate_const<std::unique_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const unique_ptr operator *", "[cuptr_op_*]")
{
  const propagate_const<std::unique_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

//
// shared_ptr
//
TEST_CASE("shared_ptr operator ->", "[sptr->]")
{
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.operator->(), A*);
}

TEST_CASE("const shared_ptr operator ->", "[csptr->]")
{
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.operator->(), const A*);
}

TEST_CASE("shared_ptr get", "[sptr.get]")
{
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const shared_ptr get", "[csptr.get]")
{
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

TEST_CASE("shared_ptr operator *", "[sptr_op_*]")
{
  propagate_const<std::shared_ptr<A>> pc_a(std::make_unique<A>());
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(pc_a.get(), A*);
}

TEST_CASE("const shared_ptr operator *", "[csptr_op_*]")
{
  const propagate_const<std::shared_ptr<A>> cpc_a(std::make_unique<A>());
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  REQUIRE_RETURN_TYPE_MATCH(cpc_a.get(), const A*);
}

