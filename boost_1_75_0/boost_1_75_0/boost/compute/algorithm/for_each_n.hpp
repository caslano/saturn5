//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/for_each.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calls \p function on each element in the range [\p first, \p first
/// \c + \p count).
///
/// Space complexity: \Omega(1)
///
/// \see for_each()
template<class InputIterator, class Size, class UnaryFunction>
inline UnaryFunction for_each_n(InputIterator first,
                                Size count,
                                UnaryFunction function,
                                command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::for_each(first, first + count, function, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
gJ9NPnkls1o+yJMt/kSLDN4xf3rqMQ9/bej35hy936iKgXFH+j13UKTfnfV+7yARtL271u85e7R+HxO1fu8Yq/U7lfqtioPPiqElitEQLdLv1Qxz8X77flW/n4z0O436fYeo9/vvAyP9Ttb7fRfr9x3jeL/f2a31+wq93930fqdQv4+Kgw+LoRl7ozMbaP1mO+UAC2H98AACLP3TfxkVjA0wwTDANTRCPuoG/hDNSn2tuFFMlRGrC10nM3MWBfx6pxPbJK/z64udmG74aX4v8/tyvLbV87Id9NhnRms52EKdxnEdzCR4Oz2VMcvZCNP+CFN5eNIdFiDI9wBoJ8xAHcVI1Y3OCIcY2TKhjuGIbNVeM5brJ7KVdS5BCHeFjw/cTp/UUehWY5yh7z1tspaJtPXw42VVsPdy/rSKyJnzhAtnj9VnfeMAg/JkCDJ41Ldz0/VOZSobd+lKk+vG6kqTPi7GJeUZLfbQMPm7G2iRMV+vc9xxlCjz+1R7k1tv+mZj01frTdcbm7450vR6t9702jFapZJJemYV0WKZrL3fae2F/qQ5C3ThvcSFkfOn1QY4TI905t3+hs7coHfmPWNn3t2pd+aqSGd6jLkEHJ4ZboCDqQ0cvnTpTd9gbPpmvelnjU3fEGn67y696edGG+Gw2giH50w6HFZ3CIc1BjhMjXTm7X6GzozTO/OEsTNv79A7MyjSmS6jLwGH/kY4
*/