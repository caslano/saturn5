
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
N8m8kRMtIrJpqr7FpnuLTtwRdFxM0S+GMskK0GGWFZckx1x4OWI9V8M+yAqa58sWZpDBrzNJs3IbubuGjucV8bPTyHtSGpF37vvvLpXcF0glb83nAZ8LlT6cSg8Wpv9ESr3vj1LvJarTv8FpljxG6YPVGTyzOl82X59VoYFBr9csBXbxs2n/QF32Z2N8Egf/+072Q7aeVbvBXT3nviG7eabNmfGXVRvsseb421aqVIni9TZMgCocZXGA3hiPR0cWE8sSB9zQXt8IFef5tpVnkW7hApRY4n1z0SJhQWdgOl7V4rnIrqjKuJ6YUZK8MwGRi0wxzSqOz6vQvkdl22gTPB+ScKnH9wVyzgXDoXouCF8UJOWYBlqupeOwmto5TtkXZo7XQcadtq4jFUMJ+FUoa/eP0+Ov+CJxeDKefN75tD9kc5Fra8aLPh3amUtj5njv6+h0//hkZw+fWuwCnSWYafjcIjFE8ymJ5lkeW2up4dvR+Z6NrGj/9iYupN5p+/qwm5JrfDUuEjI+m2HymBAMbPutPtbRaPBWUzc6OZ3Ybsf1MTU1XXHFENJ8rRWWAlbhZulF7YVcQwrttQCqreKOSM9AZMmS6HQhNFHVK8+KNP10jgAK0pQpV00rvKxkK2dccaYjjPyR6mQdnMFJ
*/