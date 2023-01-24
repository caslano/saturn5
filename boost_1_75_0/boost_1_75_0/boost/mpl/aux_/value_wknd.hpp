
#ifndef BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

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

#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS) \
    || defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)

#   include <boost/mpl/int.hpp>

namespace boost { namespace mpl { namespace aux {
template< typename C_ > struct value_wknd
    : C_
{
};

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct value_wknd<int>
    : int_<1>
{
    using int_<1>::value;
};
#endif
}}}


#if !defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
#   define BOOST_MPL_AUX_VALUE_WKND(C) \
    ::BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE::aux::value_wknd< C > \
/**/
#    define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) BOOST_MPL_AUX_VALUE_WKND(C)
#else
#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) \
    ::boost::mpl::aux::value_wknd< C > \
/**/
#endif

#else // BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS

#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) C

#endif

#if BOOST_WORKAROUND(__EDG_VERSION__, <= 238)
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_STATIC_CAST(T, C::value) \
/**/
#else
#   define BOOST_MPL_AUX_NESTED_VALUE_WKND(T, C) \
    BOOST_MPL_AUX_VALUE_WKND(C)::value \
/**/
#endif


namespace boost { namespace mpl { namespace aux {

template< typename T > struct value_type_wknd
{
    typedef typename T::value_type type;
};

#if defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
template<> struct value_type_wknd<int>
{
    typedef int type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

/* value_wknd.hpp
MzwN8XPyihIkeQ/LhQL2Adct5fP6uKmJoqN3FpMeZ+PZAO59QW4ry7v29YybZXow2++P+EWVmhLne0w/K/JiGd+X/piS6OrOHNsdP1o9n31igqP+7HVwSSZXTHDJTEMuQWQOTOk57GHaeLuhNN8kMB+t8fIEe+E/zX/3QUHbWeOdV3p4ZFow+uwnpgmw1xm1h6bO98f9nf3bX03tjj9WYFHDiuPBdZw6CymJaX/MYV+gL6/0Dnz8+p6A9/MViCwr0F/YBrSQpbj5QLJhqZxqIEy5tLDSNFk77XLIRVjMNEOUlg5OUixaRzdUooMDWR0BmUZWaxrFojYPEOTM6yvHFb4DrBaHpcdQu7X3rmqYDw8/OIkfx+5BDd/8x7zu8DVAfy7p1da8WvhSY2fxJDSEHFtfhRlLCxR1X1CNjPKKz62O81Xu0Hxc+Xb1VCYfUHtNAPG6w7nb+Yk3ryT+fIv06PuyV9Vz5yzCzu4G746Wei1WH1gvf0bpC9+f9aa4cN7w3UDakNigShTpftWSvCPyRbqLTPeNIWIH0j2iKflX2stW5TmEDtwWjBaSFtQWghasxdcNiKe2HXQ7pIGkQZmBEz3lgTp4cVbmmbVTQY6TweftWhmZfwAu9Dfcesh7snuwNtjm97x3fAKhBZfr7KV9kGqPRyxUWHY+VFfM48EvSM1kfyrw7C3KH3DxNIpD9Ce0gme1msoI0ex80+pc
*/