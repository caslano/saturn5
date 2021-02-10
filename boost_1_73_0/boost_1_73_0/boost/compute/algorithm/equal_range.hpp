//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators containing the range of values equal
/// to \p value in the sorted range [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline std::pair<InputIterator, InputIterator>
equal_range(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return std::make_pair(
               ::boost::compute::lower_bound(first, last, value, queue),
               ::boost::compute::upper_bound(first, last, value, queue)
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

/* equal_range.hpp
MxllFvvPNR2U1iypR0Wplo56h/+GVSoP8i8up+eT4fVseDVOAmhFYzLRjtzyjpoqAF3VdlmrNbG517U1azbI2RWyvrPcMOcuJcHd3El6aJ+gqgAzP6DYnQhskwZXalU/UmkVkipNnqldN87TAj6ospTShA5WWLImY9ogAVDmamvQwdMjhOBKIipCEIJ9boX8wwZqaW2h1FUq40PIL2zNe66JPjEYBSlJlmwNgr7Wy+Af7wUBKHZxgv4M1eUVliG99bVg+J3sKpKCxFlZcmrN4SzfM4xrT/RROAhD6XVVcmtX4KvuSsJFIU0EAbYmnghh5BZgMEowXPxeSN0rj7I1MSKeRV6HGz+ozJeP4ANsFax8I+HyNpG06e/z64JLu0lpyj5Ygg1dy7KG/4tHuppoJJns3KuyCVKWLKFMk6EhY+s1Mt2Cg0Jy9wMbB7BdxRn4jiR95x9HV2eD0XwwGiHaF9a88sKMO7gE4SCkUhhAZAjBFGqtS63qkCACigR5zUg/cBhQ8bWV6pIo7BohRJZ04CbJbXG2n4t4Nla8rVnlCH3B6W1xHZlbLJdNib5o3KzY7JjZ3ml70jZddcopUOkkIju7oIVciFl6KIrrxhjspbE8cstOYvGbqA2OGRs1dbICuDjZOJH4lLFnnClE
*/