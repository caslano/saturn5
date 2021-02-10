// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_TYPES_H
#define BOOST_MSM_COMMON_TYPES_H

#include <boost/tuple/tuple.hpp>
#include <boost/msm/common.hpp>

namespace boost { namespace msm { namespace back
{
// used for disable_if
template <int> struct dummy { dummy(int) {} };
// return value for transition handling
typedef enum
{
    HANDLED_FALSE=0,
    HANDLED_TRUE =1,
    HANDLED_GUARD_REJECT=2,
    HANDLED_DEFERRED=4
} HandledEnum;

typedef HandledEnum execute_return;

// source of event provided to RTC algorithm
enum EventSourceEnum
{
    EVENT_SOURCE_DEFAULT=0,
    EVENT_SOURCE_DIRECT=1,
    EVENT_SOURCE_DEFERRED=2,
    EVENT_SOURCE_MSG_QUEUE=4
};

typedef unsigned char EventSource;

}}}

#endif //BOOST_MSM_COMMON_TYPES_H


/* common_types.hpp
ZWFT1dRxrpfbfbDaTa8rwd3WD5yJcW7b1Wlb8lyDRB7nlaVP+MbSPMFbk+OdcZImVpiFKPvbBRTG8FQhl6jBDsA2VVzETdh2qe7fAWV8KiFkmgE7aZRg7EJ1iyFiCo6IGQxUJPSA0Neaa1LkUmjBReKSxXK9BVO21b9XFrlpkXrmJv5ryBbZeKs1PPrbzZT+a8K1iD/bBRBsp/S/TTCEuRd4FvnyvAqqLncl0SJPBAt7U7itKO84dS5GnO65/gFQSwMECgAAAAgALWdKUpcFFCO/AgAAKAUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5MzZVVAUAAbZIJGCVVE1T2zAQvWsm/2EbhgvTxJRAZ8gITw0JkBkncR0T2l4YRd5gN7blkWQg/fWV7HxA4VIfHGn99u3bt1KoRqU5U+gSmhZLYX5WuH4WMlYumY2jgMy8mV+/wLuLbmES+eNX28D3RpNmP5jeT25CbzAk4fXV6fnZKaHOnos6DT05IAcwQ/mEsqPSGAmVWGZrA1B1kOexS3aVNvzhMPB/QnsXbkOvd9oAVFWWQmqMN6AoC8fRfBLded6lZ55LMRp5Hz8XNUtYLRapSjbpR3B2/KVpDV94wopHBM4KjlmGMSzWwLMUC/1GUa2x
*/