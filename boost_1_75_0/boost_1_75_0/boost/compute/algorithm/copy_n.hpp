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
r+blnwWVH+Hl/wwqP8XLX9TKRQ/ut5AHz6jBZxhbWvhk+e29+oqRyFY23mziSy7aHlDdLXh1zWzo0rq/hBsEBdTj+qL98CDwbJtE40hYnoFjGkjfB8/ynRqxa+AO2DXI1UpzG9hLMPTN+tsQeVolravCJk+mtgEUYObIh446qAnpiYUBWcFJR5k8gHrdA/x6YiB2u6MD6efhgdRFp+Xi8a5qerqVLhvpspYuHw80bGE1E+wASLYpt+dilacHhswXnkCxw+d20lJ1mbDkvEuYuiToBaiL3/sMTeySvhsnoeJ/P74S65SH5SFf0aI+khWuS8FBtBIyGFNSmXnJheyqTGtjZqTplfKOBdO7FhqfvZ5oZl9bmFzGY3ukKv8ZhkHQSEPUd/sgVDD/eBL/AEizcjl8nH31iMlQmMO/Wmcy8bTLcw1fTYGvlufyEeZDs/bhcl49V9liN2M6ilz6ebGtGYlRQIPQbYaPJSGIuJ/xCMJlP7WEunW6ctkw7Nax2K13sW5dCNt5QoSYvlfOuvUZW1kvsyBpriRmI/jgteYAUmvb5R2C6ldrfpFx3HETWbig3HhIi60YHi+3oFd3kgG1yxmm5drmJas0kFdKqUfV31ubDTujrOqVvGpqPbZugaqhvcDmkeCB/SeG5rcESwM5evn5Zxedf3ZRb+nGr5341Q6PdyotqFYsXUx0Odev/vlE1HGHGBbiRe2NBvBv
*/