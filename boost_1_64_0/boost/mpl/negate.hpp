
#ifndef BOOST_MPL_NEGATE_HPP_INCLUDED
#define BOOST_MPL_NEGATE_HPP_INCLUDED

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

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct negate_impl;

template< typename T > struct negate_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct negate
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : negate_impl<
          typename negate_tag<N>::type
        >::template apply<N>::type
#else
    : aux::msvc_eti_base< typename apply_wrap1<
          negate_impl< typename negate_tag<N>::type >
        , N
        >::type >::type
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, negate, (N))
};

BOOST_MPL_AUX_NA_SPEC(1, negate)


#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, T n > struct negate_wknd
{
    BOOST_STATIC_CONSTANT(T, value = -n);
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct negate_impl<integral_c_tag>
{
#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
    template< typename N > struct apply
        : aux::negate_wknd< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (-N::value) >
#endif    
    {
    };
};

}}

#endif // BOOST_MPL_NEGATE_HPP_INCLUDED

/* negate.hpp
0TXUB+NQcsjVvwOPdpsd6PPwBhcf0RnFr+/5IyfASNpJBYQUnob0cyOgqpEg5Sx68QnmaPffmKFy/yimyHvg/Tcd3u/B8UdcKJakhYjQ3ROQyYMV85pF48EACjM3Myzo+gj2VeypvVlYU+3NUX0EesKlZYyehyUO6YXJ6l2cYkokUvJdSPFbUnZ2WRICSFCCR7eZUMo+vHts5U8/3ejlxxVN3rRk8+ON9LImfntzmiG8kGZ+d1EKb97lz9mmXmTslxLI2ba3986vwPhHzu/lXyP2abBR2seDzDg/OdqdpENMLAnpMrVKAzoIwFrl4fHpMhetz++oK+5qNtye4i66gZnmSs09bk9JB65b39H8httTviNc3g5jhsrH6zKzabQ1dVoDogDsfE39NpSmcsk+f7ik2+TNrQAJls28O9/jKVJlrKgPY+Si9/sQdXvOExv6z3DlhnAV36cZplBuZZRQijfQhQQ/KTSGksknjHf5Zd8m8i6uSs3WFK5qoWun6cLmukqDszXRjeeUrfMmSzYyGUenZmsIVzXSodowxaIruzlbQ115I2W7z5qNbNFb76Vk2xyuIj9hc7i8u45v9dxCOW7mHMVkBBM46xPbfV1nXWvd2xR+331du6d1KH0zdl/XJt+6d1/Xyt/CdB1e5SZgd2nsTo3drrElX3ki75Hy1qImz/NDY+GSpnBlC7J26KxdOmunztqezNqmsjaEKxuRdYfO2qGzdumsncms7Srr5nAlXVFKoJJO6lDpKd1JN/yQG6FpaHlLuJj6gthrIjnRnXEJkhuGljeGi6nNG/lu2hJDN/qJSN48tHxLuJjatn8LD0GyNG+CxJcjx6/1evj1VN6VsstDu1LwBHIvtkfFiuAOklEsKu/Neb6oJNbcczgNx1RboERpEgeUaBIlqlAMoBi0VAoUI4liKJRuQsGmpG6gdCdRugmFnuml5oH4sL0l217TQxrg7/lnb1+fqZA82eM9XPku0jWYNQCiAMCa4beB32LESNeo5HBmtqmMbgASBPjm1fvLUP+PfNienob4323anhpJe2qIhTJNlgbEtTWV37GkMTXq8l1kb8y+cysAB26KnqtpyqrZSbFvupSeIimtLMeVcTYwrWRjSZjH3iAGJlzZGq7aQWDaigabqDGOTMHA9fadMIkaI8OKIaV06MQ/TaJEvka+jWbWpC1Fz40iCiyow8t7oVZdw1mAScY6h5f0MvHyDkoCjd7dbYgwJCglp6Rb3rOnxJzyLrwDHKOsOcWd0LMocGj0iJIWFjVJiz5HBt5f1OfJHzx0e7icKifsJVIb4exJUoGk+JNL4znZldIs8dRmyTHz6MHHT5bp5OyhCUs7xVLbqeP7kkV1nWMxUaqtTNpu3t0Hx1leDacHvsuMiQLi2aUaSEoEJJEgX802yniGgD4lmpg8/zQF/i51eFIberdn+tmbTo75BMlmiLZMBHAxQLeqhqhhX5PRDp2H23ftOxhLj6K10zxdIkng2CH55EIhJ/BuM/F6gaf4ILzsfNMN9GCecKkVT6RCo8Fq+jDnONaCJjw/7zHx9kt/8f1zQ6mcYNMTw/1Gx0Vy5WbWFPqFdYWs281vofzgJkb5maAov2t79R0mgrJJ2+9UkLyvNb2dNySrln5uz5pvAtcsoi+lxtdk/l+Xu4x+0pK2/PzgFST+3877QrFPJkUjJ0f7qMjMEXrCWZCBKcUe4zfjsP+90np/yuXmy0i4hy8bPdTzBV4deLkM+3GxDTerx8std2LXUH9wJbfNZHWoqyJ7zToCkEHhPRo7hNIOyoHr6WvGrObGqBhjlH4Z14GpVnhZlrf4EqY17U9xM42VdWQKeyqcb5QDh+liOQg=
*/