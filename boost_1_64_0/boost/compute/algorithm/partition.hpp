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
QCIrRXO9BlnWd4qTAYGj9gbSVGBqBxGDId/leI4xGD6aMA/XXivO+UlfyaAFFqC0LQ60oD5Y8Mr59g1CTrvo7vkeZI+tDs1ZgYMToSzMXqztdzB6OdAfROWfx9dBmZ6ZHLROQ7eyVnNpYdqWJp5P1/YdL0szz887REPlu3D9/9jna//dbPx6CF862EHG017W+VFS7RCLKHKMy/R5Vug/SDM9wwFAMOrN0xr/C6c8UrVS0xrWycaDz09XlRf9DuJR4MeLOUA/0TwIMoyDFN6aBzXz4F1kdMc1bBwonRQ31K9Pqzy1j4oOKiJ1INGxlrbnrpI/QnR0iCI7KxJMAxkIJoatj3fK9Mjh9CduxYpIHzLI+p8e4h5Tp/zlu2WppYD8Ipzjx+z0x9h/zPP3zzpk7L6s8H8wGipPn0KkqZxL7eqF3IWbMDOM9mbqEiYI2NqtE1lklnMo2h9K96r5iK1IiP9HZjkwSYUF9c4wlpK07KHkwYCXDA/u9FHudhCywEJNI4LBlMrapqXBQU6Mk31IXijoLnbNYhlSm4NII55ZUciAfA/Y7yAiW/7l0Q==
*/