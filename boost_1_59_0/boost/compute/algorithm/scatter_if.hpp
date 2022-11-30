//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Pola <jakub.pola@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP

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

template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator, class Predicate>
class scatter_if_kernel : meta_kernel
{
public:
    scatter_if_kernel() : meta_kernel("scatter_if")
    {}

    void set_range(InputIterator first,
                   InputIterator last,
                   MapIterator map,
                   StencilIterator stencil,
                   OutputIterator result,
                   Predicate predicate)
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
        if_(predicate(stencil[expr<uint_>("i")])) << "\n" <<
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
/// at \p map if stencil is resolved to true. By default the predicate is
/// an identity
///
/// Space complexity: \Omega(1)
template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator,
         class Predicate>
inline void scatter_if(InputIterator first,
                       InputIterator last,
                       MapIterator map,
                       StencilIterator stencil,
                       OutputIterator result,
                       Predicate predicate,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<StencilIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::scatter_if_kernel<InputIterator, MapIterator, StencilIterator, OutputIterator, Predicate> kernel;

    kernel.set_range(first, last, map, stencil, result, predicate);
    kernel.exec(queue);
}

template<class InputIterator, class MapIterator, class StencilIterator, class OutputIterator>
inline void scatter_if(InputIterator first,
                       InputIterator last,
                       MapIterator map,
                       StencilIterator stencil,
                       OutputIterator result,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<StencilIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<StencilIterator>::value_type T;

    scatter_if(first, last, map, stencil, result, identity<T>(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SCATTER_IF_HPP

/* scatter_if.hpp
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
*/