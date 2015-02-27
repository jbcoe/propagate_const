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

#define EXPRESSION_RETURN_TYPE(expr,type) static_assert((std::is_same<decltype(expr), type>::value), #expr"->"#type); 

TEST_CASE("Plain pointer operator ->", "[ptr->]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  EXPRESSION_RETURN_TYPE(pc_a.operator->(), A*);
  
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a->method() == CONST_METHOD);
  EXPRESSION_RETURN_TYPE(cpc_a.operator->(), const A*);
}

TEST_CASE("Plain pointer get", "[ptr.get]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a.get()->method() == NON_CONST_METHOD);
  EXPRESSION_RETURN_TYPE(pc_a.get(), A*);
  
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a.get()->method() == CONST_METHOD);
  EXPRESSION_RETURN_TYPE(cpc_a.get(), const A*);
}

TEST_CASE("Plain pointer operator *", "[ptr_op_*]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE((*pc_a).method() == NON_CONST_METHOD);
  EXPRESSION_RETURN_TYPE(pc_a.get(), A*);
  
  const propagate_const<A*> cpc_a(&a);
  REQUIRE((*cpc_a).method() == CONST_METHOD);
  EXPRESSION_RETURN_TYPE(cpc_a.get(), const A*);
}
