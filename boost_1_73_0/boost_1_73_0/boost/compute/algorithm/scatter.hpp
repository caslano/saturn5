//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SCATTER_HPP
#define BOOST_COMPUTE_ALGORITHM_SCATTER_HPP

#include <boost/static_assert.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class MapIterator, class OutputIterator>
class scatter_kernel : meta_kernel
{
public:
    scatter_kernel() : meta_kernel("scatter")
    {}

    void set_range(InputIterator first,
                   InputIterator last,
                   MapIterator map,
                   OutputIterator result)
    {
        m_count = iterator_range_size(first, last);
        m_input_offset = first.get_index();
        m_output_offset = result.get_index();

        m_input_offset_arg = add_arg<uint_>("input_offset");
        m_output_offset_arg = add_arg<uint_>("output_offset");

        *this <<
            "const uint i = get_global_id(0);\n" <<
            "uint i1 = " << map[expr<uint_>("i")] << 
                " + output_offset;\n" <<
            "uint i2 = i + input_offset;\n" <<
            result[expr<uint_>("i1")] << "=" << 
                first[expr<uint_>("i2")] << ";\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        set_arg(m_input_offset_arg, uint_(m_input_offset));
        set_arg(m_output_offset_arg, uint_(m_output_offset));

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
    size_t m_input_offset;    
    size_t m_input_offset_arg;    
    size_t m_output_offset;    
    size_t m_output_offset_arg;    
};

} // end detail namespace

/// Copies the elements from the range [\p first, \p last) to the range
/// beginning at \p result using the output indices from the range beginning
/// at \p map.
///
/// Space complexity: \Omega(1)
///
/// \see gather()
template<class InputIterator, class MapIterator, class OutputIterator>
inline void scatter(InputIterator first,
                    InputIterator last,
                    MapIterator map,
                    OutputIterator result,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::scatter_kernel<InputIterator, MapIterator, OutputIterator> kernel;
    
    kernel.set_range(first, last, map, result);
    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SCATTER_HPP

/* scatter.hpp
dQO21E2VQ8kfBBiRCfkQwtTcONAFRsD4ubQOYzZOahVjegFOmLVtwxAIXlkN/IHLiq8wHXdQOlfbd8Nh1pgKKxnmOrPDrKMiLt36oKobRLPmW9C1A6ehsSICso9grXNZ0DtShId1s6qkLaMdLEyo8qE2YEVVteHQVQobShCQtGxFZAk1opeO3qxWlrJtSr3eM0Ra20BFYxSmQ1rQLtdIfASNyoXx9p6ILkvLsqf8Oy3bYc9BK0QFg1EC02QAK26ljeDLdHk+v17Cl9FiMZotb2D+CUazmzbe39PZGWpDYlYD4mtthEUUBuS6rqTI95L/xElfngP1M103lZMpz/O0RD6x4a9h8AYuuclKVPbL0wEMKrkiU/g9fhv/1vt+yVXDqwGLk3OYjS4n7PmAJ4BfiBbB7RbaQ2wAB2+KnbYW1ejDJDez+VUyTdgvUmVVkwt4T0GD9MoPjI2vFxeXmcYHzyY78s/hRTgPZxHQIbyg9O3R8Z8s5rnPeDZJxovp1XI6n7FRnluEZR0acZMfAiZdtJAdz+7jIIWiURlNE2S8qmAj8c+a3wvmx+22mPah3BZXqGbljK58NFuLTBbYZTLs4UO7mLEvJc37AXEYFMsNEuZ9OJFfAhlXSjs/GvR13VgHeMBwBimHJ80nwokp
*/