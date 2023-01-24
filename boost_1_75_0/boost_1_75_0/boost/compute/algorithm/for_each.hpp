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
LJO1NRZrOBgfitWj3yq/4nDcwg/HxZH6nCsumHkw3AtaMNyTtlV7aFF2EAl3K3/Rxi1C0+GSfPMVKtNGp62Dlq3WdYbVqq1rJyABjbw6lEfyHW0FNOQZ15VWSa2xEr5qtXd7I+/a+VxEeWSEr6RVNe4Cimg1s/AcuLOt+hLqaCrCgLg8iHaHhJ7mxj+12mR04+/A12KX8sdEZvL3VCKTE67m18auTDG/mN/v7cqutfxa0ZUc/Deyy3vs8hf+8lV+fYFfn+RXqSsLr3tFIkkrdyv9ee3zeYF7+fXurloMdmN+rdlHIgQo5do53NaW5KaJHduSwOE0PpeL7LP5RutnNCbh1iBsl52YYBZIUxCeqll7aOYjb9t0xN9Lpy77GmxCmNjeYEXCkX08F9qbpTN4ZLN9edQ/HmbYJ1WTVJ5mOpXZHGhyQBrV9AlMgG+QpWsB7xdHAt7rg2A2Kvz5Bsoj3fPSgdmJGr7qE8YS0BlqyBxwJIGtgoVd2LzsTNDmhdHG03BypBPc9uKTBj4/bpRcAL9yC0ZK7Xf/DAuy5E4o8YfBSO679yLd1koGhru8snUeSY7tbg9efHuV5+px8L69qr37LbTp4Nn5cbiGby2Gmwbl52pE+ME5zVisgabH3Qw1VKF7Y14qAtBvxl2602PWmh5gaBo3CGv6Wtb0TpE33U9v+lmP1vQKarrag8nHzzSIfVrEwUDvBxqjDXV8
*/