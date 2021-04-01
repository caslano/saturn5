
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
82jeItK1R3Bh69hAlFGj/SExk0+SzoSdSEQK6MXuq1A1BrXFFKIq97+XM8Xb6ElwzJK6C6ihDtDH9A4JdeieZaDRDQEHheiukCAK/62qtym8Ta4ZbwuskLmy8U7e+JAXhUpzs9joj10qvyN2t1/dt2Gn/CkaVHwQF6kdP4TMBjQluE2n+9oIXuEGIT+vS21vc1WGckQZs4/7zuBd5WGX5dGqgkeVscjWOMTYdNFjyxY9qviGD/KCPlnxEQDw2HCUCSPPTCYF8Ot2VpY7eQf5mLNYuSl38jxSLaiO58ofG0xryItRhPvWfSJpCfFdCvi9jJftEGWZNL5PKsmIT7emnnG7qSG+so3K8NoHywAHUgmJ3/x3qbOxO2wbPgg6j/raObQftfdXP/kU41ytBpiOvDHUFGBD+T1ambhuUC3PoTWvTWOQkqiMdpcsMZVPPV2AlbcMsfBlF6oROvjVM2Ip2w7d+wDYGKUDXhWzXQYpYRYVE493VMb8DeAui2iHtHgRaZ0tdK2mSvjdjO1iOAe8KIli1SHqpZMs42Qk+njsCPbM4NfwnYF8r75gOg==
*/