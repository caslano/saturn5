
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
P2UxYu8PA6DCXJFPahKhh+3q5mHPpP3UhsMcsLi4RGNIMcB+qxsG92rrbP7qn1Z79BRLjtuAn3d/wSiQdeeZg0vCg3nqx6/f/eyMn1tGrLVo3aqZs2RPgh8lwgM+Gwceh532mZylsjxAA0leRP+anm7a97x/cZmXS1oDeXlUXDWAgpya7l21sE+eLoShQ3+ZfRBD2EeD4mPtwIpi7vv1Y4r745ZL3LL0R+xfiEXvg/sioFjqt7D7HL10j/cGchc8TrcfhyKnMnRiQK9leptg0FHUDU2gzkRcaOB2uBii7CKCEeULoz96r2onWOmFaVAEBoB+jfWU1b8P3ulv23PaE7oxeBGCbO0x/77GI9Twz2sPN4XwafgDvfFH+GLUCl9qNWoim6BnOqk6AAjFTv/mnWVFFBcHVWa6fKVcDHWP25gH7rAX6pNBoViqso1Ly4qijJmFf+rRylRdmVXylzPlTFfvWrNl2rh9ot8DaEOTHSudHdxlKuUSAcK56eZyu5XeVVp+oBYPZdy71WecX5aI9SG6mjqvDC7hinMNZcdXq/EZ8rThLDzx7GO4+8Y6rVwf6QostXQt1OOPMZNd9x+IrsfeIwKLDuZWnTEXym0JOSDe41yQIb6vv4VfgMElRc+vaEy/vC20Naj0XzMCEJGJl09r2ksMf89n+W9PuIeQxIDObsiSdkp6X+eSFJTUQJaTRBo8ZtIUK0gFqqeW
*/