//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/detail/reduce_by_key.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// The \c reduce_by_key() algorithm performs reduction for each contiguous
/// subsequence of values determinate by equivalent keys.
///
/// Returns a pair of iterators at the end of the ranges [\p keys_result, keys_result_last)
/// and [\p values_result, \p values_result_last).
///
/// If no function is specified, \c plus will be used.
/// If no predicate is specified, \c equal_to will be used.
///
/// \param keys_first the first key
/// \param keys_last the last key
/// \param values_first the first input value
/// \param keys_result iterator pointing to the key output
/// \param values_result iterator pointing to the reduced value output
/// \param function binary reduction function
/// \param predicate binary predicate which returns true only if two keys are equal
/// \param queue command queue to perform the operation
///
/// The \c reduce_by_key() algorithm assumes that the binary reduction function
/// is associative. When used with non-associative functions the result may
/// be non-deterministic and vary in precision. Notably this affects the
/// \c plus<float>() function as floating-point addition is not associative
/// and may produce slightly different results than a serial algorithm.
///
/// For example, to calculate the sum of the values for each key:
///
/// \snippet test/test_reduce_by_key.cpp reduce_by_key_int
///
/// Space complexity on GPUs: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce()
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              BinaryPredicate predicate,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);

    return detail::dispatch_reduce_by_key(keys_first, keys_last, values_first,
                                          keys_result, values_result,
                                          function, predicate,
                                          queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         function, equal_to<key_type>(),
                         queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<InputValueIterator>::value_type value_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         plus<value_type>(), equal_to<key_type>(),
                         queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

/* reduce_by_key.hpp
2rmP4BDYEh4Mp9VjntTTB/736kHaXnOm/0R94FuZI03atIuVjTkeMxNTtcmbN/XEE0888cQTTzzxxBNP/h75u/X/F5T4zeiTp4wp3i7n/x8cZ5l9mx117r8zpjGmA2Yj/puSa+YQDxw+uqzIn/PoCQWsu5Yx9ByZuxe7ziloeGIH5/aD821DnP46tzq5rFT9c93jm32Hw8L8y6waf0bxHXrXCGP0rlE9Zi52qM7XZLm2nnOfZY7MtUvZzD7LaHGjPOoW1I0nZTD606LD9jsdB7lW3ORaHXvl50a513vGbqbeTa1HqnPCRq5z9Y9c5+ofuc7xr73OCeNa57n/oDrfij3bF3nOwn3OJfKchfvcRKS5j+03Z7G95iA2y9zHruNWLz7xx2k3zbtnr8OPeWFzj8hzMe5zEJHnLNznOOo/9+Q+51X/uY/6zpFFmvOSOYXAc0bv3VjnnILotm8MW8IOcDeo8bhXIseL13hNNV4CrJYzRHy1jqO67S/Zionby4yLuo2J6lio+96RyOOfhMOMwEQY89Q9IpHHOVdiNmTUb1zzldXRrmObSU1izfjmdExwHJO4GOd+D7cxS/dxSucYZd3HJgPjkisZg9zqjUN64oknnnjiyX9WdtD3/+RxY/2f/3997T/fW2ZNYal+//fU79BMzBf4Vwa//8m3a2bW6IIiuR783b4X+R7VOJmu35tDgv6qD0XXnJ5QOj6QRm5YGo3CvnmHueZRWF6Q79C/Tpg/6l8vlbBFZZOsYNiMsLBTQ75fB+v3a04t36+5Lt+geWHfqon6XUqZcTNlNmtAG4V9/xab+IGyxcu1lYqblMF81yZh2vNtEme3mXPfuWkPv/vsuhN6JS67PKq1fq+YMkobI+5roOJhJkyAuMn7Nu/W8s4b97X3HuuJJ5544oknnnjiiSeeeLIDv/8nFZbkb5f5/wODuv9lHkqoZYnBfIb/JSHf/yQzuajEqnXPduCbdAFmpHyT/vD81Z+tmnvDtUeOeu7s2E1VX9R/P9n2mkuMMGer38haXhjr8o3chG9iPxNgDGwOU+CyzjJ3xnyYzGsxPwX3qZknmuh9M3viiSeeeOKJJ5544oknnvznZAd9/3Ng+vaZ/88Omf+fH2OJbKYQ6XAF/Aj/uDjz/T+20J91Heb/a+L01XNMuBqxN4q63NpoP+BraPXQ803WinvL6JHoZrqf2B9hDkPT1P2YjXZXK9030nqNE3sKo2Ksp6N2DV9PYM4/GSzpXOK7ili6xkCvgfN5JEwgrxST1/vETrI/9UVcg2DS6Cn5HI59kNgf9V1DPmniFkh3N5NujN3SPsUXI9edEvX2H9Yv9GCIJAMeIPGejN5CvKFc9TlozPoKDiXeVF+C1ZwyF1HmBtEx1rHRuxodRpuaBs+WGWauMYO61nOYxF4dVck1Vvl+xd0fD48E3NFgf6QVI9fZScIHrr+1Xr+j/m2td2cZMh1rLDR/NIpRrrUBO72og93QOpt0UinP2ZiDSOsm0upFeS6jPNp3/rBuIyMszfX1TLOxpEkf1f6RBE+X+GN8h1pRvkA+WWH5bKpnPrfX6BCbUlCOHo+aNtW6THWpyzjfztrPYq0io18qW9qkod3SWq1urEwRtx+5j9fRdgPQOVUjLcS9pZ1uLaVP444N0TQ60nsSKdNCYhq9mqLrjuYyZ1q9Td8BnLK0J7pQSuxE1Rm3XK47yjfBms4ZQbOtRO3/H0r4z+090eCzu/2MOVvoOMmz0j6MnKYxOvYZfao/5cy3W3BtpEmY7Hjp31E9eZqcxg6HHnYnq8Lew1eTNok3Ex2ZuKahR+aUkDotnVSsbXcdbCB5NSblT805e6Hls0KeA4slzxI=
*/