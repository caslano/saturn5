
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
NUXrNjUmR7ZRaxMeBtt+tXlNiQDrEIUdWGvZvWRv7AnRdS/80JB+v4MIafcYiZXuoL3vsLpTSiPb0/QSwKyoZ4taZHpUIRy/zLO1tM5CNhtfIzoXT5qhfJKFAHYEbEUrLJxZWCGc/j20iRby/VlYYHfRwHK+/AgxSYCRzh0k/+UU/215XhHZtDhxyF2myOS0vMCXJvl2lRLCv9bdAUSGDviDXNd9Sez+UT8heaOVHKas2N+A+FfsHE4tAc35mu3n51PWjntRb3+Rf7kQpsFPALILVmHTJZ6mJlKIIx8r+6HK5PFdlWhQtlZ2Z/fhNTtGTLcC75mhFoBx2vpRh+Mg3wIZhC4ggpS+CZExHWmbE792yfgZAAQYsKWzH63O5Bhnc4mat36D7smykbvZtkq6eU2/bbcmKirhSx3PP7Gf9lrFuCvAftRiJmTB4fkx9SnhptRJYZjQ9sLeBbjU0bFW0RCdaSk8kkWIqtdsd0nysqmA7Ukm50Xyqy2Cxb6LBAJbNHqQP8YoxQeT1j49XwuiEUV4tvKAZh3HHn1gwAAHBhjY3tiPlDLf0fHTiQ==
*/