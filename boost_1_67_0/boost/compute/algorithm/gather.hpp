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