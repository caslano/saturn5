//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/stable_partition.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// Partitions the elements in the range [\p first, \p last) according to
/// \p predicate. Order of the elements need not be preserved.
///
/// Space complexity: \Omega(3n)
///
/// \see is_partitioned() and stable_partition()
///
template<class Iterator, class UnaryPredicate>
inline Iterator partition(Iterator first,
                          Iterator last,
                          UnaryPredicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    return stable_partition(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

/* partition.hpp
3Vd6teVItA5Ay65VlI5oIb9SE/EBdKrE1vk7ItZZBpYd5d9p2ab2ErSiqsCPUkhSHxbCSBPA+yS7mF5l8D6az6NJdg3TPyCaXA94b5PJOc2GpKwt4MemRUNVtCBXTS2x3Er+A5WeXQD3M1/JFeYVCmLBwHPwDw8h6m47Y2mun73ywa/lgh3hVfjiZXjwheFSqE7UvhemFzCJLmPvW7x9aiMNPbDRzeHPhrIaSx0aXFx0ej2ZztIk9cI38JNURd2VCKcM189c9doLTUNfE/DPrubjQtP3b7LtfLa4id8Dvx/9oA+kJnW0npyToanrPdaV+gGJzJLBin8w1/eKjJVswN89oROK0tV5Hqdn82SWJdOJd7NMvq3g+e7NcsZnNv976NDjcP7E7jRCPHGDZ0VTTbKjARXGyNte+Nvh4Kq3uocZjF8gsYXnWPSO9LQdfwKkGNbnAl1/KNfkajz26N7iStP6EEBjeCd1Z+oH2gBWFCyaLRSH3VewTRkVckwiRAVKq/1/sSWRFYJ2QF/cUDvnXrZIqF2jlddiU4sCV0g9oNl31PUN60hkJdbIC+ukX4R0zEIY3MCteFyVtgTq9aCkI9qk0tYPVGKK1kp1y6d6rBtDSfe0eZnBO1HL8piUTEfnDPTe9TwtHjyXUpB7
*/