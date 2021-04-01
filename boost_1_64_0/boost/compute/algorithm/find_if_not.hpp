//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c false.
///
/// Space complexity: \Omega(1)
///
/// \see find_if()
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_not(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               first,
               last,
               not1(predicate),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
UdzP6Pk+/v7wDGMO2vYYMueC3qoT/XNFgapB6WlG9cYUa+wSxOHJIgpCHK+u8CmCj0bwK2XpV0VthU1w99Z7cCQ6Y8LaeaXQKUvP9eNhUbD6DwDq3ncp8iioocb7tdoD3TOYXtTDwFHDjuV07quSLUVTn40qkEit9NzGzL6j9MgW+CSsSy1OMIpGJraRujuVwcbhIZpgMlbfq/H4242hnMeW0qc70qm0Fg3NI/Fv9f7ob4AF9+h1HIFu8f/DM4ogaZnm5jn0fKf6WrA7LboiD40r3SlsLmeu6Omx0CMJUGbN1odSygqPqsSqYA/2+N9wohwatC8uDODP1tSaWoWbDwZoU6DrauvbZ7guHCS2cojRhPrgAcKvGXketMjQwhD3SpW5fKqodj7uNkIPVzIF2xNswlBDA1Zmp9uighg+ebPQwi+nM6jYakDvGKTkDRjhzOH3/AhPSrkxtU7CzgevM5OkzFt7ssIaR3WfVyL4k8WcJUTG7r7F+Od4ZxTA4H0EVW20rShFnCoXHbjNvtpF1jI6fwDSOr6/z/HJB/gJxyxxdzlef3abm+o8tw==
*/