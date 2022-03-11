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