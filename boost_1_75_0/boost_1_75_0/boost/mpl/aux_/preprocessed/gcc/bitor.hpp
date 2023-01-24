
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
VY5Wr/F3b4GTGTasQzxzx5mI1pm4V0opRU+CWoRv2Q20RPL1Mathjms67uHdZXzwDT+qiyOU2sZzW4zAg7fVCoY0Bf8RmHkMpRbmI8JEqaZ4Vd8G0bqotqHChFENWUZ2tpzEWp1/vMT74q7Nf4Y6t+sd3sAljXWeEbZYunUQUXz1VmErPR0fmBdx4ehx3Y75LyoIRXvlY8AGuPy239X32j8u3mhFTsPTWWEUPSsEAikN2Bh38ApU7Z9R1NVwI5naHP+WR+lAGVQ+XFuG5c+1ycbkw6K12XlkZuPLcpcyaN9R3RAu7fxF38XintEvy6gq1OZuvxGnDAgFKaiqTP/pGJcXnxe+/V68oWDj82X/Oxn/Kb43Q6hf0VZRfd75Bfr32ek4GEbsvWPU3AjG2Z83OCq5L0WbLIc53wJUrjB7kQIj36VqGnF0PTsdvQCLNAbDVuxuQydijoxpbZFZP1JQnlBR877OOJrQ4f1hitjMS9ZSEN+M4PdUGC8eiZHt5jLfuLcHnsxtQt7rp5kjI4tpGdhrXsgNy6yzh3zv3ODZRVs7E7XDyWgmJL35gttPdcnZh1YA4CKLTov3cMgUTSLJD/xTnp+aWpEYMcUO+3fhvcdl4qFHKS41A+6uGw+r1LlW06bG7z/MQmS0RNlK12o2e8FhRR7D1zRihMEuosfqLYQ4mRetbmMxAxvyoE5bur7j8q0wzLRvvBONoDqq
*/