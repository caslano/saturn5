
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
kHldIgQQH1VPf/6KdnymWrbxYRnnkrN+m9L2z8A+TChIaEq4wjg+9fXbVLnhy8wz5a9afhncU6q/b+6Q3zd9ssv9rdwHuWA1gpfcC/POp1hnrIzl0BVdsQrWxKpYD6thE3TD1lgD22Mt7Iy1sQfWxb7ogYOwHh7CBpiKDfEKNsJfsTE+wSZYKDtliMWxGVbH5lgHW2JrbIXtsDX2xzY4EN9EC3rhKHwLZ2M7nIMdcA12xA3Y
*/