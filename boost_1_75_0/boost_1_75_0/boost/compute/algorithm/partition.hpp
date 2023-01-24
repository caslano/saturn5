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
EWRF/+IgI2hR+qy95EmmuJgIpr+X7N6kXR6oBlDl/sFoSNHrFGEIT42mlUnV/ZkNbVPL5/SW74WWmZwX1m3iia8uPVm157VgC2hMki2gXxTWkI410Oq7iR8onVV7l++RpL1CYG4jJPgu/p4Wv/bZaVj95IsTtvBwC4ZOw1wjRe6Rx2R6QmOaPdKYdLgqytdWfSlmU4zSvzO+BMpzKh5An3g5jMIj3wcLY0E6DJcQF6yJWk+wcK/gRKkKLpW9MKYffyZ4Xu2l41465CKHEzgXKBFqOlrVKrlMzNQJ2swnCh1j1P/NIO+YFmXnxc14Bi1uY8bzAYuehRYz7iyVzH58UqN0Lmu/UzrllsflKYf9aB3zYGdXzl/J2MxlG8t+uMtP+kegC3w8pwYyncELpoVXInmTxG2Ugc+rbHXLbsCJHpR5i2TYFO8BBjRwwikdc0pnXDkssZttJR5szg1D4G9wp+qWxS5B1WRbiTFGpWog0RLGFjkdtf4EqQoo0wRXE8XnpRcLbesri5wZlUXB1k6LCqVK+Ol0bF/Q2Sv5P8n0lbcE4rzy8PqXMdTnHtVedAKlGq2OmvmdPkLc4JKXqSSFcZPIwSMnuJSGBShfwg1mOebMUAE01KVxQ9zyxMxwb6nKck6tgp0X44I+LrwMOzRdxYfVDpaby/bYKBQgW6kF2Jlx0i4oPoJEOhGjpvfnMJqdUiMYMlFxS0kdH6S0
*/