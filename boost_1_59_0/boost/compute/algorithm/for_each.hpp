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
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
*/