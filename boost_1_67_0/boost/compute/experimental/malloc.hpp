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
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
*/