//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
IeqavVu0QionUxqQ6F2UjKM3yTjJrr2IkDWnNbxEa+QwrZD7cZFlswDSy2zGp00uI9c7VLxxyxCisuyXfq+5HnseZ1fzCbyLxlexxyqI8+lbDhfAb4BtSy9OGkwpLGmDE3l9cPxXdDkbx16olh48ooQ1Fb+5STjxPNhYNn65aBpU5c7wLSA1Oib3L5zhmNa71qQYCh/t8dpnAg3CZ/+GWUCnMdhobG/kPaJm7lWwCc3mV/EauRG8IodRKIUVX0GwaYj3nx0+/+XFy1dHJHCmKf87nk/zLJ5fJpMoi8/XkNxfJWjqtpHYtEZS3Yr+sxs+X7iUjlY/jWOIxumUdsSb+Rdxoizd7vFpJfjef1BLAwQKAAAACAAtZ0pS2lWT9X8EAAAKCgAAKQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX21pbWVfaW5pdC4zVVQFAAG2SCRgrVXbbuM2EH3XVwzUlzhQ5GwW7Xab7KJKojZCfREsebcuDAi0SEcsdKtIxTGQj+8MJSe202LzsA6iC8k5c+bwcOQubTj9bj/LJTj45i8x/wn+8L4LCpvqb5Hq/w5Ikifo/jBwifc3pBrCS9RTMoA3RT3BiYlK+lxX9Jwkb0i3JJJ0GVLwMqFHHOki+/ibqt42
*/