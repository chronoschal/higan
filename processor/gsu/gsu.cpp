#include <processor/processor.hpp>
#include "gsu.hpp"

namespace Processor {

#include "instructions.cpp"
#include "table.cpp"
#include "serialization.cpp"

//note: multiplication results *may* sometimes be invalid when both CLSR and MS0 are set
//the product of multiplication in this mode (21mhz + fast-multiply) has not been analyzed;
//however, the timing of this mode has been confirmed to work as specified below
auto GSU::cache_access_speed() -> unsigned {
  if(clockmode == 1) return 2;
  if(clockmode == 2) return 1;
  return regs.clsr ? 1 : 2;
}

auto GSU::memory_access_speed() -> unsigned {
  if(clockmode == 1) return 6;
  if(clockmode == 2) return 5;
  return regs.clsr ? 5 : 6;
}

auto GSU::power() -> void {
}

auto GSU::reset() -> void {
  for(auto& r : regs.r) r = 0x0000;
  regs.sfr      = 0x0000;
  regs.pbr      = 0x00;
  regs.rombr    = 0x00;
  regs.rambr    = 0;
  regs.cbr      = 0x0000;
  regs.scbr     = 0x00;
  regs.scmr     = 0x00;
  regs.colr     = 0x00;
  regs.por      = 0x00;
  regs.bramr    = 0;
  regs.vcr      = 0x04;
  regs.cfgr     = 0x00;
  regs.clsr     = 0;
  regs.pipeline = 0x01;  //nop
  regs.ramaddr  = 0x0000;
  regs.reset();
}

}
