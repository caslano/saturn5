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