//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP
#define BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/iterator/zip_iterator.hpp>
#include <boost/compute/functional/detail/unpack.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the inner product of the elements in the range
/// [\p first1, \p last1) with the elements in the range beginning
/// at \p first2.
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when binary operator is recognized as associative: \Omega(n)
template<class InputIterator1, class InputIterator2, class T>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type input_type;

    ptrdiff_t n = std::distance(first1, last1);

    return ::boost::compute::accumulate(
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(first1, first2)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        ::boost::compute::make_transform_iterator(
            ::boost::compute::make_zip_iterator(
                boost::make_tuple(last1, first2 + n)
            ),
            detail::unpack(multiplies<input_type>())
        ),
        init,
        queue
    );
}

/// \overload
template<class InputIterator1,
         class InputIterator2,
         class T,
         class BinaryAccumulateFunction,
         class BinaryTransformFunction>
inline T inner_product(InputIterator1 first1,
                       InputIterator1 last1,
                       InputIterator2 first2,
                       T init,
                       BinaryAccumulateFunction accumulate_function,
                       BinaryTransformFunction transform_function,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    size_t count = detail::iterator_range_size(first1, last1);
    vector<value_type> result(count, queue.get_context());
    transform(first1,
              last1,
              first2,
              result.begin(),
              transform_function,
              queue);

    return ::boost::compute::accumulate(result.begin(),
                                        result.end(),
                                        init,
                                        accumulate_function,
                                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INNER_PRODUCT_HPP

/* inner_product.hpp
HI6EI+EoOBpmqIxvjMqGx6lMeDycrLLkafBsmAO7wELYFRapTLlKZcgr4CJYC6epzG86vBtmwofUXg9nwRfgRfCIypY/gRfDJtTzAhgHF8JEeClsD7NgZ5gNU2EuTIf5cCZcBBfCYnilypw3wpPJGLf9MtbWzTkC2VbnWJE5jof+csf8zrFfuuxxfefYr0T+uLNz7H+9DHJf59ivnRyyjrZ0EPMppsOLsVYGJhuzEbPjxbB8MvwL/8K/8C/8C/9O5/fVyP89OpzOzPr/lX7y/536rlCg70TZmN8l8V1gq/2tfvb8zAn+Z2wmqc6vRPluqmFJYZDVxs8/V/Xb2f79rQ642Wv1K6pK5M9E/Sa8UMLFswIgwshdHonnfeo05BNc25zRmW7suQ75Sh8SlutqAh7Ho5S5NrDMbHwILLN+K9awp17DLmeH2vlyyEkiVX5cr3KURzF/IB91gfkoz8lbgqTksirOLy6wQulf1HhdrGZG32GFkTX8VPwSxD7ZhE2WsL9P8sqHkvW793Pid6+Vwv/zMbr/QuO0lesnSgmWmft3Af5/Ef9S3seaS5gMCVOW5wmUrLKYVyVMLdeNtsZhOiE/SeN+bItgbSzhI2quij0/OjIiKTomrmm0LW+pSeBvua62PS3XoBtJj1XVybpuRM6HEbcMkZv4ZL9ridcNs07bUkrIe6Yy2SA6/9Ih9WrkXxnYqTvslY72la6HHher/OtSzB8Jt+PGgPsq39Od5UqWe6lhSaGPFcca6QSVZQc/S5W2o+G7mHUZT4t9Iu/cLtV/afZpmPtVL2HGIbFoqffYl06Ko96d9RV6LUKitnHnOX6ST3HLMPUn+XDUWZHqKfy51tljmE+os7SbGtbZAFNnjnFIw17D2pkp6uaynhO3gdRgTKi603gdTd1NFft3kcy59Nxdu+6Ste4mS5hbkUzGcsVmWn++tNpj966jeVfsUZJOc29/yK8qt0z7XST+PQmRaM65LRE3t18fqiCOLTfcKv4NwktfGkHb+zRa+9Jqb1eKHRsdGRfZOnRf0r6ZKelcSpmiSRs3k/8W2MfK/XtQ7FOlbyWTXiRux+K919vjYSP61+m0F+re0V7G+ta46LqIofrcGoD5s6e9bAtoL1WlAaNnkPFT6zVD4na290WJPd5v/K/UZ5r6cfUeVlNTrxsa8ZwKObaYZ0Slkf1sDO9d+rdlGKcrowolU7lUZFfz7xnSY2SHJhNvrO320zcmD/js9M+wPFOyt//UXieKbOlER/p4jcurT1bPUNM5nswj8XOeoTZCv2OPhmfDsfAcmAOHw0VwpNrx07Oc9DsvvBBOVfeZ8Hw4T+0LYQbMFrv9nb1W85Mo+XF+Z/dk38NEGAdbwbNgMmwBW8IEsdvymzpNr17TM/Ib/Z7eVuU9vWEZ7A/XwNEqX5iicoXZKj+Yr3KFQpUjFGn4CpUjVMMrIMa6En5X5QmPwjXmzEt9XutcoybgzMu2+t2/ncptOsB02EnlSylwOuwKL4Zd4KVqV7mJPs94Lkv6TrlJD5Uj9NRy94HDYF84QuUCo2A6nAb7a/pper8GwgI4SOV9Q+DlKl94TON9DDMtHW/hUM1HEzhe87EOp3h4Feyqcp8eKgfqrXbRdQkHqPuWRu7xibsi9Hf3vQ//b397P/Twl//9/fjDp/4Gr2dFce7Y/863+H18bz+COYHp9hLf4jHZL4W/wYd/4V/4F/6Ff+Ff+Bf+hX/hX/gX/oV/4d/X9fcVyf+Ll54h+X+2n/x/l8rCn8R09tgx7P9HcZAtRzGb/62ge/Q0bDdzXlY3sW9rsGc4zd6jp3H6mT3Do7zXs06113+4hFsv9iKTzvCT7u1vAwdIuKs=
*/