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
qzvEHLgfMPgKdijUBxh8jVDQIx3mBsVkQh8Tbb4+R2/vDzoW5bDOF0z/AOctdl5ZPzVlPQCYflHw+8jhjj2Q1MnPjoh+vAkM1B1FPbLLR/ggi4FmOTradvzBoPfKAUmen92d9Dq9QGWFee92Dg4xft67P4/RnT0JfiOHHAY6RnMO/jmkBzkHX3nngB7YzH4GujdGyDnoyrjLCMbJgW/iGAb2LPhzWQz63vXXQ7syAroWAd70MKWF/XTV0THPgn4SdwvoQT99O6QHdT92d9A1EbF8e/4B3QoA/Wn3COnUT+7doGN+2/LBf8+QTsv/yIBOfZQO3wt0rA1Wgl/GCMbX16P3HtJdNwHzNopBBku/rx9+nyHGz9H0riHdiAH9X5QORQL/kYAejPWh+wb00I4MOtZItAFl3G+AIW3YH9KtFOQ2BB1rKHQK+UDvH2KgV8D8YxRDx37jAcD0a1owx/81hgnm+N4DRzBB390ABt9NdB765kFDjK9nN0fooZ698sHA9N+NoE1/G8OgTfBlGWKCNv3eYoz12OKwVkMfDOYhPsattf76+FBKxxqJMjTmYR4Gr/ZB13sZ0Pt1yqP/6hGge+sM6Np2B7q3TnjfgkeBTuY46mAwx4Dx52dPf/SAngmP/9pjQPfnRh/H5bGgD6IUAPM4YILoCB7m8cDQl+U+5gnA0PH3MU/UGBurYP7Yv+NJwIyO/Zkngz537I89BZjRsf8z6ONjf/WpoI+O/f7TQB8de/Z00OeO/T2fAczo2P8e9MHYu7jIoI+O/dZx0OeO/fIJYOaO/aGTwMwd++vADMce+fPu7dtnWpZyWSV5LW7ZPqOjV9i34campPv3/O+NzUhfEJ9b29nxfr/Y/b5vCTZf+C/170fuoeWb37c3tZ1iF3nAf21o96K0c/u7k1cbuvbf/o2mT7Vnk6Zoi9PO1sS6MhkT1oz+u5Bu182e/ocR/ks7lo692uO0Den9Cw3PrV+crsfmBu7o33Kwo12YTozHlqEf8GInHBqh73t7iDs7OsIV6Jqsbb3Gj7X157sOMdolzcJIHuW7O5yDuE8RfKGP38PQpx0Fv//M/f4a9+BA2yng34rfz/FVnXUpTs/FVXtO1YhhYv29O5zuSQ31ZR66t6PtWwrKvoHfRwuH3UXvfzSOjBBsXYhTcmSIwR6ma8t9hxj95UN9jt5vQIdrly/rH0Mc/Mk0BrlgQsxUe3T5mK0HDDCIU4L8W3f352TDChNF9dajNdgZ+SDP//x9VjfsMOD3dyy4391bl5PIU0bzKdQ8KoqkZW4WuGg19G6j9XlK1uSlqHktDI+LJ0DvNs5bPGwpUiiVZA1zlaH+QzsOi9irPKlqwWfoOqqktY9pxZjsd/dSqNfbab1amVRNVErLqrv/5Fbwnvw9Pr5iMjP2pzoGXrd98E7lM0HbBU8i2ebgmToZuJuk+KSJi7qMmF7hjH/B5tQFb7Vr4M+frhmsjV6XNhK79Wf6e3cH6L6Jntro3+vZ6DUQsVvhv7B1kPgvNEUb1Sa/R2Je5iydPrX0rEWtZsdPrZw8fvyESRVK2/Rnn/85bd3yJJaSnY5P6hxsind9dhzxtRweNiRZCaHqgulOWEm2p3unn2WlrSyKNLQJHbnky6qSirfSeJqsa1nbr77QyVrBG2aHx71mUkRN2ZakbU4aWua9X1v2+Z+VR00Wx7lgq2lE36kyHxcrVlVFU8usb9PJ5ROLzzm1sqxTXcV2purnt6dWtAWjmkxZL2+Lyqu5aFpjObzobkLzbl4QeRHjZR7JRCZj8mod/aMTdVEPvWvjwa5P30P6NK70mKVRaUP3ruiGok9Vp/OkT2sm2jKORSPJ+J2wPbpyRls=
*/