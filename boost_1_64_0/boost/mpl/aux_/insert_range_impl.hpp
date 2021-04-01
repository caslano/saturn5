
#ifndef BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/iter_push_front.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/same_traits.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'insert_range_impl' or the primary 
// 'insert_range' template


template< typename Tag >
struct insert_range_impl
{
    template<
          typename Sequence
        , typename Pos
        , typename Range
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : reverse_fold<
              joint_view<
                  iterator_range<typename begin<Sequence>::type,Pos>
                , joint_view<
                      Range
                    , iterator_range<Pos,typename end<Sequence>::type>
                    >
                >
            , typename clear<Sequence>::type
            , insert<_1, begin<_1>, _2>
            >
    {
#else
    {
        typedef typename reverse_fold<
                joint_view<
                    iterator_range<typename begin<Sequence>::type,Pos>
                  , joint_view<
                        Range
                      , iterator_range<Pos,typename end<Sequence>::type>
                      >
                  >
              , typename clear<Sequence>::type
              , insert<_1, begin<_1>, _2>
              >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(3,insert_range_impl)

}}

#endif // BOOST_MPL_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
5wDVO/WiZEAtiY2K0wYUjOxfc6Rh3GJsE4yB8PcBoVSKDgbgdjTSIUvG5ZwU3H3lALxxvNJT/qp+sO/EXeOy77V3XhgQCG71IZKyc1L4rgDO/inPz74DLXRvDQe61ZFXr+5ja//r3jdBbeUFx6I+qazUU8YtE3SoeIUD/sNJvm62Y37Nfc+iNLovuC8CgSjPVVzKH9o5lWVWWtL1UtgkbUuuQKp5Ulgr/IGtv74THZwqEP/Tq48mOCYB9Hhm3vgwhE4KKzzTqiy9NVgE5Ejacv89H0hv7yrQMGpE8JUAIE6/doV5TT/qyXamo3gE2KA5KP8lcMiNd0qt1Xb7COOn+gMrI3GdW/ekKVEYYbXOVR1t5xEqGn2z7R/dBMgERYixeHeCU5fwUntUWHXgOweAANEp2xo2nY0B5OmBo4M5pLYUvhhAy1VQ6YmrctviY45zV/JTGsSPw1hGP+23sD4xcV89hsMbjN/8umurxD0FhNoyerhEUNklL7S/byx83zB8oOCqAeOqBXp8DPA4voY2ZapawzTqj7+sVRYfneMaMyCwCE0lLywhZ23E6Q==
*/