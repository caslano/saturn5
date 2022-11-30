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
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
*/