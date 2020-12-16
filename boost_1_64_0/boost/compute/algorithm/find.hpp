//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) that equals \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator find(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::find_if(
                   first,
                   last,
                   _1 == value,
                   queue
               );
    }
    else {
        return ::boost::compute::find_if(
                   first,
                   last,
                   all(_1 == value),
                   queue
               );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_HPP

/* find.hpp
PI55VTXtn0vE78FztkG9j475kVM3vdar9FUobtSbuiWY9kpdBbSBZg29FxrthcibMmqRy6N+a79nmjYQ6tmm4Suad6RZYh9+tjmPxhkd9JmwWPx6OcdAHfNuEr8a5r1gvdhbOecA2l5miN/IUtexGftCz2uc3zMa6TpQ+c4G9dv2Mb/6o+chs00XwcPZ5K2ud+W7i9apL43GaucJJv6uoLIM6lPDNzTPve/F3kP9Nb6R15bqrPoBweQezjNXJA9m/Xd++frvX2z997Oy/vvKL3amjJ0x95U+FfIvfaG9Nep/d/13qPMivrHHL77tE4b4f7BE7iLrIjtjkK/K73YYBhH5XYcwNfR3Pr9r6u+n+V1Zf/fG6DpwXf/At/TAdeCqx9fDYbCG2uPhCNgcpsHz4EjYGY6C3nQxmu4lQdK9nHB14FiYAK+ETeBVsANMh11gBuwOszTdyZhiTXe8pOvUo8h6YUn3U9gQfgYT4LewDfwcij4k2At+BVPg13A4/AZeJuF96+tV/g4rBFlfP0/rZz4MhwugT09Wssa7X+I59WT9Xdfln4G14Hea74rEbwS/xy6DMvYp6p4PXXCG+l+r9l9BN7wNhsHbNfxqWAHeK3Zdn2+p7Blmar7CYVvN16VangF6vwfBq+BgqPWBHDd0fVyj8Wdrfcyx46nMlfBB4k3WeNnQDaf4xdt3lni5Gm+axsvTeMmYQxpvjMRznodwnu5vaAcvhefDIWofqXbV665yOtqEpmPrddd15LAqbAGrwTawuvaLpvBiGAPHwRowB8ZB6ZtwOYyHK2AtuAvWgXthffgUbAD3w4bwTZgA34VN4Ed6Hb2/KmvingW5vy00vy3hBTARXgRb2/Wtsh7iBanv6VrfM2AYLIBG/5rGGyvxnPrXOug+ks5aT120ni6AA2FXOBh2hyNgNzhK7Xo/Ve5B3gPvp64Dl3kfbAqbw2ZqbyF2O50NZ0knUdNppem01nSwkw52TeeI75u2yghIR+ZJBzUdHhlSz51hD3iBjjfd4VTYE4q+S3gr7A3XwL5wi/o/BFPgk3AAfAYOgvvhUHgQDoevwRHwDZgG01zMd+FVcAzMg1fA5TAD3gYnwDUwC+6FE+EzcJKWb7f5dsc1tZ7i4DaMPDK0nt6AFeDvYGV4GEbBj2FV+CasAX+v49wRHZff0fo9qvX6LkyEf4St4XvwfHhMx+v3YWf4AewK/6T1+hG8FP4FDtTr6vNHv6HRx4I8f3Zq/nfBMPgIjICPav4fg9XhbhgH92i6n/u+/eh3s8kB+rfvUD37d2r5V0HR1wxFXzPsBNfCPnA9HAI3wAx4N8yG98AceC/MV3uhn775++BtcBNcCTfDDfB+bT9b4WNwG3wKPqTtp1jbz4PwNXV/Q90PqztjhLi3grhr/9ZvC7BlkP5dU+uzDgyH9fR+19f73UDvd4L2p0awhdpVX7F+H5A4zHV+2jkGpzGFmt6jmt/68KSmN1XbbY7e91xYDebr/b5a79tyWB9Oh03gDG2nM/V+LoPt4C2wi4bvDq+BPeFsvc9z4FB4LRwD58EsOB9OhgtgLlwIp8Mb9H7fqPd5MbwdLtH7/Wt4n15/i15/u15fn1v6Hsq9C/Lc2qv1+SSsCJ+GkXAfjIGvaD28CmvC/TABHoCt4HOwLXxe++MLsLu691Z7CnwRDoC/hcPgyzBN079M0rf76zHN75VB+mtPfe4kw9qwN2wK+8ALYV99zvaDw2F/+GIZ9ukE01epOir/5Xt20D/5i+zbQYfkf/3eHXQ4/sft30krQr8hZg1mL+Yo5gym/m/Qv4jJxCzDbMMcxJzERN0aaSVhRmMWYTZiDmCOYazbIq1ETDImA1M=
*/