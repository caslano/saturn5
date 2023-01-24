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
9xaOxCkal6MLAvKSbXZwXvr1i7p56YX2fnkp04uX3vkiFF5ad00gXqp5E4FpQzDFLfC7VgQ4ftuhwrFh2Yl05CMos8qIfIkf5Gq+8EWuKXlBAWL3dQ1fHnoDDb9+WehEYO1uTSem+Pl6KbB5BprNrW36kZCy63qzOCdXMf9Ur0hy5iEZ38/9NxR8L24aCN8/viHNx7a9QfYfDdbJN/3af7M87D/BrwHo+tyfAQhjYhvDMJ+VTgTubI3If1SQgU3nNG30MgHf+Twk/DfxbwKefR0BaktwXfem9/4ALkvJjaN7S5TnXcTV5zCiroyRdRn6PxE48hVIQXX0y5S8mpZ66utoQSSBXI6Z18HijC72qJ5XsoCpkLEYpw26My66KsDVTLgKucr38qs5uMAEV5mg1q3kV+UC3sZiKRIPFgwtU0jEzougK5nOpyfRFZFfyXUunEhXCvAKzZ2cyybQxXFwkZdhh+NiJNtlxbIn3lpPgFzm5LWAVUaIskvDlNzh5HVf3I1XQ4f27ozAeCCjlldM536To0bVM83kZxyx93eRCo6ZP4+gPBIJFrEpOKwWIyp4E5A3dJPJ3T+Z4s/j+arQjM/0Gli92BRO/hbJcdJIgkXxtyxU31JcMRmOZSW4kkvAmhVgIW8OcPLT2DbfA74zTd4DbigeGY6AZDFg9Spg3d1Uz5jlZxyxt/WSgB0Ka9uXAOcbnxKcYVcC5/xA
*/