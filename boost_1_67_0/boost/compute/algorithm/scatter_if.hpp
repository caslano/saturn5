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