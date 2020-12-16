
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
xBvRuOr3k6PjeKPjeNXjeE/7x/FePiIhufej6+699/23r7zkswtjzu043nSEd1nLcZsVMg7KDXvAj8NAutgw6XIk3UpJt0qXLi1Muusk3fWS7gbdOKR0STdSMQ7pZkl3i6TbDOPhrXAg/AQcAW/T+ZEXxg+f6KsUfRt06dxh0t0k6dZJujJduuow6ZySLk/S5evS1YVJVyTpXJKuWJduj6SLV6S7Q9JtgX1hjS5do6Trp0i3TNJlwzh4DQyOR5Z0QxXj6UZIukvEz5GwNxwF0+ClbXp4X7DWM0b0jBU940TP5aInPagHCaNnkOgZLHrSRM8Q0TNUN/7SLXqWKcZf9pN08bAf7A8TYQIcDBPhlTAJToED4WLdeLg8pFn0b1CMo58g+qfAFDgVzobTYC6cDvPhDFgIZ8L18GrogRnB60eeteEtiutnjtiZD9PhAjgRLoI3wsVwI8zSX8drrOvlo1K+j0n51gfTIWHS3SXpaiXd3bp0GZKuuyLdQ5Lu8/AC3fhcN5It6TySTrNbJOm2Sb7vk/NXJ+fvU1IP7oej4KfhJLgDzoCfgVlwJ1wJH4Tl8LO6etMsdjMU9eZLYvcrYverYvdrMBXuk/bq62L3YTgdPiL6JzvkmRAOFv3d4BjR/4SUxwGx8y3R+2TbeESe6azHLb6uO67a5nF75Lj+FscdsTm+MTq2MTq2MTq20Ti2Mb3B/vjGI9+LcbQgSd+PcWQgJcg2pB45jjieinGMQbKRKmQPcgQ5hXRnEPIoJAepQQ4gJ5DYp2McE5FcZPPT0XGO0S26RbfoFt3a3z6a7//ODe71nf/+P9DRK64/D8rHU8538CTjKs6vLCNoRH5Bmcv/t0T+1lLNuwdfjT356+UvDv+4gcHkMNCvuVm+4adJP+MgZABps+f7+xmJPuEs8LryPYUlfhURxeqfggWWCQj2LU/jd0G+Fx3GeFZ0zhr6vmPle/t88WkukoxP1fPb+r5XzVu+cP51zuxZy2ct0eIMpTvdFWWlhZvs+NdX55+/dHT932PYJ5oM32bqxaeHpT/+q0gKPjWH9clfZO1+J1D6I9+s/Pt8692O0O9WRVXGuCjyqJMsZTYAGYR/jQus/RvvLKnw2ogxF668OImGOE2xsBLR9hFTxHBeTyp8TNPqqZWPhWXUPGdxWf5ab2fP61BEFBm/BXdTrJsRh1+ZFj4Ve1yuDvqit3uimzmO0JBU/LGyq338iuC7TmsdMdYZrjNDncmTb/E9Je9auqFanQnng/YZ2sZYh0D+pxnzH6wLzeebvzkOw3ZTWNtul8sTmf0pavuMATDbH4795jD2nfmVvhJWAd3gKrNtX5d/Q9kfF/uT5fxPRGb251oIZ98fScteHbA65zkXqvOdsTCM3SKX21div8yt8tyksD0C29nhbGsXrY1vh+2d72zFt/VLsJ0XznZpeUmk9q3yflTs9xH7vZCR2HeHs89tP5K2xsr2XvnG/ux51DX4FLwU23VWtsk3n4B9kcSdotx5CvGSRr4pij9eT2EwtqTWBuuK1DFQV099Fc4KxoZsxKwrdG1g/iYPOMY2dLp8vy+SaygPGU2+YpdY5KusomJdpdufpywbeQre2yRPB/CnOJkyXq++FwfHNIhfZeJXCTJGK28rv9aT9UDbFsG4AsqcspF7nPwu9lSsl/ILrkfcptlYfqvlG/5M8XMqMhY/05Za+ElgUDtjC/pK2Vjd+3pJhcoUu3MRrT66rexqA7EiGPcTWi7T2srFFN8xQfNV6qY3n9MglVN//RwQf4fJtTtEnq2awvnrdK3PL7V/n7B6tmrVwvkMPlvJPlkrW+9nbm/1M6BjmbWfH9UzYMDHM+LjFPFxEnI=
*/