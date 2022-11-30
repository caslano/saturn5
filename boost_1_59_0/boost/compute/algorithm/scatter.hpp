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
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
*/