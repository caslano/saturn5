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
/7ULxmW7rcIbmpMC++S+B1BOOAfQlTvJJR3PqnCF5qQTeeTOw4ADq+bkYyQ7H7B/Z23d3JnwP1e126tIpNpXtVuq2ltl21ahMr3anW9C2PUPJ3ulcUAp+pLQI6kz8efLkhAXQBVfk2JoWhKKLDCI1sNxUkPT71AgI428BpO6yNMKPkahtQeD2gNu+qdqv4K1HqecO3BRDdcDguq8GR1qmm5H/R0GGJd9BR44otQKV3aaKXBGrdhEiXKeE+UEARnT5Ri0w7HN9vg8FAsVnoVTG/DXsuvwaLC+SMvkclEeZxMdNYs6ixua2UlvE4ONzcpDs5nWSfanZQJSgFk6s1cMtibZHptOMqaJSar95I6IKgbdYrwhWG4lSRTT6UcTSUX3nWJZSt0FbmkPHP2XE9VAy2fUNopWXrYTEblUJ8rla1A4Ln3j3HQFik83xqHwan3PIiDOrygKJWFywyKnY3/AplY6ge3EaORJLONhtZkezd8HvFgoEw28e1N+c2jB62j1J3hZ3U0oI/x4EImfZHxQFPqohIBezfJUOBGILP6AP9WzorUngMv2OPm2yU+voSmV56P6/ksR5VTl9LFaXTQ65/qSQIunsLootMVdQuK/GDdJzkamYBXBQegmFvrAWkIahXJWxL69lGLdJin/NAvsPJ3LewovS77kLz/WXs7AW7e0Hbi0nIDgv1upPAcIu0C1/6PWJISyVftHcI3s
*/