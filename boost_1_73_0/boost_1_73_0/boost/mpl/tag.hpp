
#ifndef BOOST_MPL_TAG_HPP_INCLUDED
#define BOOST_MPL_TAG_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

namespace aux {
template< typename T > struct tag_impl
{
    typedef typename T::tag type;
};
}

template< typename T, typename Default = void_ > struct tag
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : if_< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type
{
#else
{
    typedef typename eval_if< 
          aux::has_tag<T>
        , aux::tag_impl<T>
        , Default
        >::type type;

#endif
};

}}

#endif // BOOST_MPL_TAG_HPP_INCLUDED

/* tag.hpp
5fomOKGEIwjJ1uAFbmx/EuBkEiYSTiIkRa+uI0wOke+IpdWSY/iUEBnDpxL+g3A04fuEY0Lku+fSCL8iTCc8Tki6yrF8RoiM5bOxmBCOI+xPmEMI2ZkQIp3e2whHEU4knIg5JywmvIOwjDAvRDq/dxJC/vMJ7ycsCJGxfxHhGsJiQtwpNZlwPaGHENmhKYRvEJYS7iGcSniAsIzwM8JyQnJJ8ALu6u8IpxFChipCpD0e49L2GKUwMZVK85g2TZU=
*/