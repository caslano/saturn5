
#ifndef BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED
#define BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/config.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct integral_rank;

template<> struct integral_rank<bool>           : int_<1> {};
template<> struct integral_rank<signed char>    : int_<2> {};
template<> struct integral_rank<char>           : int_<3> {};
template<> struct integral_rank<unsigned char>  : int_<4> {};
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
template<> struct integral_rank<wchar_t>        : int_<5> {};
#endif
template<> struct integral_rank<short>          : int_<6> {};
template<> struct integral_rank<unsigned short> : int_<7> {};
template<> struct integral_rank<int>            : int_<8> {};
template<> struct integral_rank<unsigned int>   : int_<9> {};
template<> struct integral_rank<long>           : int_<10> {};
template<> struct integral_rank<unsigned long>  : int_<11> {};

#if defined(BOOST_HAS_LONG_LONG)
template<> struct integral_rank<long_long_type> : int_<12> {};
template<> struct integral_rank<ulong_long_type>: int_<13> {};
#endif

template< typename T1, typename T2 > struct largest_int
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
    : if_c< 
          ( integral_rank<T1>::value >= integral_rank<T2>::value )
        , T1
        , T2
        >
{
#else
{
    enum { rank1 = integral_rank<T1>::value };
    enum { rank2 = integral_rank<T2>::value };
    typedef typename if_c< (rank1 >= rank2),T1,T2 >::type type;
#endif
};

}}}

#endif // BOOST_MPL_AUX_LARGEST_INT_HPP_INCLUDED

/* largest_int.hpp
NDGfkp7Z/OJdjgiL81JZrfLIkmWC8gF+4ZMQYadDuKWCwOmf2n34G5XrWQmA0W2yP5eFAhA4P77p1t8Q4xC5S4denuuEPWqaK6hemZ63D7agDRHC+NBKoolDonqA7JRrP+SRefsuP1PT/6j2KslTG4FkY+eVrhGDdmQsO7kNDHhvykeH2whAtmGMU7l3sI4qu0nX/RYdZZPYBbBJg+B8e9VUdQp5caZqzYGTlkgut2kMcsJrb3TvkQlH4IvBiu9T3sjZFVRklc/4ja/Qre6hBPDNz4JJR11k2SH16fF5fsWfhFStHW/exVa2TJbKRmHTlt+s76+HEYDHh9TERZLrevrHk4w0MQ/X1cT9sS0tkDYoVhGTClJjKyz/Wf7aTPLrwV+9ibo14H947Pm0A3wCSmim5hzDctDQuMInY7vTHCXvX6DvY9HzHu+YK+x6OhxmBo8uJxmYmY6h+Z1TIzhx2W3OAX2pyqTvsYWNEbZz6udeA4dZZQxB9ShBGg+6jcxTXfHbO+eh/ZrFb4CA7qd81049PnXSj7hAncnduXptcWjO4JapL6mA5+hZenMyRw57o8RbA+Srb2iRXZ+WWumE7eMx3YaLoKOTtZzti/KHzqgmMsYDqu/YJUZK+4QONgfM6IOlBxVXOU7YTUtBrSIST7YwzKH/ZYCb7VygHCvcYQd2PRF3n4okAMRpVL5zF6r3HJh5Wd0EWPCQ8QPt
*/