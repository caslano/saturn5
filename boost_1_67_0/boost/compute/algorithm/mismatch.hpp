//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP
#define BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators pointing to the first position where the
/// range [\p first1, \p last1) and the range starting at \p first2
/// differ.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    ::boost::compute::equal_to<value_type> op;

    InputIterator2 last2 = first2 + std::distance(first1, last1);

    InputIterator1 iter =
        boost::get<0>(
            ::boost::compute::find(
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(first1, first2)
                    ),
                    detail::unpack(op)
                ),
                ::boost::compute::make_transform_iterator(
                    ::boost::compute::make_zip_iterator(
                        boost::make_tuple(last1, last2)
                    ),
                    detail::unpack(op)
                ),
                false,
                queue
            ).base().get_iterator_tuple()
        );

    return std::make_pair(iter, first2 + std::distance(first1, iter));
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1,
         InputIterator1 last1,
         InputIterator2 first2,
         InputIterator2 last2,
         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) < std::distance(first2, last2)){
        return ::boost::compute::mismatch(first1, last1, first2, queue);
    }
    else {
        return ::boost::compute::mismatch(
            first1, first1 + std::distance(first2, last2), first2, queue
        );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MISMATCH_HPP

/* mismatch.hpp
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
*/