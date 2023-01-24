//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/detail/device_ptr.hpp>

namespace boost {
namespace compute {
namespace experimental {

// bring device_ptr into the experimental namespace
using detail::device_ptr;

template<class T>
inline device_ptr<T>
malloc(std::size_t size, const context &context = system::default_context())
{
    buffer buf(context, size * sizeof(T));
    clRetainMemObject(buf.get());
    return device_ptr<T>(buf);
}

inline device_ptr<char>
malloc(std::size_t size, const context &context = system::default_context())
{
    return malloc<char>(size, context);
}

template<class T>
inline void free(device_ptr<T> &ptr)
{
    clReleaseMemObject(ptr.get_buffer().get());
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_MALLOC_HPP

/* malloc.hpp
PZSLdmuDn0j0z8CBNF2CNcYRv+5DLh6o9y3ibxH35+XLr+voX1/wW4p2aaPerO9p+R55FPWuUGSm0P2I2D8uyaL3k05R5P3juciXcRXzxkfyj0swHsT+8ZSLkCdQC+gKNL+A9SqX4j/lH48+i/lRhX88EfMyfw44D/0dlgN5nsZ88x3WizNoPzARes2f/3VBf5vi+aoR8CL6nz/Pmw39Cd+H/TswSIS+QHOgGTDlW1q/uuccTPbx5wAo5qC9/HngkmTMr7ivB9QGagIZYDnaVQosAhYC44H5wDxgLjAbmAFMB0YDxc+pU4HJwESgGS//uajnrPB9gXRgOdoXxNtBiIdi3CYBjUAvb4N8+iinPfYr39PxaQ29kZ53ht7kvYOca0NPtCi66WA8APMaYfw0gZ6ivoIXaN9L7Ld+h7yBOa8oFrymePgNxdi3FBPwvMfgYi3BeHh7Ae8RrEE7EqHfwKINiG/E/PclxnMSxbBN4HMzRV9gIjANmAHMB2ptoagPNAImJWNcpUJPcB48BcjP6xLYpQOBaQcpRqK/44FJwDRgFvAiUGMeRV2gAdAUaA10BfoCw4DxwBRgBvAisBBYBtQMw74VaAK0BroB/YGm86HP6Ldw0BOAqcAsYB7wIbAcqIFyzIGuwALIoRQYDXoSMB2YA8wHlgCZBZAf0BD4EPyaIi4BugODgJHARGAaMBto9BrzIlAL+pqC8ajK
*/