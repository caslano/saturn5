//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the range [\p first1, \p last1) and the range
/// beginning at \p first2 are equal.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    return ::boost::compute::mismatch(first1,
                                      last1,
                                      first2,
                                      queue).first == last1;
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  InputIterator2 last2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) != std::distance(first2, last2)){
        return false;
    }

    return ::boost::compute::equal(first1, last1, first2, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

/* equal.hpp
7+9QdURPt77ND+m7bn2jg3Br3up6L8/z+XeouxUj5c+RXL6dyyNW4s32/rmtHmu9XHk6OD+kN+/e/Yte08nxyXGfLpTRXNLUs1lwvezT+zys/GelHh5Sx7/0iT2pMt0TOFtpR84WfqNqJjyXOmPjOCflKGeX1XqBH9qQXzEVumQ6v7r+Ohx/7NNmpbNVK+fRNuRWtilzWql7ppoz1vdRTKVqT7aABMjPtfOQ2XhtTQr1TJ7rtWvFiBGqdJbUvdKlWkCd8rTyvnI/Hx1lTV3Ck6PcZu4o60KRrvz6mVdfYc1aPZKtPHlLjeM+yfk+rW2uC/lGiLBYNYtSu1X/ySwoNPmRrclxWbbicFWziy4wTdto9eUkVbBee/ly1jjRtlnZ9d5BhLUVVDS1gTqEBedyi8D3qTE51+F8CESnpY1yCPlfQPZke07WwCrqDaY0nPZooZx2ffoynH26upnRl8FkMhjPvtLVBxqMv7byfh2OL5AbGlpr4oeqZgcratLrqtSc7yn/gZU++0SC53xZ2oUq59ogiqfUe/OGPgO5k+Pjf/SoV+qFHKK36ZuTnZ+flWlU2UvS6ScaDz5fJi8kvaaP4Rd1V2RVK4CtJPPCzenX8dX1dDhN0jP6mzZZ2eRM7+V0zLTVL0nqKuwOqXd+
*/