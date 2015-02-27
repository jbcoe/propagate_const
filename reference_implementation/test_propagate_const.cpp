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

TEST_CASE("Plain pointer operator ->", "[ptr->]")
{
  A a;
  propagate_const<A*> pc_a(&a);
  REQUIRE(pc_a->method() == NON_CONST_METHOD);
  
  const propagate_const<A*> cpc_a(&a);
  REQUIRE(cpc_a->method() == CONST_METHOD);
}

