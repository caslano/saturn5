
#ifndef BOOST_MPL_TRANSFORM_HPP_INCLUDED
#define BOOST_MPL_TRANSFORM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/pair_view.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux { 

template< 
      typename Seq
    , typename Op
    , typename In
    >
struct transform1_impl
    : fold< 
          Seq
        , typename In::state
        , bind2< typename lambda< typename In::operation >::type
            , _1
            , bind1< typename lambda<Op>::type, _2>
            > 
        >
{
};

template< 
      typename Seq
    , typename Op
    , typename In
    >
struct reverse_transform1_impl
    : reverse_fold< 
          Seq
        , typename In::state
        , bind2< typename lambda< typename In::operation >::type
            , _1
            , bind1< typename lambda<Op>::type, _2>
            > 
        >
{
};

template< 
      typename Seq1
    , typename Seq2
    , typename Op
    , typename In
    >
struct transform2_impl
    : fold< 
          pair_view<Seq1,Seq2>
        , typename In::state
        , bind2< typename lambda< typename In::operation >::type
            , _1
            , bind2<
                  typename lambda<Op>::type
                , bind1<first<>,_2>
                , bind1<second<>,_2>
                >
            > 
        >
{
};

template< 
      typename Seq1
    , typename Seq2
    , typename Op
    , typename In
    >
struct reverse_transform2_impl
    : reverse_fold< 
          pair_view<Seq1,Seq2>
        , typename In::state
        , bind2< typename lambda< typename In::operation >::type
            , _1
            , bind2< typename lambda< Op >::type
                , bind1<first<>,_2>
                , bind1<second<>,_2>
                >
            > 
        >
{
};

} // namespace aux 

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, transform1)                    
BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, transform2)
    
#define AUX778076_TRANSFORM_DEF(name)                                   \
template<                                                               \
      typename BOOST_MPL_AUX_NA_PARAM(Seq1)                             \
    , typename BOOST_MPL_AUX_NA_PARAM(Seq2OrOperation)                  \
    , typename BOOST_MPL_AUX_NA_PARAM(OperationOrInserter)              \
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)                         \
    >                                                                   \
struct name                                                             \
{                                                                       \
    typedef typename eval_if<                                           \
          or_<                                                          \
              is_na<OperationOrInserter>                                \
            , is_lambda_expression< Seq2OrOperation >                   \
            , not_< is_sequence<Seq2OrOperation> >                      \
            >                                                           \
        , name##1<Seq1,Seq2OrOperation,OperationOrInserter>             \
        , name##2<Seq1,Seq2OrOperation,OperationOrInserter,Inserter>    \
        >::type type;                                                   \
};                                                                      \
BOOST_MPL_AUX_NA_SPEC(4, name)                                          \
/**/

AUX778076_TRANSFORM_DEF(transform)
AUX778076_TRANSFORM_DEF(reverse_transform)

#undef AUX778076_TRANSFORM_DEF

}}

#endif // BOOST_MPL_TRANSFORM_HPP_INCLUDED

/* transform.hpp
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
*/