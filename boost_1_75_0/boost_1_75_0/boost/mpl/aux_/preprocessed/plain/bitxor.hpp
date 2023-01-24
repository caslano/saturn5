
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitxor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitxor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_
    : bitxor_< bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitxor_< N1,N2,N3,N4,na >

    : bitxor_< bitxor_< bitxor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitxor_< N1,N2,N3,na,na >

    : bitxor_< bitxor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitxor_< N1,N2,na,na,na >
    : bitxor_impl<
          typename bitxor_tag<N1>::type
        , typename bitxor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitxor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {
template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  ^ BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitxor.hpp
Lo9W376f8MpN+o2a4yfIul0dPsnkg1H0mP7yMqu9gj3t0uw/3JDA4sN9STMpDdpZJgLt+EheZATe7t76UT52mraVNPmP3i0UQckwaoqmIaVtFEh9btorSbkA2312XpdBY6NNUhqOW3NZoNLGKJIJyZPPNNnWFxkDBQEIT+qu6FJMVkV4efh6X5Kp0eRWAA+TA8OtzFvJUk2P4zflibtaJXIKofQpUdwu5Dk8UTFmeJ6KGJ7RweR4/et6IQFu21o+WzCtGXPlzsCByUCClGcyIZVAZZYeR6+Zz94pvmwmTIy52JeeIOxH97J7eiM6u2/cjnsfTKj2IvvNUtIYCSLDD6OuF99N9WoyG4f/4ump8Y98+b6OA26ahSC+xIIUTcR2LnCu42w6ol4ijSWhOpEBKyKzi4cmB6TXSg86DzzXjbPdvb0XY3ebAIouatsORUiBE9Igvm/6S8hL0ksUSAKCBSvT2WxZ2Wzb+3Lqu+EjMpE8eCgToQjExFkKuty+Jl2KS1ocw3WjZidre9OmykBEOC6Oxsc3oza2XZTKfI669vvmvMG2SFN1uXUIcExok/asxXk8/V3NO7E0S4pyN12wvnCK8zcIoyFKKVrF3Kpb41ZaqXfmzt+3szu7vfsH6NgwfGffDhK5Ln4omDN5ON07vKk+baE8mfq9x7usaDEGO5W6ijwPZ4bB/Z2C1DlmjU0WBw3BmCAlsTwBAb7F
*/