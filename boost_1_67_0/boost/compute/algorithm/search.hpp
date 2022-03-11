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