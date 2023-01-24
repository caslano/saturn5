
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
VpOIrMBW5+UfFpjucOGFrL6hBOarEZbfoiiU1L+B5v687jMji0YGcegyQK+KGAtQ5LvWIkoiey7/fEy+hWMXo+lk6m6xbiGWW5igoSuHGNaFWC14XmkDrFM/vZN5+psJ+VKlyV17UZsiYyl7olw3MNoK8FcL0GhQCZFG3YRPW2bCfzAJN77H9Se93SR6RhNHTeh7OR8JHAyZ1LrkPx7w2iQXD8wNpO0m3Hr1oifm0nw+TW9LQJiwpg/DG20jtHnT4V4dSr20CdwSfUZBYAODKS9nfncm3iH7he+QN48I9dsG5JzIpgYRRBc0HQDz8gB5q8FikCUXjHhQuGlHJ60wFJ6vCDHxPHlSkIbI583Cvu88AtyUIE7GVl+ft/q7OgKYVgGFN/0l0dtXsOxI+OuTAueciJcEuHnDXJBng0Esnl9Rd2XattX8Joas61xc6ddFH0/pHrv5xVFYL2l/J/jj6DJUx5EqnRQoHKOQfI97o1OeUjm7o5mWGi02j2ILaiCQc9VG6pTJ+X5dW71yxdo6SY59nbHMYq8lyoDnR1NJIV2x+zSeewdilw/3WH7M2RPEyLPo9jKXgyRF8aTAkfkyGXxh7EOMTYRnLA4fSbO5ploHy1e2C0Fo7oaknu8MHlXpENRE0AO9A4OamjYzZNIE/wBSPdl0t2toBEofYEhTwINAevffYYzVp8PvzJ7qXSbMuWdZTLpNr0+6gFSP
*/