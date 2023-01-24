//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_MEMORY_LOCAL_BUFFER_HPP
#define BOOST_COMPUTE_MEMORY_LOCAL_BUFFER_HPP

#include <boost/compute/cl.hpp>
#include <boost/compute/kernel.hpp>

namespace boost {
namespace compute {

/// \class local_buffer
/// \brief Represents a local memory buffer on the device.
///
/// The local_buffer class represents a block of local memory on a compute
/// device.
///
/// This class is most commonly used to set local memory arguments for compute
/// kernels:
/// \code
/// // set argument to a local buffer with storage for 32 float's
/// kernel.set_arg(0, local_buffer<float>(32));
/// \endcode
///
/// \see buffer, kernel
template<class T>
class local_buffer
{
public:
    /// Creates a local buffer object for \p size elements.
    local_buffer(const size_t size)
        : m_size(size)
    {
    }

    /// Creates a local buffer object as a copy of \p other.
    local_buffer(const local_buffer &other)
        : m_size(other.m_size)
    {
    }

    /// Copies \p other to \c *this.
    local_buffer& operator=(const local_buffer &other)
    {
        if(this != &other){
            m_size = other.m_size;
        }

        return *this;
    }

    /// Destroys the local memory object.
    ~local_buffer()
    {
    }

    /// Returns the number of elements in the local buffer.
    size_t size() const
    {
        return m_size;
    }

private:
    size_t m_size;
};

namespace detail {

// set_kernel_arg specialization for local_buffer<T>
template<class T>
struct set_kernel_arg<local_buffer<T> >
{
    void operator()(kernel &kernel_, size_t index, const local_buffer<T> &buffer)
    {
        kernel_.set_arg(index, buffer.size() * sizeof(T), 0);
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_MEMORY_SVM_PTR_HPP

/* local_buffer.hpp
4AxjZXg3iK/LIHORfUo8jSHJ5VkPBA1moQKeeGrKCZzeSTTQiiOXPOKZiqqfOag0axPSgfGDpgvxUf28PyR/mPBw0Nd5+fWQ2VFyUhQD7UPkW5/K8VpD5l6/76Xoh8CNwJ8qz1p0aHMGA/CGWF8LDUuvKijxj80x54sMOOL/l2ENQU4hajO4XuS8Ilh2Ac+ztcn8yvlMIk2kWWbIM130w8PpEX3M4Ql88c+BPkdsaMjMA9msn2fZr38GVkQs0VB5f0gulTT3ssA8u+R/SfP+kFNc+gLwMvyrIcadJSX+FjnG8tDWQftWYnwmp4SC2vjh9TMuk4x8RSXyTInbJyd94Hw1aLHlpEno1z14sBzmVJrbB/iF8nz0KYnhgLTYy1xfjjXRlfRjSHnn9MFeJqf+4vwP8VeR/AJ9ZVqEs4lLKnheh2gI+5V4/ELj08XUQc4rB47ImhmFh2VBZVmOTAfgIQa3m2kZ7HtyPkmB5X0vexyiL6A1QFR90F4GzXSBdR9d/ET81/p5vaQVLPP93MMhlWb+ujegfwbPBcs1RryXKQrWcw+3r5tpFGJFxCuvR8E+FoSXVziDtJfpr4f5syypI2MdLBc47UvOBetl/sSDB+5wkGk9oHj5qgrKO58J3prwC+tWyJzWo5ARyQ8PGFfOvi0yJyb6xLQSq5HEcECT2a9whj3s6H544OORcb+LOX0v3ln8N0ST0MvSQ4pb
*/