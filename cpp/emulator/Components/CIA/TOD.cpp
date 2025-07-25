// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the Mozilla Public License v2
//
// See https://mozilla.org/MPL/2.0 for license information
// -----------------------------------------------------------------------------

#include "config.h"
#include "TOD.h"
#include "CIA.h"
#include "IOUtils.h"

namespace vamiga {

TOD::TOD(CIA &ciaref, Amiga& ref) : SubComponent(ref), cia(ciaref)
{

}

void
TOD::operator << (SerResetter &worker)
{
    serialize(worker);

    if (worker.isHard()) {

        stopped = true;
        matching = true;
        tod.hi = 0x1;
    }
}

void
TOD::cacheInfo(TODInfo &info) const
{
    {   SYNCHRONIZED
        
        info.value = tod.value;
        info.latch = latch.value;
        info.alarm = alarm.value;
    }
}

void 
TOD::_dump(Category category, std::ostream &os) const
{
    using namespace util;
    
    if (category == Category::State) {
        
        os << tab("Counter");
        os << hex(tod.hi) << ":" << hex(tod.mid) << ":" << hex(tod.lo) << std::endl;
        os << tab("Alarm");
        os << hex(alarm.hi) << ":" << hex(alarm.mid) << ":" << hex(alarm.lo) << std::endl;
        os << tab("Latch");
        os << hex(latch.hi) << ":" << hex(latch.mid) << ":" << hex(latch.lo) << std::endl;
        os << tab("Frozen");
        os << bol(frozen) << std::endl;
        os << tab("Stopped");
        os << bol(stopped) << std::endl;
    }
}

u8
TOD::getCounterHi(Cycle timeStamp) const
{
    u8 result = frozen ? latch.hi : timeStamp > lastInc ? tod.hi : preTod.hi;

    trace(TOD_DEBUG, "getCounterHi: %02x\n", result);
    return result;
}

u8
TOD::getCounterMid(Cycle timeStamp) const
{
    u8 result = frozen ? latch.mid : timeStamp > lastInc ? tod.mid : preTod.mid;
    
    trace(TOD_DEBUG, "getCounterMid: %02x\n", result);
    return result;
}

u8
TOD::getCounterLo(Cycle timeStamp) const
{
    u8 result = frozen ? latch.lo : timeStamp > lastInc ? tod.lo : preTod.lo;
    
    trace(TOD_DEBUG, "getCounterLo: %02x\n", result);
    return result;
}

u8
TOD::getAlarmHi() const
{
    trace(TOD_DEBUG, "getAlarmHi: %02x\n", alarm.hi);
    return alarm.hi;
}

u8
TOD::getAlarmMid() const
{
    trace(TOD_DEBUG, "getAlarmMid: %02x\n", alarm.mid);
    return alarm.mid;
}

u8
TOD::getAlarmLo() const
{
    trace(TOD_DEBUG, "getAlarmLo: %02x\n", alarm.lo);
    return alarm.lo;
}

void
TOD::setCounterHi(u8 value)
{
    trace(TOD_DEBUG, "setCounterHi(%x)\n", value);
    tod.hi = value;
    
    checkIrq();
}

void
TOD::setCounterMid(u8 value)
{
    trace(TOD_DEBUG, "setCounterMid(%x)\n", value);
    tod.mid = value;
    
    checkIrq();
}

void
TOD::setCounterLo(u8 value)
{
    trace(TOD_DEBUG, "setCounterLo(%x)\n", value);
    tod.lo = value;
    
    checkIrq();
}

void
TOD::setAlarmHi(u8 value)
{
    trace(TOD_DEBUG, "setAlarmHi(%x)\n", value);
    alarm.hi = value;
    
    checkIrq();
}

void
TOD::setAlarmMid(u8 value)
{
    trace(TOD_DEBUG, "setAlarmMid(%x)\n", value);
    alarm.mid = value;
    
    checkIrq();
}

void
TOD::setAlarmLo(u8 value)
{
    trace(TOD_DEBUG, "setAlarmLo(%x)\n", value);
    alarm.lo = value;
    
    checkIrq();
}

void
TOD::increment()
{
    if (stopped) return;

    preTod = tod;
    lastInc = cia.clock;

    if (!incLoNibble(tod.lo))  goto check;
    if (!incHiNibble(tod.lo))  goto check;
    if (!incLoNibble(tod.mid)) goto check;

    if (tod.value == alarm.value) {
        trace(TOD_DEBUG, "TOD bug hits: %x:%x:%x (%d,%d)\n",
              tod.hi, tod.mid, tod.lo, frozen, stopped);
    }
    if (cia.config.todBug) checkIrq();

    if (!incHiNibble(tod.mid)) goto check;
    if (!incLoNibble(tod.hi))  goto check;
    incHiNibble(tod.hi);

check:
    checkIrq();
}

bool
TOD::incLoNibble(u8 &counter)
{
    if ((counter & 0x0F) < 0x0F) {
        counter += 0x01; return false;
    } else {
        counter &= 0xF0; return true;
    }
}

bool
TOD::incHiNibble(u8 &counter)
{
    if ((counter & 0xF0) < 0xF0) {
        counter += 0x10; return false;
    } else {
        counter &= 0x0F; return true;
    }
}

void
TOD::checkIrq()
{
    if (!matching && tod.value == alarm.value) {
        
        trace(TOD_DEBUG, "TOD IRQ (%02x:%02x:%02x)\n", tod.hi, tod.mid, tod.lo);
        cia.todInterrupt();
    }
    matching = (tod.value == alarm.value);
}

}
