//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/search_all.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// \brief Substring matching algorithm
///
/// Searches for the first match of the pattern [p_first, p_last)
/// in text [t_first, t_last).
/// \return Iterator pointing to beginning of first occurrence
///
/// \param t_first Iterator pointing to start of text
/// \param t_last Iterator pointing to end of text
/// \param p_first Iterator pointing to start of pattern
/// \param p_last Iterator pointing to end of pattern
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p t_first, \p t_last))
template<class TextIterator, class PatternIterator>
inline TextIterator search(TextIterator t_first,
                           TextIterator t_last,
                           PatternIterator p_first,
                           PatternIterator p_last,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<TextIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<PatternIterator>::value);

    // there is no need to check if pattern starts at last n - 1 indices
    vector<uint_> matching_indices(
        detail::iterator_range_size(t_first, t_last)
            - detail::iterator_range_size(p_first, p_last) + 1,
        queue.get_context()
    );

    // search_kernel puts value 1 at every index in vector where pattern starts at
    detail::search_kernel<PatternIterator,
                          TextIterator,
                          vector<uint_>::iterator> kernel;

    kernel.set_range(p_first, p_last, t_first, t_last, matching_indices.begin());
    kernel.exec(queue);

    vector<uint_>::iterator index = ::boost::compute::find(
        matching_indices.begin(), matching_indices.end(), uint_(1), queue
    );

    // pattern was not found
    if(index == matching_indices.end())
        return t_last;

    return t_first + detail::iterator_range_size(matching_indices.begin(), index);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SEARCH_HPP

/* search.hpp
sN/s/sVpYRxuiGf30UogucKjpwteKmSYFdJY98SfOuoI4yED7xh7hUV8t1DGTntmfs1mlcBbsu6ev34SZt+AbqTFZHm9mME/o4vrSe++c9sah/lOKGFwn3V3cIC5WwTCGNQSOcQ+2CCZTGB0kczxmv64gKeJYYCpo0H/iVS4MvwxPPHCSaP/6tqn8H8z4g3Q+z9QSwMECgAAAAgALWdKUmpXl1swBQAAigsAACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9tdWx0aV9hc3NpZ24uM1VUBQABtkgkYK1WbW/bNhD+rl9x8D4sCRQ7bdFu3Ypibpq12lLHsJ0WBgwYtEhZrClSICm7Bvrjd0dKtZ1uaz/UQSKHupfnnnvupP6iBxc/7JP0KRx887MMv0v84LVzGlvzUeT+3x2Wy88Qf9BxgdfvSDWAg9fn5Tl8l9dnOAteyzbXC/q+XH5HugWBpD8Dcl4s6SueRM/W/9rUeyvXpYez63N49Pz5r3AJj68eX6XwmmkpFEy90Cth1ym84OHkj5J9+tR34mUKwgNT/ZOAs1I6cKbwO2YF4Hclc6Gd4MAccOFyK1f4j9TgSwGFVAKu78bzbPQmhV0p87KNszcNuNI0ikPJtgKsyIXcxjA1sx5M
*/