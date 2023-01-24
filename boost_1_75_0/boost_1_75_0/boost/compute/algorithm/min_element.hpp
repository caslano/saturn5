//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in range
/// [\p first, \p last) with the minimum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with minimum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator min =
///     boost::compute::min_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element()
template<class InputIterator, class Compare>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, true, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::min_element(
            first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

/* min_element.hpp
oOhHTfQS1W1Y/ySqP2eYKG3Daio8lgqyvxMtlaI80SRaakXHzvlxG46jnW8f5H/SfVIVxmwIEZUIZ8cbsGWjFr5ua862JS2stWxhFbCF9f5T2sLKo4V1lgUTY+ScwbwIZnbNYAuSeqr9tzG03MoJVR7N2h+eRxRhxA6Jsj+hblu1F1LZwFg260i25TIhC+BnqE+zRaoY6EKxQYCVTuRClDwKasepNhO8U6vQU9HLjFrznBuZxvzGGLY8M/GMf4jUZ59aSACbp8n/lnLTFbNGmj+K8r8ZVdzeB2j8aYyUQ9rmpSd132cxBOQY88Mhf2BGZOEaUTZezp1wZqEncCT+U7zmgzOOjNWArkOCzytb1w4iOrryskhc/CQyRXE3kgOOrzEcA1U1aqEtGgU9oIeiPVOEqCj4RrebAWLEq/fCEt3rhoczJena5O1EP8lOsYr5E25/h/lE+oBnqYNZcGU74/094G+nQDw05JT2Pp5U5Ao546uMZyX63krwpXSEnGTPKl3h85Yq9LDNNzFJfx3vQCZ2Spc5e9PipzCfh8NAqQZLfxQWd4IqmtXcH8NAPlj7fx7L/G6tyfgLdg4MvrvyJByYa9A3idY1OvZk3lnV3telED0nVvyMhvSLSrJayvcHEqCmnf+kOsN3yONNjl2L7wJADhQL9y0FCjGmuzhSxdLe8h3LEtg99H/5/BFiIey5BHcCHQtnE+ZnKM/C
*/