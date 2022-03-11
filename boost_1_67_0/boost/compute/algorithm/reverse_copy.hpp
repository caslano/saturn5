//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class OutputIterator>
struct reverse_copy_kernel : public meta_kernel
{
    reverse_copy_kernel(Iterator first, Iterator last, OutputIterator result)
        : meta_kernel("reverse_copy")
    {
        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            result[var<cl_uint>("j")] << "=" << first[var<cl_uint>("i")] << ";\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size);
    }

    size_t m_size;
};

} // end detail namespace

/// Copies the elements in the range [\p first, \p last) in reversed
/// order to the range beginning at \p result.
///
/// Space complexity: \Omega(1)
///
/// \see reverse()
template<class InputIterator, class OutputIterator>
inline OutputIterator
reverse_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);

    detail::reverse_copy_kernel<InputIterator, OutputIterator>
        kernel(first, last, result);

    // run kernel
    kernel.exec(queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

/* reverse_copy.hpp
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
*/