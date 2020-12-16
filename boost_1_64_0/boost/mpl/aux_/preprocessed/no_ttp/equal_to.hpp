
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
PW0eal5mGa6Fjf3S4+SYWibT5pol6deuv/R5wdo5Rq/T2Vr+6Of1LXob5KWma5Fe7h5quedf19b10tolbZ/0OrNeq/v6MZqr1TdDW6Vdx+jx7tXaDj2PCrR2wrA9rQ7q9dfB4juDlINWhnqas/W22UO7llP3raNeXhHaOUlPc6iWV/px7aId//r2amj7q7f1q7Q2UL9G26LlgX4Nu9Pqe86N4pK/55yRlyAXyffYQvRgGRdXw3cCdw93b29v0/eCo7/je6zxu/l+q+vrYO2Y/nO/1wYYr9eM5w45JsKsrl/81en/gu/F8p3Pov3x09qfkr83h1i1BT7q9J/0vbqa8fuO5x/7nq1+J42oa65A3eX3vS7yW9T6Nmr9S46N/5N+3yvp97y2jc0b+qwGy+FJVNJQoKUhfaKdpGFnud//vVjJizXa+STORz3X79TOE3Ha9fUyq+Mkxuo4KbLxvdNeq+P6PAftWolW0/L7Ddsivk7epnnTb2pp0NqqthbHorQd2nca1pU6MFtrR7ky9pTl9Dh81TjCtHMf+y77ecbq2N5mdWw72Di2997lu9h+7TiwcZ3gqc+rrG2H1Mg8R619ZklJw3ztfK/krLSX+j5r3ysjrM4p2VbnlDyrc0qCjXPKThvfMQq1OqPH31tLJ/F7yrp6Olnb8jqbeT5qmxGj1zetjXS2OpfVsviOp6dlY7GWFg81jgxtnl7HgrT6pKdlm17+3tpvDFpbr6dlo9ZeM0/qyUar8+p5q/OqYynOq8bfkOIMvyGd1NOlXUd4avNM9VfaDMtz8nSrc3KSViZ63pzXykSvTyFa3dHLc7qeD9p1gZ+Nc/w+q3N8kHaOl/LWj085Fkm3ngbt+rKtFp9+LM63ugY/ZeN6O9jG9fYJvfy1a9pDWp3V4/TT66K+rl7W2nfH2VbtUm9jPkja9mn7qedhoZ7/cs4hHVqcev26oV0z6fu+5i7XzM76Pkp9Zh0tPn2/t+llS3lLWrVzoX4MntGOQf1YmK/N05fL0L6bSvqN7bzh+j1IS58eb4yWR3pbM1ur1/q5P0SvC520+m/jWjhL4jUvJfVNq3/6vBt6WrRr+iStPrCkpMVVu57V4z2plY1+3B21up5wvcP1RJEMiv5YTXm/JdKWcyNab8s9/s1t+ba7tOVn/k/a8gKrtvxQKdryHKu2/KRVW77ov7Qtv1iKtnz2f1FbfuK/qC3fZ9WWF/3OtnzZ/3hbPv8vbMs3WrXlq/5Dbfma/0BbvtOqLT9V1paXqi3P+ze05fn30JbPb2Vn+gRIH5Fe0venYITWltM9Sn4bKGUfkdLer7b+rcBD0rSztXnD7eT3slboSZqCR6ppykgx9fqQdLUtxW8WLqQr3TJdkk65NjBcOxSp026W330TPCyvWxPcLe7XyrlW7mPIudZ4H28iwXisJPhYtMccv4b7ZIZj67w67WVZdiFtzDvaVvotNsQupDFvjHlcDX5XpOOW5NE99p3wZjtphvzyZTrVUI5NPfT9OWnVF8Jb0pcn6RshfaBCCD2UcgxX05fqnupOYYanMrf0faG6WqWtu6TNGHeQ7HCqxJ1M6M1y+2+Pu+O9xN3TVtxW9Tdf4v6F8BDhIiFA2e8ILW6P8JgouoH8OWXTV9JgURbWY7C0M2+0m+SHHyGQ5RZFamnqGO52b/mQYLXfpySOPrLfnQhBLJdviMO439P/4H5LndS+z9aVOmlMU3B780Z7yH53JwxiOf8oQ5pMNbD0+97VVjqs4t0r8XaQeNsRglluvcSrjcp2D31DmxjyvLPEs0WJwPSOYPIc38OhSp5r8ZhHr1JG+QqPikxX+yyfKWWfZWN5W/ebi8Rqci1cT80TuVY=
*/