
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
S0a7JrReH/amyZfY1JGMJcd1fv3OVtqEtAz2VDYQtiWdvrvvO905smisFAbHLMrUUtPrEZtal4kZs1kcL7oHFKV+atznZ2EyCaKy6cHW4epS57mucy2FzbRiEd8DRtz5OGEncI/lBkvfZAmyqMQib2g/EVY4v3zQH8AoGML8mn0RFkOIK/wAwQXc6g0Mg0EAg/Pw/CIMAph+j5mDC6Hl45tuwpfiEcHURubaILvUyqKyftwU2No9WZ7adc6+Vko1fooiCaFBQ4Pd7IIPIbW2CDlfaav7BqVWST/VxvaVrvlo8DEIguEL8A2qlU1D+NSuKJQOwTln0hkZ0sCR7LgOD8gOicl7kD0O/+JVsBSlC1emKB//z/z8A2nYqR/xXbV0ZXSZZ+0pV0aym5CJC2bMWnnowPMUIiXW6BIIdWZTkJWxeg0TKlxdZtudqkIlUGKSlSQSWA0Ka2hlJQDuECCSer0mO+eDUrDMStK9Ez+jYXiNvBbKcpsKywuxwjYh4D/B6Wx+H39bhKdtGIv5XQz+DHpHIZiRLEe2B77fNRi/Ig6d0JlahTbNDO0c9JiXaKIlCluVSN3GNa2I71fIbqdQp90DltmygVZbEEvbOkixcwKpMPALUUHPpNr2WLTpbAmCUK2WOh+z6VUMf0f+
*/