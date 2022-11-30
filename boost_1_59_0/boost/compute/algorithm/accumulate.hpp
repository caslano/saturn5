//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ACCUMULATE_HPP
#define BOOST_COMPUTE_ALGORITHM_ACCUMULATE_HPP

#include <boost/static_assert.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/algorithm/detail/serial_accumulate.hpp>
#include <boost/compute/container/array.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

// Space complexity O(1)
template<class InputIterator, class T, class BinaryFunction>
inline T generic_accumulate(InputIterator first,
                            InputIterator last,
                            T init,
                            BinaryFunction function,
                            command_queue &queue)
{
    const context &context = queue.get_context();

    size_t size = iterator_range_size(first, last);
    if(size == 0){
        return init;
    }

    // accumulate on device
    array<T, 1> device_result(context);
    detail::serial_accumulate(
        first, last, device_result.begin(), init, function, queue
    );

    // copy result to host
    T result;
    ::boost::compute::copy_n(device_result.begin(), 1, &result, queue);
    return result;
}

// returns true if we can use reduce() instead of accumulate() when
// accumulate() this is true when the function is commutative (such as
// addition of integers) and the initial value is the identity value
// for the operation (zero for addition, one for multiplication).
template<class T, class F>
inline bool can_accumulate_with_reduce(T init, F function)
{
    (void) init;
    (void) function;

    return false;
}

/// \internal_
#define BOOST_COMPUTE_DETAIL_DECLARE_CAN_ACCUMULATE_WITH_REDUCE(r, data, type) \
    inline bool can_accumulate_with_reduce(type init, plus<type>) \
    { \
        return init == type(0); \
    } \
    inline bool can_accumulate_with_reduce(type init, multiplies<type>) \
    { \
        return init == type(1); \
    }

BOOST_PP_SEQ_FOR_EACH(
    BOOST_COMPUTE_DETAIL_DECLARE_CAN_ACCUMULATE_WITH_REDUCE,
    _,
    (char_)(uchar_)(short_)(ushort_)(int_)(uint_)(long_)(ulong_)
)

template<class T>
inline bool can_accumulate_with_reduce(T init, min<T>)
{
    return init == (std::numeric_limits<T>::max)();
}

template<class T>
inline bool can_accumulate_with_reduce(T init, max<T>)
{
    return init == (std::numeric_limits<T>::min)();
}

#undef BOOST_COMPUTE_DETAIL_DECLARE_CAN_ACCUMULATE_WITH_REDUCE

template<class InputIterator, class T, class BinaryFunction>
inline T dispatch_accumulate(InputIterator first,
                             InputIterator last,
                             T init,
                             BinaryFunction function,
                             command_queue &queue)
{
    size_t size = iterator_range_size(first, last);
    if(size == 0){
        return init;
    }

    if(can_accumulate_with_reduce(init, function)){
        T result;
        reduce(first, last, &result, function, queue);
        return result;
    }
    else {
        return generic_accumulate(first, last, init, function, queue);
    }
}

} // end detail namespace

/// Returns the result of applying \p function to the elements in the
/// range [\p first, \p last) and \p init.
///
/// If no function is specified, \c plus will be used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param init initial value
/// \param function binary reduction function
/// \param queue command queue to perform the operation
///
/// \return the accumulated result value
///
/// In specific situations the call to \c accumulate() can be automatically
/// optimized to a call to the more efficient \c reduce() algorithm. This
/// occurs when the binary reduction function is recognized as associative
/// (such as the \c plus<int> function).
///
/// Note that because floating-point addition is not associative, calling
/// \c accumulate() with \c plus<float> results in a less efficient serial
/// reduction algorithm being executed. If a slight loss in precision is
/// acceptable, the more efficient parallel \c reduce() algorithm should be
/// used instead.
///
/// For example:
/// \code
/// // with vec = boost::compute::vector<int>
/// accumulate(vec.begin(), vec.end(), 0, plus<int>());   // fast
/// reduce(vec.begin(), vec.end(), &result, plus<int>()); // fast
///
/// // with vec = boost::compute::vector<float>
/// accumulate(vec.begin(), vec.end(), 0, plus<float>());   // slow
/// reduce(vec.begin(), vec.end(), &result, plus<float>()); // fast
/// \endcode
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when optimized to \c reduce(): \Omega(n)
///
/// \see reduce()
template<class InputIterator, class T, class BinaryFunction>
inline T accumulate(InputIterator first,
                    InputIterator last,
                    T init,
                    BinaryFunction function,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);

    return detail::dispatch_accumulate(first, last, init, function, queue);
}

/// \overload
template<class InputIterator, class T>
inline T accumulate(InputIterator first,
                    InputIterator last,
                    T init,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type IT;

    return detail::dispatch_accumulate(first, last, init, plus<IT>(), queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ACCUMULATE_HPP

/* accumulate.hpp
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
*/