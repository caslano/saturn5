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
7+rAU6LFwGmcmO+bq1qLS9/vPtuWJUFLWsyI89TDwrD9luXf/X7z+Y827MoOs/EYkkk2wyG6WvSDAOHg4noYQRj8C1BLAwQKAAAACAAtZ0pSLonrLXEEAAAECgAALgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX2dsb2JhbF9jbGVhbnVwLjNVVAUAAbZIJGCtVVFv20YMftevILyH2YMipy2wtltQzEnTxdhqB7GLwIAB4yRR0bWnO+/uZMdAfvzIkxTHRrbmoQ5iyRL5kfz4kZcse/DLD/tECcPBdz+r8L+iD107p2trvmLmn3dYrR6g+SPHJV1fEGoIe6+H1QBe5PUA/eC1amOd8f1q9YJwS06Sv4bsvFzxLT1pPFv/C7PeWXlXeuhfDODV+/fv4ARen74+jeGj0BIVzDzqFO1dDGd5ePJHKe7vE4cfYkAPQiUHgPNSOnCm8FthEeheyQy1wxyEgxxdZmVKP6QGXyIUUiFcTK8X48mfMWxLmZUtzs7U4EpTqxxKsUGwmKHcNDBrYT2YghAIP5fOE2btpdEJhUfwaCvXwnASQjkDYiOkEimFEx5K79fut+Ewq62iSoa5ydww66hISl8dVbWgbCqxA7P24A3UDmNg+xgqk8uCr0QRPVzX
*/