/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_UNIT_ELEMENT_HPP_JOFA_080912
#define BOOST_ICL_TYPE_TRAITS_UNIT_ELEMENT_HPP_JOFA_080912

#include <string>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/succ_pred.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct unit_element{ static Type value(); };

    template<> inline bool   unit_element<bool>::value()   { return true;}
    template<> inline float  unit_element<float>::value()  { return 1.0; }
    template<> inline double unit_element<double>::value() { return 1.0; }
    template<> inline long double unit_element<long double>::value() 
                                                           { return 1.0; }
    
    // Smallest 'visible' string that is greater than the empty string.
    template <>    
    inline std::string unit_element<std::string>::value()
    { return std::string(" "); }

    template <class Type> 
    inline Type unit_element<Type>::value()
    { return icl::succ(identity_element<Type>::value()); }

}} // namespace boost icl

#endif



/* unit_element.hpp
bhynPuW4l8jD8vBeDv8NKhFz42dWiXX4nU980+j6dHgvZKJrvfk6k4/Nf6RaftI9nb/qyX2RLb+NJVeujM5lVy20/zWuA98szLHnKulv/KLw7hY5+8wfo/2Qvj35oCrVdXL+YUcnsWwmxu06kVmj5rh2SUf7gfzqHsapBTl96ZItTsbcII/6s+Uz8d5q7uXTwv/dI9c6h/+jRX03L9e+3+P4tkq5LxaVY8XQ/p5v7u7wGxmZO8P7QK4lDKD/GC19T+qqLoTfVl1fP5FPyRoWvs/CGeIwpZg++JZPF4S4yMFeWfZ/Szlj3k/yp6aN3K2TO5nykI4/JxpXxlbjuve2PvuS6ZGmv6da9dxQ9bsvueYOmWKOdkACfR2f6FqC8zfpeEopvxg3ia7N9EUUkDVRDpG3uRN9yXtITg7NDf82mZwsUwP4YGq+OuWeUFout9vJcf6qzJEr/LXItXtG0VU+XC2/TzX3CTFoYf59/PUD7rJeI2NGuT6SvFvY/aV1DlmzUv8+11+JVVv47iJ+aeraBMcxOJ9+n/Rhe4I8MnZOqD3iXyreF8eS112uTqUj0p3fNZk8a4d/uv2xmPA3Eo7RCc+Q9aTrTXPNZ/8Me3o+jquQk3JvWkt7zr48Z6S5Uxy3kiPyYl6W/RfeUQlv1pq/abraWW7fOL4z3IfCd3zybEX4vJtq/RR5VuaYnsnd+UPMju/GrwXuQzHyyrw37LMfw3spbHvO9TOS1XE5d7182iXnzqpnL/uftn7uULEO+V5Op0S+4v/5w9jD5tvC9959ESMOUeYMELNccsP7cA305LPB5i2Uc735fkcRv7G9rEqNkb/HyHiSjlc4v5mPCsl+NlL9pVNdeAdJ3Aead38XaxszOtwTk/WXyr1E9wzrzsl0z3TtdXb9Rd+qno4H8WcPOVDJN2Evx/JT+G7VuLbkbu1HLzrldJQHji+y72daf9RgdVRsi1tqXW/UVWzon0nHM7Ux7fk9fG8kH+rFcy2fTcdANr+XEf7vFTU8Uf5be3GKHG5n/fAeEBs+jbY/9K/St/10uYy4QcZkqy3j7I9K+7AtP46VG+H3XXqtzGFDqXwIvx8Wq8XhXQg58o49OoVvrzFuVl/j2DR2sFiL1fd8Ws+WGzP5MIqfnN9Avxwy5keSZfx/e/GDa4Pkxa/J9uwAMeO/w9PduyrlaxV5CfzoPNb4c+m1NHz2ZeMuubk8Xh7wTZl1sslvk2l8jP3Lns5yOkEcXw3vVpH7hxw7UsLebPsk1boN8quKjGHqOhmfsbGyXL2otAfNeyp8H0TmTOPvny4ObCvpQ1b43dj8DXQfPcIe5oMzyT+tv32ebp9NFIvwPQ87BtKjqJMYj1XrjfmnIxlyaKu+3WXuteH7me5qhjj354fS8F0E/WeI2YFUvmBrNbnTMDLsZ7H4yZjnMtXGSvk+Jfwb++Jn3IvhXq2/e7j3kVln3BMjrV9GpnHZ8vEc18+y9p8V8sN594H8FPI8ma+q7Zsce3C0+CKlRB7G2Ce9xF7793BxHiYW7L0j+L/QfpZLXbXXudaoXB1IUFtxaaT8Cn6Xw4sdDw+/vfZix2A1lK3HJasPBfY+X9ybKF/Z1iSPP5LoEGv/qDPj6Vbm2vLp+pw/Zp1rw7NeNn+P4g/90fy/bKx1rH023892flB/v3b2dBHbtUudL9EuwmrHr/DTy/ZgkvGnk9UcU+hZTq8Pw+/ldJmZaB/p+yN8fhXz6gn2hTk/iulJxnxNn6fDe03GjKiha5x7zDhrj1FfjBlq3snqZkE3655OF7yRTK98e6JezOgyLNSPlvLRuOnhnVnte2K2Po1/wm+hhfQz9t4qNdH1teHzuVjvj3N9kns=
*/