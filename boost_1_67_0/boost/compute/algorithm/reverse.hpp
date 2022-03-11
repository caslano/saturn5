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
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
*/