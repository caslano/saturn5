//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IOTA_HPP
#define BOOST_COMPUTE_ALGORITHM_IOTA_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p last) with sequential values starting at
/// \p value.
///
/// For example, the following code:
/// \snippet test/test_iota.cpp iota
///
/// Will fill \c vec with the values (\c 0, \c 1, \c 2, \c ...).
///
/// Space complexity: \Omega(1)
template<class BufferIterator, class T>
inline void iota(BufferIterator first,
                 BufferIterator last,
                 const T &value,
                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    T count = static_cast<T>(detail::iterator_range_size(first, last));

    copy(
        ::boost::compute::make_counting_iterator(value),
        ::boost::compute::make_counting_iterator(value + count),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IOTA_HPP

/* iota.hpp
BtlSxHW2HtAh8Ik1tmF4x/BCcZb9cXHIXqLMcMWLxa5E8aCrj8hzdxer3T6xwT1MnHL3F3082OWJKVTO98WLK32JIt93vuju7yXy/T4xwz9MvOTvL+yxj4uXYguVmxL8Yj6afk1CH5Gd2EXcnOgTixOHicO4TZCY9Lh4LWm88m5Kgryf0Yfq01UMpfopIofsKS1ThF1cK87DaYcTespesRW7in/EbmlLxSv6AqOAycpC8aXy
*/