//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators containing the range of values equal
/// to \p value in the sorted range [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline std::pair<InputIterator, InputIterator>
equal_range(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return std::make_pair(
               ::boost::compute::lower_bound(first, last, value, queue),
               ::boost::compute::upper_bound(first, last, value, queue)
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

/* equal_range.hpp
M6MZixLguSygadrsR0VI0vGFng7bXpUe3WzVfQurfMGS+wiG9YCtTovsmesXBdN9uOGU5NR+5Jap7wFO0PFePPwQA5zr7MHW2XU25e9pQNYlFnE8Ad4G05FGUDaCS2d+4aC6Je9Fyd3A6CkdHa+bGMSQWaDII6huJ23H3VZv53jARkfhPcJliW1FmTh9IsM2gE+yY2Cf1pJGndS43KoitqW6De49hdxVDWmy/oR3TGsE2uG6rpbBF8H/VgK9jwt3v5N+2r8M1kqrUbwYOKVLt5AF+UDXqDrXsTObnmyDnEWrZPq91N06SIvqcQwb58pK6NHns1kLKW4rgrSMWnyTv7jWvm800hrblmpNpFkuS0JT+u8YUV9RYxEZ2Vdp/sU9RvOz/cH2SFnMza7fEWl0r9C8UseCD3nN6+Y6ryHiHJUZIlXY/2oRTAdCgSaulrFhmJ4SzC0l6xASeJ0Od1sEL6VZD7T8fNH7U/+zss9L0y9NltdQTCfjQGhIcEmh7zg9vCiQLKOTXkJdIN+CUIXuJzPKMEN6uIS+3JIeo1D2IetxojpejP3DoCXYqA==
*/