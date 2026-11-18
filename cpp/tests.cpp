#include "core.hpp"
#include <cassert>
int main(){using namespace embedded_budget;
 Budget b(3,1);assert(b.snapshot().state==Healthy);
 assert(b.record(false));assert(b.snapshot().state==Warning);
 assert(b.record(false));assert(b.snapshot().state==Exhausted);
 assert(b.record(true));assert(!b.record(true));assert(b.snapshot().state==Fault);
 b.reset();assert(b.snapshot().state==Healthy);
 Budget bad(0,0);assert(!bad.record(true));assert(bad.snapshot().state==Fault);
}