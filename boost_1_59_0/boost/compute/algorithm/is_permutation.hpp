//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/equal.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Permutation checking algorithm
///
/// Checks if the range [first1, last1) can be permuted into the
/// range [first2, last2)
/// \return True, if it can be permuted. False, otherwise.
///
/// \param first1 Iterator pointing to start of first range
/// \param last1 Iterator pointing to end of first range
/// \param first2 Iterator pointing to start of second range
/// \param last2 Iterator pointing to end of second range
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p first1, \p last1) + distance(\p first2, \p last2))
template<class InputIterator1, class InputIterator2>
inline bool is_permutation(InputIterator1 first1,
                           InputIterator1 last1,
                           InputIterator2 first2,
                           InputIterator2 last2,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type1;
    typedef typename std::iterator_traits<InputIterator2>::value_type value_type2;

    size_t count1 = detail::iterator_range_size(first1, last1);
    size_t count2 = detail::iterator_range_size(first2, last2);

    if(count1 != count2) return false;

    vector<value_type1> temp1(first1, last1, queue);
    vector<value_type2> temp2(first2, last2, queue);

    sort(temp1.begin(), temp1.end(), queue);
    sort(temp2.begin(), temp2.end(), queue);

    return equal(temp1.begin(), temp1.end(),
                 temp2.begin(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IS_PERMUTATION_HPP

/* is_permutation.hpp
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
*/