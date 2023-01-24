//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for none of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), any_of()
template<class InputIterator, class UnaryPredicate>
inline bool none_of(InputIterator first,
                    InputIterator last,
                    UnaryPredicate predicate,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
SwcFf1YDXciO1fIzphnDTV64K5QP0xJXFLpe7AitcXg6NxC/z3KgHlbqYewYvKP0MlGy1OS2MmGApSgkUupiDbCNmyN+zqKcOKQ3Wh6cumCKjv3DuolicUZFlXB7iZX+tlRUFA328Wt63JVgZYEy+zr8anw+pxUL83X60e5D2QqyI7CXcvC3Y68/TnzcOhx/y+MLlPRLfStbD1Mru5Aa0U/BphIoTzIoRphY560yuLByz/Fz3FgCNbGK1IdTy1dp3CUjlwcDLDYjLYtW/yavtJvJPKPTYOjO6FoATe682nMBURPZJCXR4LniBLMxtzY8rsu8GbOT+MVPsWwGN3elYENVqj0jRCLjm1T787BxbetrN6Mqq8sursx6uDMj7BafN6H9JxQhb8QuVeSK2IS6WkfV/GRW6DYotAHp8aZYk8D9W3S9AXA3fz+PVll4tHqZ7S+LN4U5zEYSkyM5k12SJwloCudltvWTUpCPUu0bzjM5fyZChGxeTU6Mrnv04TipqukFzvNnapPdrxWzBMEhf1V4kDoFo5GQa8heZYSF9uH90NUp8fBjthisgn3jEAIN6L/ZHEtmPbHqXngHR1K/DT/GEp2XuB5+hIGAdKDQaoh6GzRl43UqZqqzN9R5WzxjaBJX/YjUX1W86Dg8fyfK1gu4cf3ch3gIS8bg4zQZctnNowQD6HNREkvzl7IyMn/0ZEvahljk3xqyTjq3
*/