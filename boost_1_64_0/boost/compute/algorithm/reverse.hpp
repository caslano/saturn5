//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator>
struct reverse_kernel : public meta_kernel
{
    reverse_kernel(Iterator first, Iterator last)
        : meta_kernel("reverse")
    {
        typedef typename std::iterator_traits<Iterator>::value_type value_type;

        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            decl<value_type>("tmp") << "=" << first[var<cl_uint>("i")] << ";\n" <<
            first[var<cl_uint>("i")] << "=" << first[var<cl_uint>("j")] << ";\n" <<
            first[var<cl_uint>("j")] << "= tmp;\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size / 2);
    }

    size_t m_size;
};

} // end detail namespace

/// Reverses the elements in the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see reverse_copy()
template<class Iterator>
inline void reverse(Iterator first,
                    Iterator last,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count < 2){
        return;
    }

    detail::reverse_kernel<Iterator> kernel(first, last);

    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_HPP

/* reverse.hpp
FTHlrb964GsWj2oPye5jkstuljFH97pAY/eREFCffPSyNT5W8Sj4l+6Sa6e7Hb1paUwsuj7IiPGSWdvr7FzIjV8WHF0b20F9HBhnDaPmX8FT4N3+31KaJtJtLXj2iAAjMVl/5Lhi0dUzgbUb+tr7BqmLxNeprzU2roPBoQYFVVKF02Boukav6YD/z6661kG+W7b6lSQzXwKSG3t3Ub0e1JD23jdIwKoXMAyX3u6ymkQJKA7/0O5W4DLCbmdLAaEE3+1/S4vewh+0zlpqGAU3u0F6kEsU72Av8uFM0uPSfVfzGiiBokv24qTjxis7848ZsEh0lOESocbTYLDwmayq0CZjUIpf9zxArLPfu3kpJz1cjaMRmCy/jEquw4jF6omcuFfuzdFX6nMsYO3SDxSxwBxxIOu3VbykHbubopPXh0yQAjFD9paarF7UQ0JroBjBUJqDtjlIMGmkm+YkEyNW2TkI2r3v88rrXletNqVzlXNkARU+lbLjukv6cMFXDBrlnkunW6+aq3VLGPNQYLIY7xab0014EXW2+zIN7I4GFrBxwgqxiTRRve9fQA==
*/