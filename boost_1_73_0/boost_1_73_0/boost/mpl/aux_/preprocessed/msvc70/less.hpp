
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
JGBlUV1rwjAUfb/Q/3Bx+CJ00U18KLEgQ6Y4VtFu7yXe1rCalDbO9d/vxvrB2Fty7sn5uJGOGqeyhmIAqU1uY5Bf1J5svWtiCENlTa4LkOIOStHx4AFkTVXZMrTLXBbDIk3XYvQ4wqfhEJMVvFjjyLjwjUzh9hFObkjaVhShox8nRgBhbm3Iup2KFBdVb6BKzXwGc10SmuxA015pC9HlGj+Pe2isoVOpDU9aanoxHOsSp9hfJNt0uY76PtU62aSC2SzuhVivofqb6hj2zlWMXq/SW3DxFZ6022OGjTYFO3v9M2SPDi9+/KxjS2UPh8zszu/+pGPKbcbHSxlfjN107ldX1dZZZcsYXucp+pB43WMAC9u46H+VAD44cDgrWC5CxYVF/3O+2S6T9wBmSlHF8EAMAgjY9u4gxc1W3D/+F1BLAwQKAAAACAAtZ0pSheNdg3cCAABcBQAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQ0VVQFAAG2SCRgtVRdT9swFH23lP9wF4TE0IJbyPgIaTXEx4o2aFUy9jbJTW5ai9SObLel0n787LiljAmkPRBFqa5z7zmn5x4lNahNzjR2ScpFKe3PAy4XUhW6S3pZNmgecNUf3gz6d5mvFNYVy7GACbIC
*/