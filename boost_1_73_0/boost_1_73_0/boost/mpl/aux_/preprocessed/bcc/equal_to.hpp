
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
rVPbbtswDH0XkH8gMvSlmysn6LBW0Ix1XW9o1wStmwJ7U2U61upYhiXnsq8fZSfNsLcBEwxbJA8PqUNZenReK4cJk6bKLX1ecbOyTeYSdplO2XW6fcH0Ke03dWPXGyb5Hih5n8vewSM2S2wiZzJkssG63FA4U14lXTIfHcUwjmOY3IJbOV1ah+yb8iggbfEDxKdwb5eEGMUwOhbHp4KwV99T1vMKCP1GrjN4rl6RsZdS9Q+jPvpKkm8rU0PnpcHKbxvSnUGAniFhhfc1wXemzFH5tkE6U06B3Un3XpCVWmDypgh4CwpIKHh6uIOV8QW0RBZA72vlXBAIIrDEDn+IB5L3PCC1XSxUlSUsWkPoRnB+cD15TG+m4iBkTCcPKeSdP1OVwVIsNg51g/5LYZ0/ony+Qr5Slefj+ASiFEo750EnMo/82tMB3orI3JQIofbn4V+wYcKe0TQZg7ACrt+F5W3Yt3VpVcZy2wQrpJpqznzRAcP16MFbtYJuRBKmsZOdxjHDxuQbCHMClXuShfI7LiiUgxfECoausH7I5LLDEgGJ5q22ZcKC5P8gxvbKjQbsmsICdiAxJtdZ6wvbmF/KG1sJ+Kqc0fDj6rJVzzM3WYw+6vHsp17M4gF7oplGZ3M6hADdNiU/mF08PN5M
*/