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
Z6L3oC3qkfqk+O7WfpuJtgQYZSZZ6yAoMO2ANI8HXdXrd4OiXy/eqMZOxj1E4T+S2btBhJMWn8jFwRXSi4ZDGoyjCbaZ43O6f3Xq4fI+1YdtuPwMj/4DUEsDBAoAAAAIAC1nSlJdPKf3GAQAAIAJAAAsAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfbWltZV9hZGRwYXJ0LjNVVAUAAbZIJGCtVVtv2zYUftevONBe4lSV0xRd1yUtpiTqIsw3WEo7DwYEWqQiDhKpiVQSA/nxO6TkOBcbzUNlWKJ4+H3nwo9H/tKFw592Ob6hgx9eqf2neOFzA5o18l+W6d2ANL2H7ofAJT5f4WoIW9R9OoBXoe7hwKLS3tepGafpK9wtTZDmNjTgZWqGONMhe/y5rNcNvy40HJwP4N2nT7/BWzg+Oj7y4IIIzkqINRMr1lx7cErtzB8FubvzFfviAdNASv8JYVJwBUrm+pY0DHBc8owJxSgQBZSprOErfOECdMEg5yWD8+lsEU3+9OC24FnR86xlC6qQbUmhIDcMGpYxftPR1KTRIHNkQH7KlUbOVnMpfHTPQLOmUj2NCYKUSgK5IbwkK3RHNBRa1+r34TBrmxIzGVKZqWG2KYVf6OpZVguMpiJrkLUG
*/