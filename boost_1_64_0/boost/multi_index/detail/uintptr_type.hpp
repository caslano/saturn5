/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_UINTPTR_TYPE_HPP
#define BOOST_MULTI_INDEX_DETAIL_UINTPTR_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* has_uintptr_type is an MPL integral constant determining whether
 * there exists an unsigned integral type with the same size as
 * void *.
 * uintptr_type is such a type if has_uintptr is true, or unsigned int
 * otherwise.
 * Note that uintptr_type is more restrictive than C99 uintptr_t,
 * where an integral type with size greater than that of void *
 * would be conformant.
 */

template<int N>struct uintptr_candidates;
template<>struct uintptr_candidates<-1>{typedef unsigned int           type;};
template<>struct uintptr_candidates<0> {typedef unsigned int           type;};
template<>struct uintptr_candidates<1> {typedef unsigned short         type;};
template<>struct uintptr_candidates<2> {typedef unsigned long          type;};

#if defined(BOOST_HAS_LONG_LONG)
template<>struct uintptr_candidates<3> {typedef boost::ulong_long_type type;};
#else
template<>struct uintptr_candidates<3> {typedef unsigned int           type;};
#endif

#if defined(BOOST_HAS_MS_INT64)
template<>struct uintptr_candidates<4> {typedef unsigned __int64       type;};
#else
template<>struct uintptr_candidates<4> {typedef unsigned int           type;};
#endif

struct uintptr_aux
{
  BOOST_STATIC_CONSTANT(int,index=
    sizeof(void*)==sizeof(uintptr_candidates<0>::type)?0:
    sizeof(void*)==sizeof(uintptr_candidates<1>::type)?1:
    sizeof(void*)==sizeof(uintptr_candidates<2>::type)?2:
    sizeof(void*)==sizeof(uintptr_candidates<3>::type)?3:
    sizeof(void*)==sizeof(uintptr_candidates<4>::type)?4:-1);

  BOOST_STATIC_CONSTANT(bool,has_uintptr_type=(index>=0));

  typedef uintptr_candidates<index>::type type;
};

typedef mpl::bool_<uintptr_aux::has_uintptr_type> has_uintptr_type;
typedef uintptr_aux::type                         uintptr_type;

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* uintptr_type.hpp
RWIdDM3gFIEwwzeqyDLBDN/IyaAbE7o9ruPIUsMM36Ak84MZjn8m5hvgvrygAPflhQa4zzPcxKJNyosxSRdnYi6TPBNM0omM7i2IrJe0LUnPPktbL6AuZCesyjraBuPYERXoFJuZbWvdWb13kZPqaVH2psJ/BPLMRWNeU7Y84bFAu+SR9ZSmaxeyIGmb6Q818uy6h9jJMjB79r7aZcSe1ylqMEs490C9l0fmDdPvLxWlM/33YaN1pt8nKiavvp5X/bvVwdwkC2Nmr1QtGnMzH609FmU+07eofcELOsVSTdnBErtCMa4LO8Uoi7Ldfy9D/4UWddKjXmXHggOa4Vhc0inuCmUlX96sot6XcopIZmJM/RKoS2mnyKcpa/j5V3XvvoxThAhlh7MeXIfYyVYxS7/Opw/WgrLyeCRtX8FXdrRneacYK5RZt44bgPgqOMUlZhFP4k4ivlCnqMrsp/9f2zCWyJoxm/X9U1GM3d+cYpJVmfOcB8qLreJMPoeW9nl4ORfGUlV5vJV2b8C2QijPxEQ1Wj9Z7P9knoN+j6ruTL4WlbZ6cpqlaE+yJcyO+n5ciDar4RTrWJ7N3v+1H3WpRfHxvi2ddzvK+90p1jLLFnFrPdrzj+Q1UppujYwi84Pp522MSbo4k3QuMi+YYa0zyVPUdp9nkImF1nZfXlhtk9hN8owxsTgTc5nUJcGkLqKO+3S+ddynC6njvi5hJhZFdlxa0j7YvZq+LQgLc4qNzMq++5APedZ1iuzM9re71xtrCNkYZg26nD2IetaT81baxBYbMI9i68l5JK1So/GXEHsDOj4w8w4dp94NbehMfqdb2tL4nL+iLo2c4p2mzD/62QucazRxJt/jlNbuw7vhqEtTpzjCbNmzfEdgzZzCwvIUES09kOefTrFLKAu+1nQO+r25U4Rryv6uuFy9f92S1gJmv1hKqXu44c7ke/DSHgWluII8yfw8lb0b9o96V7qDUzQQyrpWfqd+f0v2O7N7+WudQ1t3dIoITdnlT3Hq90ednKKNUPbs5g/1e8POTnGUWZk93afCujhFcZZnYuFr+RFDpL6eFdrvV/f5usoxL003b8n8YIZ5a5IuziSdyyRdokk6327uLaSb+zzDTNJFmVhMN3VevpH+kONkWfWcmcyTWaMn+TsgPrJK0jZohn2Qu6vrsbike3KDrr7BPCLzghmu/8gKM7tzPOMKlEfWm9nlWpVnIL4oeY4ibWYOe3Osgz30dqz/1ACUR+YN0/8mLbaH+3rGkW2Stj7pudOVQ78jz55O0Y5ZlXer1PdJejlFNWY5F5wuiRjISjC7H1oVecaTXWRWcIH9Kdqlt1NUZPZnnsQW6Ic+TpFTU9Zp4ensiK+vM/l9Pmk7e+e8i7r0c4r8zD40F2q/LjI/mGHMm1giWQCzYh8650C79JfjWprueNTffZ5hJhZlYjEmFmdiLpN6JpJ5wfTHWzHAfbqgAe7LCzWxcLKszCp1+14f8ZHdY/bj18Lq+x0Dnfg9SdJ5YbthjdX3gQY5RRFmwe1z29GeJhZnsBofnqtnRGRBzK6P3dEPsQ+W91+k3Sg+7RbSkT20K7v7vdJt9MMoec4gLV1sXfXbx9FyPZNW7uIJtS8jmQ+zs36RkWhrMi+Y4Z0TEwsnG6gpK3Ugy3nkOVYeG6XVC7pTBvOP7F9miStGqPOQcU5Rndn+mj8yInayAJh+HiWSjWT2n5Q7qqK88U6xntn3Ud+7Yk2e4BRbPJXl3HpO7TU+Va3za43Pgaapfl+TdL8n/R717W2y9swO7tk8HTGQFWTWeGUmtWfAdKfoyWzf7UXq2TVZOWZ9Sq6NQOxkdZlt2FFMPU+d4RQ9mEVuCPo=
*/