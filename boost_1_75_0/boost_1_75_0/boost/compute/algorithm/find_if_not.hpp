//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c false.
///
/// Space complexity: \Omega(1)
///
/// \see find_if()
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_not(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               first,
               last,
               not1(predicate),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
zsgDQH4CgAAP8lQsF4aho7wr9Bq3d7GQ4R/aauI9w3PIThOTXQzfuHJYUdvKebjsZO4S+tyFM+oabsAfvJhqW4kJBR1waMLumv8oJcMUz3wj1lSq8E+05VaKsPJ7wCHtxRB71Z7KRgu2VKt8fhg2iS4Yx45g933SdqQveWO7Ghj0Wk0MBFbl6jqTEGKtoQk0vuCdaTskL6dSmIqLjes5Kx71J1wO5nNgC7oxQJ+03UkyMvQfVuiavE3k/VFKdp9TjcY3trIWNmPoRZ/JPYpFK8MYfAYrYrWoGubL6NTVMf8a3OQGI4MuQPdMNZP3Sh5OVmx0RYt4RfnKxt5tKkrVK9J8557gFeVjRZ/ERFU0LFbjKkvaVpSpV6Q5+Tp5RZlY0WPcIlBbhV0NixalXur2pncuwkyTCtQ4k5x04jNpOhQ9k4lK4U4T7Z1Wo2/3yoMC02EYbdMp7m/EmMkW2XG6proTqc5XTcFTcDEzZ94bvSf30p4kIeJ6vmsJR0HFrCSVqhV0g+fnLbrBMzdADmlOPAzdqfbsKdwwq1bbxKuJ5tVMljXjZ7R8/qOZOym55FwT+b9TVWhj2+9RCmSr1XpkMnOxY3E1fGa2tHVDtUORqLYXWVRbvk/LBpkj55ph5Osip9Fn5ojpt244r8W2nTxZi2071wBhgztHpx7R5tfahAyJnhDmBsMcOfzsYMKbSwS9vYXkiy22slcEHvSW
*/