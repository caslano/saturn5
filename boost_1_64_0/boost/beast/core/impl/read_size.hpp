//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_READ_SIZE_HPP
#define BOOST_BEAST_IMPL_READ_SIZE_HPP

#include <boost/asio/buffer.hpp>
#include <boost/assert.hpp>
#include <stdexcept>
#include <type_traits>

namespace boost {
namespace beast {

namespace detail {

template<class T, class = void>
struct has_read_size_helper : std::false_type {};

template<class T>
struct has_read_size_helper<T, decltype(
    read_size_helper(std::declval<T&>(), 512),
    (void)0)> : std::true_type
{
};

template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer,
    std::size_t max_size, std::true_type)
{
    return read_size_helper(buffer, max_size);
}

template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer,
    std::size_t max_size, std::false_type)
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    auto const size = buffer.size();
    auto const limit = buffer.max_size() - size;
    BOOST_ASSERT(size <= buffer.max_size());
    return std::min<std::size_t>(
        std::max<std::size_t>(512, buffer.capacity() - size),
        std::min<std::size_t>(max_size, limit));
}

} // detail

template<class DynamicBuffer>
std::size_t
read_size(
    DynamicBuffer& buffer, std::size_t max_size)
{
    return detail::read_size(buffer, max_size,
        detail::has_read_size_helper<DynamicBuffer>{});
}

template<class DynamicBuffer>
std::size_t
read_size_or_throw(
    DynamicBuffer& buffer, std::size_t max_size)
{
    auto const n = read_size(buffer, max_size);
    if(n == 0)
        BOOST_THROW_EXCEPTION(std::length_error{
            "buffer overflow"});
    return n;
}

} // beast
} // boost

#endif

/* read_size.hpp
ijoMV1JHYRvwIuAdwIuBd1NH4V7gJcAngNnAJ4EzqMNzoRo3ft8Bh1qM20KOWxkwgjqHQ4DoY0XvIn2KBX0x5SoWABOou9iNcQ99Hel7W9Dnk34+5SoKgD0Y9+i21JM+gvRG3ZYlbH8l0AmsIl2DHkj3Jem6APeTbhfp/sD73g2MYbwz8En62H0aeD5wD3Au8BlgBfBPwJXAvcDVwGcp3/Fn4Cbgc8Drgc8D64AvAB8A/gX4IrAeuJ86hgeoY3iYOoWfAv/G+zgA/JzXj/H6F/p1pudo3GsDF/M+WwGzeJ+/obzLA9QdehA4DPgQn6/fAicAH6bO66PAKcDfGcZvJ8tvZzF+y9mPK4HRwFXAtsDVpNfUvk/WAKHX+/UI6S/HpRTgOuBZwKuA44HrgcXADcClwI3Utd3E/t0MvBa4hf18LfBO4HXAPwBvAD4L3AqsB/4E+CpwG3Vsf0qd2pupU3sLMApt+7nefuqs9gDeBuxLndV04HbgUOCvgCOBdwLPB+7Q+w94F3Vo7wbOAd6jdE65t+L+rMZH53Q65+8MYAvghUA9fRYwCjgT2Inxbc7gdHx2fwj9AQSzbo+9To+9Pg/oBoamw2P0F+2ro7MRuAOBsi22Ojm++ji++jeie5NurW+jfRRl8D3tq2NDH9SUK4FMia0ezdMIlBsxyIuY/VVXGXxWr8sILP9B3RjKfPjowpygHoyV3Eatve9rX70WJVcxj3IUtQgJ6MORCDkIKxC2IexCaEBocQi6RwiZCCUIGxF2HPr+yFacivP/3BUF8wtyC3UJgJM6/0/E+X73jlg/3ef/7mJpik4/29+DBTTD4yuM+6lWvM8ohDXJ2Od6z/YLiypX5KKIgHwL47flcac7oYLnYXOAcWhTbbGUyzJVs+xs1DH/IMVzeFzioxw2PArm76+1J8/h9xIf6+ig7VR25Q7LtSuEF7DR5pwqW5XVV9kUflTi46TuXj78iOmSn/6FWM9vWfcZ2vVyLrMNed+Va10dw8EfiNH7H32d2cMd3uPfKV1tr8sYjA3AQ6ixsCO20YKHUOvPL5A24t7MZwwcUxflQHJ53p2p3zvqiTWPqWh2uD3K2fvd6yc0QznOnjK6WNpynKLS45X9zTSJZ1ra28xW+ZNkjNFfvr51KDNhzqffD+23SX8fSxRECI53Y2cP19e+41gLXx2ZZl8d/9f8ERs+iI0trf8+f+T2RP36K3fPvOej32/o1qvx8SdrOzru+OHyR5QNDPJBWll8R6VzHz+Y+80M7lvzNK6DXPtrKDM2k3TjKQc/AajnnQh8CjiJ++/JtGWTxe+YC4D6Ofp07o8xTLRVxWeX61GN2VaVyL13AY7id8yZ/I45i7abzgbWcl+891BUwL3xQ3f667xvKYzS6hB89sfNtjc27oupx96s++OmdNR34b7s9sr1hU3ulamPjnSvDnqz7pmhW94s++Zm2zNfHnFS++Z39X3w4Sgt+fD3Zz8c/oV/4V/49//yOyXf/5VFRYXNIP8fz+//unH6979eqHy+K76ANt57vXj+YN2xoaLJ86ZVFM/3Xt/tvV5UMN+tI/CogY9QZsNHqC9SfASdOAQ+AmUdbMpt8CmXNxJU2Z42Jzuty240lM0bDqncFTblasWqXHZwcOV6eCoxLWh/DqGnnJm5eSrp+VKuXmZQPBXkN/FULpX483ZyH8zfX8lxXCzxl+z4JszfV/FbciT+oubHN6HcxyxJf5Z8FNKDj0LbBOCFeHkgj6X4xoOR1/T1uUl5CQueSJ4FT6SkCZ5IQkvabCSf/g2OiWs+x0TNTTUsduNCmtOVXPTNEt8FSdZIu7EhTR/F77pJ4k/iHCfCbnxI01vxqbY=
*/