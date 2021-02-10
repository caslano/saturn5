//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP
#define BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
dispatch_adjacent_difference(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             BinaryFunction op,
                             command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, last);
    detail::meta_kernel k("adjacent_difference");

    k << "const uint i = get_global_id(0);\n"
      << "if(i == 0){\n"
      << "    " << result[k.var<uint_>("0")] << " = " << first[k.var<uint_>("0")] << ";\n"
      << "}\n"
      << "else {\n"
      << "    " << result[k.var<uint_>("i")] << " = "
      <<               op(first[k.var<uint_>("i")], first[k.var<uint_>("i-1")]) << ";\n"
      << "}\n";

    k.exec_1d(queue, 0, count, 1);

    return result + count;
}

} // end detail namespace

/// Stores the difference of each pair of consecutive values in the range
/// [\p first, \p last) to the range beginning at \p result. If \p op is not
/// provided, \c minus<T> is used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param result first element in the output range
/// \param op binary difference function
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when \p result == \p first: \Omega(n)
///
/// \see adjacent_find()
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    BinaryFunction op,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) {
        return result;
    }

    if (first == result) {
        vector<value_type> temp(detail::iterator_range_size(first, last),
                                queue.get_context());
        copy(first, last, temp.begin(), queue);

        return ::boost::compute::detail::dispatch_adjacent_difference(
            temp.begin(), temp.end(), result, op, queue
        );
    }
    else {
        return ::boost::compute::detail::dispatch_adjacent_difference(
            first, last, result, op, queue
        );
    }
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::adjacent_difference(
        first, last, result, ::boost::compute::minus<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

/* adjacent_difference.hpp
n55h3G24mE/OY8RKrsMpfklPT168fhW6EyqO0uwG0/HX6+gA8SHUnBKy4dw2xu5YxVA6XH9rIg2z9kLqoHxtTbepIfAMWoiQaUbMltPZPJtkUfoZ76QuVFcSLoLNvvTqT1HqWj6dIH4wsjxc4AhFLSzex2i9RYzj35mjKHvUq+vs8m4yX0xm0xd0B7Luf7FNgXtH0aqaHBicH6+qOTeq8yTKUEX97nGoNNGTFdo0QoVC7mMVXCec6k55tjRNxH1RkSVdsAG3+0CrEVpsqCHtmZjfBm7c6hai5eIoROjivg0GdmkUzYVzUm8ChsD0/vYWrZGaazvsMGMWKBDdSqUY/R/afxaqThc9mCXPTRLJpqFSCk9qx6a+huZr9BZpL2qcXV9jfJvNWOfPd/tEkHC7vNP80RItIWZFEk7F4ejFAeLoX1BLAwQKAAAACAAtZ0pSGN5G9b0HAABPEQAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9jdXJsX2dldGRhdGUuM1VUBQABtkgkYK1Xa3PqRhL9rl/RxX6IfSMLgd9sKrUEk2t2DaYsvFlXuYoM0gCTiJFKIxmTuj9+T88IMM69yU1V8ANp1I/pnnO6W8Fzgz78bR8vYHP0p5+p/Zvig++t0rjIfpFx
*/