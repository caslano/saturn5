//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/partition.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/functional/bind.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Rearranges the elements in the range [\p first, \p last) such that
/// the \p nth element would be in that position in a sorted sequence.
///
/// Space complexity: \Omega(3n)
template<class Iterator, class Compare>
inline void nth_element(Iterator first,
                        Iterator nth,
                        Iterator last,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    if(nth == last) return;

    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    while(1)
    {
        value_type value = nth.read(queue);

        using boost::compute::placeholders::_1;
        Iterator new_nth = partition(
            first, last, ::boost::compute::bind(compare, _1, value), queue
        );

        Iterator old_nth = find(new_nth, last, value, queue);

        value_type new_value = new_nth.read(queue);

        fill_n(new_nth, 1, value, queue);
        fill_n(old_nth, 1, new_value, queue);

        new_value = nth.read(queue);

        if(value == new_value) break;

        if(std::distance(first, nth) < std::distance(first, new_nth))
        {
            last = new_nth;
        }
        else
        {
            first = new_nth;
        }
    }
}

/// \overload
template<class Iterator>
inline void nth_element(Iterator first,
                        Iterator nth,
                        Iterator last,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    if(nth == last) return;

    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    less<value_type> less_than;

    return nth_element(first, nth, last, less_than, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NTH_ELEMENT_HPP

/* nth_element.hpp
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
*/