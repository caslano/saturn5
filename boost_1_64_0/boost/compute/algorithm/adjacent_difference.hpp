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
YrLI5Fjp4fYK2gepDRuuhgqyzBouMzTdDtSl2z9e5WGs6gPY6pA0YbkXM7ZLXjkmebWNzx/V8Xn/VL7uyl3+esq1l6cUY+xyVNlcYzN3QsKp7tmudk5lq3HOkjg1xPmnhDu6P+1yh+3ZwbAzDUTX3CFOaGy/lvAbEva4F7ra6Di9xhkaGqd/TWS6uMvUfm+WpBPqx1PleVnS0BRWh1Z/2UvHPcnVUfMS/VuQMiBYp4T5awBh/o2sY2Nj0FXS/Kurn6uzFVx7ZpMnUNeb8Vfjr8FXN2v/lVRAPcs1Q+E5GvZgu/eUXM/KmT5zyBBLjz0aOkbyxOPY/ebYKAnfaML5Em4y4XMlXGLCIyU82YRHONmd2NujbU0cqd8IuxN//Wm/rG10X6ol7nf4LPwRPA8kc47tbbSiurG+sqS8yaGdqnx/YxvS9hx/+Ms8z2eYtuDStqD9tMbpa+oxSeJ8jWfFHda/L+H9uabRF+q3NV4fiTeHcILE+wZ1G7BL/bfEC/UDVRInZMu6grAlcR6npSZGvpOYPukCkSm3uvKf7mMibWp3mrKZNiKx6o3yIEx5hNYy0n7f3K+pu3/L8eD9YA8k+RJ5W39zbXtL3GfVFmAzfjdnNuRF1CU/KZH16NXn83Mi24S1DrWJ1/rVNDzRz7X2BQ/I+TmkmRTa18ojdjTir+Pvz5xGvxt+f2M7BgQn6e/TaHySPy+Dbfcn78jlsd8fVLavY9+p58Pen8v5DZalYcz7cleROVvbo8aRNhIeh0KWiKH3Z+/g0BpOs0w8r+M7cd/BJ30n1veTU/Zr02K8g6gNkr3/8Nrei/W+9b1kvjluuzdjw+bSc+TPVmeb9O1jstbZufh1fhu13Kg6q3foW1S2p5SDT36H2Asp1I/o+a6mLV6nv5n6LqH1XF+1upz86npxV+dqPeu7RKVJx/ldYqumG/4uMew02nTwXYJ7ISz3ErGOvOTVVo7YlIkr1XKch8+gzBdFtP2qGrELj+xzze/vOpEfz5tZkpavpsERe1mZZ0LPe035rpLwNH//YNpgSTNsbdVW3db3SVlE37exo6UPEfclve+92qftOdt+30xmiNV2kLPn/asS3sGaLy7Hd5QfiMw661Ly0Ztvgw1cL598bMEnDElyJ2QlJaW2TUxNSOU7oW1SWBnoWnr6W/Ga6fdOz54wvP6ndwoI5uj3Uzd8Fc9RQcRz5Gt0fI5UNiew/lZa9HOk58393KBtO7cFeQ7WJ+lr27a34+2dY/cHL/az30ddeWmZw30gG9kfVBkb4AvkvL0/+BfhqP6AONUw2B+82S+qPyCdk/cH7/WL7g8aTqOe7f0B9xLVH5DXiHJM9lri+mt7yMG387+3RfQH9c6/hSqb4/hbqOf1XSz6t7DYpNFFv7Vj//bN8su18Lcsv5V+y8hTrN8yjjf/tyz4rsznqrjV+mctviN/ZA+JKvNGn/O7MvL2/S8nSngu6zi5HPvtQpG5CP1JSrCdk47uU2nKXq5s2ud4Od9VwsVGvqee5y1PwljGm3dmyqO+gfUvQ2tIjhGZGda5+lxUmXS6WV4Tr7ahsrwuGJW4k9LZc4EnQ2X5T+cxmHq+5gP8bkb+fhSY+pT7V/1K8L05dE+qX9HjtjzLe/XcIQ7v1VmWOA8PeReYBL/DA1Jwlr3eL6urIq2Yda6yPc13/EIJv+H6K1fS/tjej5k43cw31aUSft31F/IWqx/LgPNF5i3XMb6FtB/TdDIdf++q5Pwrrpf41+ld9JhfhjS9+m10XMKdXOOsIdjsNnFnHOfIfjm+3VWAxfRmpB/mm2uqq31YupfVsWNpqI8V+bSY8z2WyLnXXBH9r/nuWynnf+P6hdXGlj4=
*/