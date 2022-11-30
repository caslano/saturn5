//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_N_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Copies \p count elements from \p first to \p result.
///
/// For example, to copy four values from the host to the device:
/// \code
/// // values on the host and vector on the device
/// float values[4] = { 1.f, 2.f, 3.f, 4.f };
/// boost::compute::vector<float> vec(4, context);
///
/// // copy from the host to the device
/// boost::compute::copy_n(values, 4, vec.begin(), queue);
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see copy()
template<class InputIterator, class Size, class OutputIterator>
inline OutputIterator copy_n(InputIterator first,
                             Size count,
                             OutputIterator result,
                             command_queue &queue = system::default_queue(),
                             const wait_list &events = wait_list())
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    return ::boost::compute::copy(first,
                                  first + static_cast<difference_type>(count),
                                  result,
                                  queue,
                                  events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_N_HPP

/* copy_n.hpp
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
*/