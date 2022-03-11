
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