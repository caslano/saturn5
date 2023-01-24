
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
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
NMh8+yA1NVBsz4BvB0NDQ4OKEp/dN0IVeEVgO88TBiLh8WSQOqVg0S/KCVTxWT/Id4T9e0PPtpSAUo9IFI9INlK+ip6Xb3YJnq6NNdXftSvbmyBNldNnN178NQBBb18BAafT66bFFj+jNWjcSZZA68mxsHKEn2UpOd4VXmp5KJmjeJ1z8geAo6NmZze6mYtcgkIr1uLvtbvsGrfFRRf39uwHeUuYLsDDn5ZsvmUBcB+OXl2I3rIPNVlVa7ir53PVx9d4WyKKdI1y5prGjREP0VJK6Bp9DUG8GxsW/s3/8B2p/NgD3qVYelwcX7aFrxgrunki5QoimOH0NivUjV8gYgSEFdpx/3FGuTscJ+ideziGkKU7xI9UUdHJQgNp52gkKmLqc218EArjKdbEqCIzFkZNc9PJN6LHiO5EqsIIOdYIDt8+fQzTxD8udW6pyPYGdo39ECd4LSOIl98Lzhg5RJ+J0tPTu6hw+75CFHM/fO2u74WHgibrrrVsml9R0pfM3Jn4KEOf7EN35bRd19bWVo7l4iZ+7bf9XFkpzq+dSiGYZBKFzWCqBkFmgPSiK56r5qh2pPhwXBlut1pM/q7TVwodFlTUPBAopqx+8OkRl/VfEfG+cFlpc2fKx7y2Hm1OZX9VSJBIjMX9uQUtxlmCFL7KUGT+cV/KOKWC1sSVu9h6ebb53HBNvxTHZ+oQYCOnVmbHDsYInU8H+3/e
*/