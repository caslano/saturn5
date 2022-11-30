
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
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
*/