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