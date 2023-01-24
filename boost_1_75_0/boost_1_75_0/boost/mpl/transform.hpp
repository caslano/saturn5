
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
iGd9CrB9b9YNsiE2J2XVbUu2I36iPv+si2sbbfGhbHfU5liv07WhYn2jgRU3QTNoLv43fjG/kp5DSj2/Eun8OyZrKwQ33NlZersjhFkea0WcEpAwSa4vD0/wBGR8vENvJP4n3hsqOEUA3OJxMZ4mABLgdrF0z4Fe9xKKPh9pgnOdrFGSZkgHmMsZmXBJLMqpVUshfJED+foGr17e+kWUCOjRa6YisfueN6na8IfvKn4sdLd0e3U/dSOlu/uWSz/tJ8xDhaG2xX6JiIUjhah0l+5Wjq9qf7TQk9zfzARQtrRZZrN25ZYLKVhTet33DlIWZuOKzsYGaihnJeaJin+53kRiipWkkU0uHJER5USCNZhH67oU07ogEvFqdLI9d2aJnJMGZhTMaXl9SZcN3RLouTFvfX2A0/45BgScjuUlXxbE6d7k1L75b51nvwl5YEjtbAu5CxNs/vE96bw40IjbshcocIkP5n+rJKRdGo+FRd8damgdX8NUPZWGQregPbJ9GYFja13kekK0TMl/3kDJUXAMgmHQOBi7PXG838DuJBLATiP2yF/VPaJk35564WuDh+wLf5wzhOkaB7+rx2oOn3/broIp/tB+lwJfjWiE1E7SHD2/2d3ZhWMFrw13+qMiYOldNdIiwhLWlF2+W/fpjyWEJQTSHzHd6N30G8bvIDHdllv0W5ZbBN/eO7I4thX7cLfrzl3l32FQYQ6w
*/