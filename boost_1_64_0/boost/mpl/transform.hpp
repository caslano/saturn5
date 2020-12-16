
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
0fMDPW3f7+rqSE8PevrTczw9I+gZT08JPefQ8yt6ZtDjp2c+PVX03EbPGnoepOdxep6j52V63qDnXXo+pudzer6lx06Trj09mfT0pucYek6kZxQ9E+g5nZ4yes6lZxo9l9Ezix4/PRX0BOm5iZ5b6VlJzz30/JaeR+jZ8MGRl/P+r/70+jnqCmmP+kwW4+kTO8jQPTOrhT8Q70xazZ/9lVrN881jlUNyScIWzqUdgUCwtXt+Yjvksev/zBj/H1PnWP1/3KfBGkuAtTf6KbDqBDvbhP+P0ExTYneqPnh7ZZT59QTRHoDcns9ADs8bSNGwIyexs8pXOkmDFZXNn1fp9G0oPdi51vnL4P4fPMMin8kVnBWMsDQqIyyN9JPCheJmbm7p8t73muXhKjrf2SNZNouMhP3tUyxbvRaazjLv/3vj+meYHDD9M5x1xZH3z8Dnf5fH8c/gYSQd7/UQklby6R5WFe2fITXZ6p/hehN1gaDfY5PBggZXQcnBylSxCy0nui/kpoE2sCfgwhHjBp/VlYOJ5g08ARagJBYwZ6LxhM5KQAR3Dp4F5qQCvH+6APDiXHDWUJQOoDKTjow7h2bmvyfCH8FBR7P+CC5phT8CS6l3J7Lnv6bF9vx/uEzSz/SyxPb8d09s6fUaU/53WUvs+b/eInv+25uy53/jZUfInj/D+/mlVnivjANvTwVvQzS8DYHhGt6udsvoggLyJE+Hh69k2/z2eJVwP90auK300ImxuSnSE0Ez+6N1o+Pvvw6NiL+/slopOTBabVN0vHHf7Fh992uuSLxfS5mp4YmVh15wiT7PlNfTsJpMs/nZmv40G3lkuqstTf+NYvrP915O0/+Nc9WaOp0mPOz0TCWCCTv8U4Uw7h6VwXMDlYg8q3SefMoDuvQpPiWzGcL35IuRXKF0R/p61ulyFqpyztLlGA76dJ5u5uUlioz19vxOAzwLmXrpTE86KMYBqOXV3hNUPoL7EV3fAlXfx1NU1jkOeXdvahlsi04tNZYPUu7f+nqe0HkXqbwP6ryFlBfnWRNBeuHeziPzVmYoiTiohSqvRpcXVOWdo8s7IHTVTzpHMz6+Tl47KPCFo0x1pXuVw+/KKZYTypmnmSnmKxPw/yxACl4QXrvOTHGBcnZaOI1ToJYX55kpCigFzEty18DzGBIdnQ9otetvuQxaTNyg4A8GUjK+LZqvrGUYpxwnT0YNYXneYJ5sbp5pWvdlUdJTSOuercTeTd1HrSdL29P1fdRLheQXZ+re6Va5fUib5DlL1TEC8vwVg6NOb8/Up7dLpqlOOArXXp9lRYLw4PACDHWOUN/3dbcyw8Z1k6IOc4/2fKNxdSwG+eqz0W0YiYNFR45l/J/+KXtdE2y+btpc2gQY56LX7WMngHKVswWvvkg6hxYC4KSLPJAxmcSRtkvfwZ1MyvXjzYjJIgJmaBDrJqffFwNHEOsWsWBJK4Ap3hTjXRBzpzfZawNLXeE2Kr9x2FogXmrGnltf1rMbArg8v0+VyMGeaorlqtDi+7PuqPeZUe+eBPdT50S9T456x6piGR+3VBFRPXjrhJj1qdn7svkJ9AeGJ7j/OyHqfXrU+7So96nR+kgYX6PDjDj3f6dE30duzf1ieh8T9T4pwX3i7Gj76Y8Q5y03JvLCobCTh7OiZGxBM6pKGWFFchsmxyQ5ObaPyxAhxBbrWLeOnaZjp+jYqTp2uo716NiZOna2jvXp2Mk6do6KXSDWVZVg4SL5ImYQrplW0DrzFWYQdpZHcRPJk0GVe0I4DcVjpiO2KxiUbEpGedm6eNXE3HAaasx19c9ycTKwJVls2wVby6yqsTnhNICYM3KkTSaDx4UMS6UZVe4=
*/