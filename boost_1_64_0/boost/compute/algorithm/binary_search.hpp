//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p value is in the sorted range [\p first,
/// \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline bool binary_search(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    InputIterator position = lower_bound(first, last, value, queue);

    return position != last && position.read(queue) == value;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

/* binary_search.hpp
zy4v7d9bEM4Oqw+9YxWq6djY7aaTbIU/A8dFWkKQ/wXFqt/mrahBv5u92sQ3lnoJDNs+Yvu4xlv+nCuYfDtW6R6rqAR4YNJ2kTybhcZMug23Nev/Ou38W08CaZRl0Mgi21dQMV1HSbINWpGZWCPBROvEc7BcJodWgsobk0+59kC9dLEIaBBgpf00bO4gQ5tMAKxek6K4fErGaJ36rikYtTtUhMKW0i607Bluzg2XO7Gy0+X6FBljxI3rV8Olzjjot20L4ODxas3eWPkhMgbdKT4gQMoNMSK8rhXnFks0oCHn5n21Kd0H5FzrX0jv0BQ9rJ/huQhvOjnqLm1l3btHAcsNnCLjpiGIUymMCbF6CFKu1ZZlY8fGEBXsRZ5mcq4fUYlak0i3KZa2BDVAQ556iJvO5tWkm57UHMlRd9fTv7cXQ2EBnvj7jgvKqkLaVTq1hZOOqKKLT4+FZu39QHIJdo+SPpAmMokAr6ObkHs/Qjqn7IfSWjAAtnl8Ruu0QosTnc312cOUceca8IocGptSt06z8x5s0UPyA+aT1U1807S3of3knb5r+VRZYQ==
*/