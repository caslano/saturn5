
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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
Onh0/NSmKnEzC3usKivM6qSfVlVrCkE8iU4UQcfLcQaj3VTwx0nMeE18zAptCMAguF0f5qpcb7ztP/3sn7SRaB6CfInNVxV84fzRomsaERGwVHs3LRIBOHqTmgiEjQStISzBHE4mPy8sRx0GLVoZKcnmA0SNBRbXOOdGTt7t0uyqw3fzYY++68b+Uv0aMOoZ1dOPwwwN0T7dZBq58BJtcPxsJ+Y4wcdFcz82OGw1EGO1UOcPuip8TgDWlLRUiT7hBxgNfHvqQe1TehJI9mJKSOz+6q2uuWglsz3WLXGrWJo00ZUZJ7/dE5bZHbj286Bnqkd+e5HM/Dbg6BPdE9DqVvQYIcVLMIHLuw5MTgcSPaOsqYFNy802vr5y0k6JaHLbUyacTrrwkCc/8L4aWgLxY0hxembjIlgAr0cywxSHn7pZ88x6nIzHyXhpRPpAKiPCJcLmw/IGjwUCTN/GQLGeuojx5E3YXZ07nlL2xJWVPrVAPC4qy+nIpEYl7Z6mB61U+v0K+9T1yeIlTYofrbcMLTxisiIsl9cn+QOlR0piYwCxTUpDqZQ+t5tXul3DjZa7euVh0XuWN+qMwQxISkY8CX2xVjyJIHZOLSrzeuNlx2WX4HpPmws52oW2qCbr0eLoMGnUbcMlKmW/kKd+EJuLtb2hqWERaksTHBhXyaQnWSIXDmClkm4TNejd/p3FWGE17wjhbPX35lU9iZ3U
*/