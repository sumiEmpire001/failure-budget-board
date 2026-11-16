#include "core.hpp"
#include <cassert>
int main(){
 using namespace embedded_budget;
 Budget b(4,1);
 assert(b.snapshot().state==Healthy);
 assert(b.record(false));
 assert(b.snapshot().state==Warning);
 assert(b.record(false));
 assert(b.snapshot().state==Exhausted);
 assert(b.record(true));assert(b.record(true));
 assert(!b.record(true));
 assert(b.snapshot().state==Fault);
 b.reset();assert(b.snapshot().state==Healthy);
 Budget bad(1,2);
 assert(bad.snapshot().state==Fault);
 assert(!bad.record(true));
}