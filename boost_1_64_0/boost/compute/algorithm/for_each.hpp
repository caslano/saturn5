//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FOR_EACH_HPP
#define BOOST_COMPUTE_ALGORITHM_FOR_EACH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Function>
struct for_each_kernel : public meta_kernel
{
    for_each_kernel(InputIterator first, InputIterator last, Function function)
        : meta_kernel("for_each")
    {
        // store range size
        m_count = detail::iterator_range_size(first, last);

        // setup kernel source
        *this << function(first[get_global_id(0)]) << ";\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_count);
    }

    size_t m_count;
};

} // end detail namespace

/// Calls \p function on each element in the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see transform()
template<class InputIterator, class UnaryFunction>
inline UnaryFunction for_each(InputIterator first,
                              InputIterator last,
                              UnaryFunction function,
                              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);

    detail::for_each_kernel<InputIterator, UnaryFunction> kernel(first, last, function);

    kernel.exec(queue);

    return function;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FOR_EACH_HPP

/* for_each.hpp
gTfDe+Gt8AG4G26Fz8Nt8GV4H/wEboKn4E5o0V92wQT4CGwOd8PWcA/sDR+HqfAJOBI+Ca+ET8Ep8Gk4A+6Ds+EzcDE8BJfBN+AK+Du4Br4L18E/wk1wPyyGB+Br8Hn4LnwBvgcPQlc47RyGwT/AlvB9eBE8DvvAD+EA+JG2y9k+mRU8pv0gCuZoP/iYcI3hJ7AF/Ax2hp9ruzwFh8EvtT98BWfCf2i/+AbeBb+Fe+Bp+IT6n4L7jBxD5DhyfU/6u6CsnNH5wVTYERbo82YWHAVnwxvgHHgTvBaugTfBh+ACuAsW8v/jcCF8Bt4AX4CL4CvwRngYLoYn4VL4BVwOPZkrghXgbTAWroAN4CrYDq6FQ+F6eBm8B46Hm+FkuANeD3fCRXA7XKbuq9R9DdwF18PdcCfcA/fBJ+B++BQ8DvfDM/AArOBGtgKrwFdgrNoT4GvwIvg67AXfgEPgq3As/D2cBP8AF8Cj8Hb4PtwM/wyfgn+Bb8KP4cfwJPwEfgpPSf3qt0e4XttRVVig7eh7T/+BrjD6DwyDPWA47AsrwEtgdXgZrATHwQg4FVaB02EknAWrQnm3hPMknr3f9nPNRwsX8QP22zKmyXxmHDwfToA9YBYcBSdB2Qeu87FseAOcCn8Fc+FSOA0uh1fD38Dp+jxbrPOTJfAv8Cb4CZyp85VZ8Gs4D/4DXg+/g3P0ubYMVoA3w0i4HEbD3+hzK8HS70swXtcQumCclu9tv3CFpQy3oZTh9vmF6xoQrpFlhzt2jnBfMf6wn+6ce+4G8RDNwfjOx/o8zz4jK/xiDA+lREyzi+0zs1ZiL8b49uEdzicd/HMC9uOdzi+5Jy+qB/QYHnLdMZmYTrgn9yAevzdixvJ7Nwy1b+/o1fbevWgekofgQexfYTphH4TJwRR5/DAnMV17kn/MV4SdC+vP8J7PtYzfibDvDOd+vwM9IW5LsB+GpzHHcduCPTyZ6xawrw3j2w/YFrdjMLmAsDAD+u8NHJRHWfldiPsys0+Q9JuG2XsF8duH2xGMb9/g6QLsMHom6WDO8DvZQ8JkwPq9MEmE53d3fqdhDvF72ybuJfTtMaw9i31zGN9ew7RZ9n7DFfxeRphizEbsh2Hg/sNDhDmBOelxv4ay4LYIk8TvjfBFzEndmzgZt6j2+HvIpGsNXEk5E3Hbd03wPYsncD8A2/ax9y4m9yEcxn8P41zszWDb2eQfswjTHfsK3LdgtmEfjf04LIAv4naa3ydh4hx7v2Onvufe8/iV7nscTbzDuCX2s/c/5sMVmL476EswDre5c5znmZ0MsifyxTn2vsjj/K59LeExbbGnwWD7JGfjnoP7Mkwx5iAm2N5J6xLKQNgifu+D9bGfgF1h1HXkDZOheytT+L0B5kD/fZa7cCvG7TS/X4RHsZ+E0XNx43cS9N+HmYI9GebDuBTqBPr2Ze7md3fcjsKxsED3aUbNIxy/izFF2PtiP7KKfZqY+qsjra6YVEwOZhFmA2Yv5gjmc0zUGvadYpIxmZglmC2YF9f89L2Z5X/lf+V/5X/lf+V//6q/X2z/P6uGfo79/w1ZHz2yJomI/infNuj06VybNYKW+I/C//NKDn+P8LkAb9EfsC/GPj8wx6Xf4zC8v+JO/oi/YY/IQ/sNH56ek8f6Zl9KZIZk7LUNz5LKfjEq2wy9tsHILBNcoWRsZZeBBZexhZZ1fSM6FCu806nd2ze/9Ocd83/4x8k1a14PJZMLJRv718tEVZaj94H7I99+nLKcCqqrLQI2gJVhG5U1XAirwh6wGkz0yMx+G2nFvRQZ6vxl1ePi1OFyEqN6W1RPS8lzldP0Pe009Ne/sgVT7NO3wu/ZvUrqVEk=
*/