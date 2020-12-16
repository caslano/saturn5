//  Copyright (C) 2008-2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_LOCKFREE_FORWARD_HPP_INCLUDED
#define BOOST_LOCKFREE_FORWARD_HPP_INCLUDED


#ifndef BOOST_DOXYGEN_INVOKED

#include <cstddef> // size_t

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost    {
namespace lockfree {

// policies
template <bool IsFixedSized>
struct fixed_sized;

template <size_t Size>
struct capacity;

template <class Alloc>
struct allocator;


// data structures

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class queue;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class stack;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class spsc_queue;

}
}

#endif // BOOST_DOXYGEN_INVOKED

#endif // BOOST_LOCKFREE_FORWARD_HPP_INCLUDED

/* lockfree_forward.hpp
7WA5cHfiC7RNTpRnjNJTlxVnFxfFdg/kxPicyTE/P4xtlGN4ftzevG7qU9ZRjtqX28t0dE8R3EOeFzmmvix2MbH25ZwY+3KOoS+H18y+VqU1MtdbHM+PnO3YZ6M9P46UOv9V6nwfoo/YgTi+k1PxNepcbEsYHgSpf8wrhmsbk5rr4Ceq8m0NbSGy+a8Z1+9n82wKPI/O/wZDHSTUZi8ix3T3oe4NQ5kny3jiKrGV6WG6nui2MtqG4ghVbiJKRp/pWpBrtJfRa97nqvQCWiLB1N90+dbURX1dFyHbmRuJM4hfBdhvuAcbGGwi7n8ubBMRn21NuP4SGpn7Q8Wz5vqTnhC1HzxBOXM/EJkR/WABV3hTHfSDj+Q6MuU6WhLP5To6rotyHVxGWS39uasql2a6DmRG2tEUj7Bca+0fpNJ31HZRM7fh+sLvlrHJoczpCEyCAbGByom8vhhsoMJ9fbQq6/cdynGMz9B1NeyezM/QdbGNB3LWxTYekHxGO6cAnKbS38M+INE0RqC80c5J2wWer9K3qPSLlI2TU2+kyz38qEpfrNLrqXTe0C77p1Jdbwk17aTkOJs5zjkq3x/WYfSDJq7+jq2UutdvFhuoe4kdSJvG9rVEyafih65nQYOt2Ef1f9azj4rHPmq0so+6fsPTN+96/p6/nbVl5qEXLtxpat3ZR5ntneK3m/q/2EcteD66fVSq2PX0Fvuoo8Wupx8xRcodKuXqEw+Xcu9KufdgI1gJ94Tvw7bwY9gOfgQPkW2RK991ZrkvidyXRe4rIvdVkfumyH1D5LItcgkit5dB7gqR+6jIfUzkVojc1SJ3FTxMtkWujNX5vjDI/VzkfiFyN4jcL0XudyL3G9hdtrVcOd+eBrlrRO7TIvcZkbtW5K4Xuc/BHrL9HewRHveBfURuIrGLyM0mn0/srZLEzioD5sEOMF/kzA6PmeBkkdOUeL3IGS5yCmGy2Fm1hEVwPzharjcID7dk/Xax+xoAx8JsS9Zvh2fDYrGzOxtOEHuvi+Al8GJ4mdjTXSXbcr0yvjFfb385z1PlegfK9Z4m13u6liPjC5hpkHOsyAnbv/WDqfAEue6TRE5l+D0oY4YKuDPxZZEzUc5jsti9TYFZ8Dppx+thHzgVngiXwVPhjfAMsf8rgDPhWHgzvE7sAKeKHeBMOAfOhrfBxXA+fAPeC9+B98GP4QL4PVwIf4SL4a/wIZjI+S+BjeBSGIDL4FjPXs6zl6tDe7mPljWwGixvYHUkDiCeS5xLXEf8lbj7w7QVsexhz47OC17wghe84AUvbP+wPfT/I7JLgkVK/b/t+v9ZLv1/Xn1LhT+YANgXboH1+PjYuEr0//369MsN5qL7zw+Wcg6FRWVqLm5UipozLHHKBmSubvBqp8yh/rkkZfkbmX+/iVyZd5Q5+7FWa5kD9avyU/zdrUS+AS+3zvHtYPW2+1pz7A0c4zDmy6Q8Z7uXb6Q9i2OEZUuae66Rv4oLCmC6zFUOVPJ7+e+yfL69/YxF/Unm34CuMs9ZZoqc31X6l/7T+KVUQ9+59kR/fesafxPyu37/LMdNg1nquMP9e1tzraN8yVae72ef0lGwd9wTTlqxnWylEg9r+hFzlfVV/s/8VXOew/KLZE47AF9WZTrIHGxYxh5axtvISFcyXvE31DJKLCftddIaqbSP/M1k7pfzLS7IHVpWHKyaNz/iKTVvLts+K1ttJ1jpMp8aOuYYjrevlWTbVsBOUvOv5aq+SvPz87JHctLqmJ+RP1Md8wWOqeuUrl5MjtAxd3Ko8rzjOuchqnwl5QMq7Q1VJ4M7qespVn1R6nhaqB4tU71Wycu19pS+dqiSl+1P5Cv3SX7R19s=
*/