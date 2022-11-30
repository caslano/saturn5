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
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
*/