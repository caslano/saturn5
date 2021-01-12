//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
cWQgzevD2JcUSPYmJI4OZHl9UpoSPazkW7KR/+rjMh29J5IpCTjKwinFoWUzwg+4ax1SRGQ8vRcJzZ+lRb2Hl6TZ5/5cqevaeNJNHeY6s1htkKn3QuWjc1ycedT3pI+7gReDc/5G3w/MLM3Nm1tg5+0d+IT0AxbwvJ+JXdqwKB3/Tfomuk4yVA+IvR0x7KWJvdCYS+yG51kl3t25joxrnJY1rdcj6tkyadNSJay9hBWsx3vF
*/