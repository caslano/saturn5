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
hCcjxMeQzPF8K1B6L/Otqm1zL8U8L4RVDRAeyPIM3rw9WCNBHj5CssR6jeyr8iiGs69o36MZkHjYyTaxex3ErMC32SEFTF8edqS4v6blpGLhzC32SPdSgXbk8/XKexU5xMfXDvqXK/K5elgnCa9t8Q8+v4I65xe+Gfbw2A9B8rrLvYPlnkSqj0cUn0cOrKCwv6pZ916EFYnW+EXr+RetR1jk79fqkRfafw1cYJIU0x4QpsHJ+Kyn+ocXD+2nHqapaHNT6tmjOwWX2s0dcRHKX2jHvN1T/wNQSwMECgAAAAgALWdKUjKHTLiABgAAqQ4AACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9taW1lX2VuY29kZXIuM1VUBQABtkgkYK1W227bRhB951cM1IfaAU3l0sa5NahiKzURWRYsOakBA8KKXJrbUFyGu/SlyMf3zC5JyXbQ5CEyLJG7O2duZ2Y2uhjQo5/2CSKGo+9+lu5/iQ9+O6FZrf+Rif22wHL5lfwfBC/w+wOqhrSR+rrcpR+S+ko7TmrZ6nrDz8vlD6i7YCP5a8jCF0t+xIqXbOUPdHVbq8vc0s7BLj15+fIF7dHTx08fh3QoSiULmltZrmR9GdKb1K38mYubm8jItyFJS6KI
*/