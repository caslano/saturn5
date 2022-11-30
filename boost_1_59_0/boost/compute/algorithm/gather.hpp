//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GATHER_HPP
#define BOOST_COMPUTE_ALGORITHM_GATHER_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class MapIterator, class OutputIterator>
class gather_kernel : public meta_kernel
{
public:
    gather_kernel() : meta_kernel("gather")
    {}

    void set_range(MapIterator first,
                   MapIterator last,
                   InputIterator input,
                   OutputIterator result)
    {
        m_count = iterator_range_size(first, last);

        *this <<
            "const uint i = get_global_id(0);\n" <<
            result[expr<uint_>("i")] << "=" << 
                input[first[expr<uint_>("i")]] << ";\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} // end detail namespace

/// Copies the elements using the indices from the range [\p first, \p last)
/// to the range beginning at \p result using the input values from the range
/// beginning at \p input.
///
/// Space complexity: \Omega(1)
///
/// \see scatter()
template<class InputIterator, class MapIterator, class OutputIterator>
inline void gather(MapIterator first,
                   MapIterator last,
                   InputIterator input,
                   OutputIterator result,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<MapIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    detail::gather_kernel<InputIterator, MapIterator, OutputIterator> kernel;
    
    kernel.set_range(first, last, input, result);
    kernel.exec(queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GATHER_HPP

/* gather.hpp
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
*/