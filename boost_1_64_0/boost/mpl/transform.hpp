
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
JD0vMVbYWfiStsMDFT0pZAjQioc535JbR9nhWWzriEux5gek54KAC7AB6FuQWpdyDEHVeoZ/SF6rg3arOaMj86+XogZ//qWLeK2Mcsk1HCTs93Mmxn9F8PDxBnT+NEijaC3KapyEWRX5+U0lhVoubqfZpZy9r6LRMiX1ZrJReHdu16QRGztt3G1dB9cGtxLtvHuZmYN1384ZHVX1MZvcev3PlcgvN25uOqo3Zyiy/tVzkcqUpK0uVdKGfDM+bfEOgGkxqKsSso2qjfh/CKKYAcbUVpMaqpgYOuRWXLkl0mm5vHqLVHUUgqz6ZirApLMGR0YbAZPNL6YO1HfHEve/liHZsAnktO5VA1Ado7NsPi7Hv3noL18Fe6nyiK8RGYGTEnStW0MlvbiTviG+37b54Z/zh/SIkYlqKKQzYaeqhB80HWCG0N8+2zIrSvzoNVJo7twziYKTUwNZ7B7hhbfh1nKqwRZUlYHfP6kOgPoB5T8oTT/GWeoFi4OC9p1+uUO0zBGsXthrcyxaWJK6M4bLfI0ERqehI1VHU7sOSnZTfuZ9lR+UIj0nLdu+/g==
*/