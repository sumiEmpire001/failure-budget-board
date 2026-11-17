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
 // A completed window must fail closed until a deliberate reset.
 Budget exact(2,0);
 assert(exact.record(true));assert(exact.record(true));
 assert(exact.snapshot().state==Healthy);
 assert(!exact.record(true));assert(exact.snapshot().state==Fault);
 assert(!exact.record(false));assert(exact.snapshot().failures==0);
 exact.reset();assert(exact.record(false));assert(exact.snapshot().state==Exhausted);
 Budget bad(1,2);
 assert(bad.snapshot().state==Fault);
 assert(!bad.record(true));
}