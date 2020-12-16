#ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED
#define BOOST_MP11_INTEGRAL_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/version.hpp>
#include <type_traits>
#include <cstddef>

namespace boost
{
namespace mp11
{

// mp_bool
template<bool B> using mp_bool = std::integral_constant<bool, B>;

using mp_true = mp_bool<true>;
using mp_false = mp_bool<false>;

// mp_to_bool
template<class T> using mp_to_bool = mp_bool<static_cast<bool>( T::value )>;

// mp_not<T>
template<class T> using mp_not = mp_bool< !T::value >;

// mp_int
template<int I> using mp_int = std::integral_constant<int, I>;

// mp_size_t
template<std::size_t N> using mp_size_t = std::integral_constant<std::size_t, N>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_INTEGRAL_HPP_INCLUDED

/* integral.hpp
Q/89WOijqGA0ghc63KyA5kYX50NDBKHfN52EfjB8xWidN/WHJ7vArTjoUhz2XYr+I+FjhT+Xb/ml82OXg+L141PqDf34juEd1Y+/gLYXPj4D9ePBJ6TUj5v6d0A/PsWXyP/VaLN9IBnknEUD0ym8qj61ASWkbCftcFX9JCghW+mGbFFH0Vs7LRoi8oAGeuIYVD/EmiFwivYCd8zrsmH/NyqeXn9lWMfecUEvId1INZKk0+1JQjdSDRGJ7gdi6C4fyJ7e+lHG23B80Tv7jd4ZR5pINy4XMrkJMxF6I/ir4snoengXJCpQWhYssFUP4eWzu0Vg0Bm4mk8+m8RBUGlLntW27DLG/wPF+P9ZwvH/Tev4O/v/PVC8L/MAjeM1+3+fWk/s3JmtqsX5D4KtaaZBj5wLjYxsbXqjSOjmvDuIwxy+naEz+FBngKV6P+YXPvBTqs6WevvW99vvN7Kt/UtbQ1FWBMa7haHofBX7xFtnwFdMtfuxWa1WpVeo0m/4qq7DSouj6SLdRaQWqOxsrCxrAJtcccJegFE0+c4w9fmYiQqLGSCNM1gaMfkiTJ5corMN1nMGXP7jRgYVXD4sb6dpZq7qtAYHDg7FKmsj4KrHUEGCin7C5NDRuWV9go6Y/yDx5v/lXQJIFeU/fSipsmZih1YVgZmjSj7fyjQdpOk05Pq88U0x/KxpcBms8Eb2B+QaZ/KiGmGiWi3LDSgj8JWGoY7PQSDG7aqREC7RnzVe59Q2673r1tbG1Gl1Dto6qFJW3rI96ZmzLC/oDgzMLlCrcQ1iwUA2R+wGDwfhQ1xbmc0P+QwPTtSbKuamxINFvCu0xCdRJA4cInI+WQs8gIrnYvfFQMRqR2qBfclJCfcsZwbLoFvZarB5Yb7xOQhmnpZ3C4wQBR//EbYab6RLYJTIcQw/wqJpaSSHFvi9YsvtaYG+jrj+zQH925xC7t/ytWwCBfADX0WgD/wIpoUDtFCcH+ivk+kkMssKY8jMYBNWkMWY08LxRfFrOZbtNhrrFG0ZqYvuIoK7GDCOfotHCc2NxDxuypqN7ONKu60iJ6ZVrDf187OERK0n32hoWbu5/LDAiHhudAVu3L8Hc2MM1t0RPpfX4gIj4+p+CUdLpW/v43Or18G9FO4av1tdCfcXcJdDb+PNdquPwO9N8H2lirqXMxMulzszzZNp54Voe9tLwQ/n8v8v2VeC+QT+2qL5xCViPhEU84mjyVCwD564ZR69CrhFiSEn0zTkRFRuN4APXccNgwjoo5OHpDB5vtRoXDvz8Tlge6WfiHb14VpfFNUOVQmehoM/aKCAh7F/wgxc51+GHgLY1U8lxjq0TX+1aVejv0JlkPor7GBEfzV/K+qvNuc9jdUb4izLEj89cKZGCWUYmIKZT4SW/AxnB8eLHSkaOD6+nR8Dz0vDIagIuCosjtH5u+CCm85CiLcz9nRss3Y+9Q64RY5Ug2CQnj66p8UZQccuY/4HY3H4C/gAxxJHxNBqkEdTnw/9ugNKfAdAHj5Nt0geljfbl2D/+mugDWv+Ok1uunxgAxlYiQNBHb6eycFy4O7QXdgSbo6pS3eC2PYOfKDHvJJi+jkmjcMC/9udyUfQ1Y3WqVEaXtwZ2qgfddH0phUM0MK7pBveLw80cLxWOg7dhWP0he8zvM+znsyqYneVI+SEw/kQ6TwA8E5v1SF8ACz6wbJhz5u+37Zib8LjDP6xVy2opAEv5g3S4EUVTIuIZnWY86JMqi2Qp23/bOE9yjRZHIaN6co9URbZOT298/BlK6ja+Mg7gJ3aZXK4cHHnjvTT9rf31neeYF46jFmdTbR0ArqLO/9yL21+s8eKhPObW6zPb/Jp/r8XnQ8=
*/