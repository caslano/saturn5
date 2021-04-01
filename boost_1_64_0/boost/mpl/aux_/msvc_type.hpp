
#ifndef BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_type_impl
{
    template< typename T > struct result_
    {
        typedef typename T::type type;
    };
};

template<> struct msvc_type_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_type
    : msvc_type_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_type 
{
    typedef typename T::type type;
};

template<> struct msvc_type<int>
{
    typedef int type;
};

#endif

}}}

#endif // BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

/* msvc_type.hpp
AA67xinSIs1Wwpaxd3k/3oVPFsdi7WW2fROgF/oPgnXWyEJmKJOh1TElWVIBOejgGqXRScA/90A6aIbNXPCifBw8teCW43TpqQ0qJxuMjOivGRZmvpyv7Gi8LCpLursfRhTlReKyg0PYty7XYxsTcPJywJhdBE43EfHoV/kVvpjfKdo8yI8H04IPnhLxYM7w/XcC0hVaD+08vfUdwjy8JfXP3YyZ3s7oc8fT654pVYu8OEOhtm5fvamXRBmhbPkjoRVSD8kax/1mwq0FBvzRibWI5FIZsSW5pG+GAqOk03zCy0FGudxDgCpde7KdPRv8YDNL1SFiTmcK8Suq2AXCACso3i4zETdQ8G6n7sn1Z6eulkV2oAcS/ymNmMiYWhAq0eZkSQf7x7nFVwnWs7dbcc1JbnTYh+4Ej9StNLE9BbJ4f+GOQB8RnjKVAuYG4uRScusDdzvN2RQkG+29x+A310desmQwsHwgahnmPNtrXFun7Gs1zAY+5SunM24M2WEfwKm494Z5+m7X7evhaUgfwLMsgICoxGGqPboEB9y49XMiNNXz2SBpqi/ZGQ==
*/