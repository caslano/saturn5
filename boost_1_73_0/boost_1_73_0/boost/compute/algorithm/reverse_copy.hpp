//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class OutputIterator>
struct reverse_copy_kernel : public meta_kernel
{
    reverse_copy_kernel(Iterator first, Iterator last, OutputIterator result)
        : meta_kernel("reverse_copy")
    {
        // store size of the range
        m_size = detail::iterator_range_size(first, last);
        add_set_arg<const cl_uint>("size", static_cast<const cl_uint>(m_size));

        *this <<
            decl<cl_uint>("i") << " = get_global_id(0);\n" <<
            decl<cl_uint>("j") << " = size - get_global_id(0) - 1;\n" <<
            result[var<cl_uint>("j")] << "=" << first[var<cl_uint>("i")] << ";\n";
    }

    void exec(command_queue &queue)
    {
        exec_1d(queue, 0, m_size);
    }

    size_t m_size;
};

} // end detail namespace

/// Copies the elements in the range [\p first, \p last) in reversed
/// order to the range beginning at \p result.
///
/// Space complexity: \Omega(1)
///
/// \see reverse()
template<class InputIterator, class OutputIterator>
inline OutputIterator
reverse_copy(InputIterator first,
             InputIterator last,
             OutputIterator result,
             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    difference_type count = std::distance(first, last);

    detail::reverse_copy_kernel<InputIterator, OutputIterator>
        kernel(first, last, result);

    // run kernel
    kernel.exec(queue);

    // return iterator to the end of result
    return result + count;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REVERSE_COPY_HPP

/* reverse_copy.hpp
m1iLFS6EBJtxSEXO4exiehVN/g7gJhNx5nA2qgKTqSpPIGM1B81jLuoWpmTagkoRAfETYSxiVlYoGaJ5DpbrwjgYcoLlRgGrmcjZCs0xC5m1pfl9MIgrneNJBomKzSDuqAgzW/ROdYXeFGwDqrRgFVSGB0DyARQqESl9I0W4WVarXJgs2LmFBmUyUBoMz3MHh6qCm/YIHOaOrYAkoUTvhaUvo6QhazeZKvYEkVYHlFZaojmkBeUShcQHUMmE60a+IaKz4lhuKH/gyna+J6AkegX+cA7R3IcVM8IE8DFavLu4XMDH4Ww2nCyu4OIvGE6uHN4/0eQcY0OgVQ38ttTcoBcaRFHmgid7xn9gpi/eAd3nstRC2hRegf/qBIa4yjGgT37xwc/FiiTg1/DFyzvL90xWLPe9cP4OJsP3I6+BKVgLFLSoRbq/3F8Z2Vu3S4dU96DqHlbdW27ROn0Hh6mZKl0w21xMZcvKYijJGkMFg7/xf341uZjOo7kXnsJPQsZ5lXB4QzAD53KYvfVCU6JABD5u7J3nCOEMbmVMwzPfWQM/gDAMj/9Aila6r+jOcvRXNB41OgnJPx3HdB44nVWVphg/34clvwlmxL98ieqYzrc5l2ubfZ+J+gHCarbEQkCGmF4b8L8F8zT6Hov6
*/