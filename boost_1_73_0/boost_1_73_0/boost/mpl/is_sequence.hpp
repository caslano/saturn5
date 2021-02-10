
#ifndef BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   include <boost/mpl/aux_/msvc_is_class.hpp>
#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#   include <boost/type_traits/is_class.hpp>
#endif

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {

// agurt, 11/jun/03: 
// MSVC 6.5/7.0 fails if 'has_begin' is instantiated on a class type that has a
// 'begin' member that doesn't name a type; e.g. 'has_begin< std::vector<int> >'
// would fail; requiring 'T' to have _both_ 'tag' and 'begin' members workarounds
// the issue for most real-world cases
template< typename T > struct is_sequence_impl
    : and_<
          identity< aux::has_tag<T> >
        , identity< aux::has_begin<T> >
        >
{
};

} // namespace aux
        
template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : if_<
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          aux::msvc_is_class<T> 
#else
          boost::is_class<T> 
#endif
        , aux::is_sequence_impl<T>
        , bool_<false>
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#elif defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : bool_<false>
{
};

#else

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : not_< is_same< typename begin<T>::type, void_ > >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#endif // BOOST_MSVC

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct is_sequence<int>
    : bool_<false>
{
};
#endif

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, is_sequence)

}}

#endif // BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

/* is_sequence.hpp
luJn5dez1Fkj7JKt+TDer0DYDcIzCwMM4bZlFrtonhlo+ghPKNeDawQp4hi/khZOtlf+/07YYSBJDx/jjaEFQkuoYzw54a8B+/Q3UEsDBAoAAAAIAC1nSlLQ48n3fAAAAMgAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTYxMlVUBQABtkgkYE2OQQrDMAwE73qFIeeiDwhDyaWXPsIkCpi0MlhKS39fOaF1TmJ3B+2SsdqUlCNQlqX4WfnzLnXWCJtkaznc7tcRCHtCeMAwwBDGR2axi+aZgaZdOKFcX1wjSBG38Sdp4WRb5fN7wm4GkvT0Na0yNCI0RN3HIyD8V2Af/wVQSwMECgAAAAgALWdKUpZUtmG/AQAAEQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNjEzVVQFAAG2SCRghVNtb5swEP5uif9wShVViuaYpNWkIStS1r2kajtQYdO+enBJ0AxmcGmSf78DQlJ1H/YFsH333POCNWFDqWlwIXRerh2/fuNx7+qsWYhVkkTdA6raHY5Cyhr/7LhBkqk3SEKrS7FWfb+4ElcQY/2CtWzyDIWusbJHLsgMmR5UzaYzmPs+hA+e+GQIA4gNvYP5B/iCv/hk7sPs
*/