
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
1LFTYN81IXcW8uJHG6Emc2U6wECn44MSP9b4+dU7i8sA328vmcBX5M+IvOsFb/cCsLjNpjKnDqzkY6knSfcTqZS+7dS6VGvKEiRSTeMWZ/KZ5beKrYlnWUchb/le4DHs52pfQpOfpGlYfuszyHyWxNCMJiiQMubhVyehTy3ej44aTph2gZm5E22j00qv0XpGnAx5TKGNqSJQ6y6I6t6i/yYpmzAHK5D3kvcMc91whidR7bGaq3sn5UV9T8CQE0yiCmXTZIK2yOtP9jWzJsSEnnwF5OlLXk37O9rMq2J9iotgsJCQrGaD2ymUETCQuu4x1OlX4hkgxBQYOeDau9w74GVKJZmm11r8ThlRyelAh2nXGa99ddExb1/53Rtg+VSYTq8Xib8YgVWg1xhR2ormg5yHoGJJRRpWHZRCl/ZRDV765nHX+HYnNkD+VDPFjinQN2Lzeqou/5OpGBDBRjceEm3NFKixPnrllEU92XMRqQJOncA38duewMPK7VRVgC6+XCzyvargmuuig4QDQ+eyD7aLTkVzqT1SH/TU78ogdB4/22VLO+bGxcE/aUPbZbBC2xX6pZPvyihxjyhuzMU34aGqd3Uqf86nx0bVu/oaDA+v5fOdtbBJINQHt7pmrpHMpd72rtHpNCHBY+BWFtxxCX78Mjj4M3EZbyOqnwvvVnSAfIeRV0OqxUrlKBTsVHbhb1KRCWveS9tdLeks
*/