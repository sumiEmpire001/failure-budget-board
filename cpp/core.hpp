#pragma once
#include <stdint.h>
namespace embedded_budget {
enum State { Healthy, Warning, Exhausted, Fault };
struct Snapshot { State state; uint32_t failures; uint32_t total; uint32_t allowance; };
class Budget {
 uint32_t total_=0,fail_=0;uint32_t window_,allowed_;bool fault_=false;
public:
 Budget(uint32_t window,uint32_t allowed):window_(window),allowed_(allowed){if(!window||allowed>window)fault_=true;}
 bool record(bool success){
  if(fault_||total_>=window_){fault_=true;return false;}
  ++total_;if(!success)++fail_;return true;
 }
 void reset(){total_=0;fail_=0;fault_=!window_||allowed_>window_;}
 Snapshot snapshot()const{
  State state=fault_?Fault:fail_>allowed_?Exhausted:allowed_>0&&fail_==allowed_?Warning:Healthy;
  return {state,fail_,total_,allowed_};
 }
};
}