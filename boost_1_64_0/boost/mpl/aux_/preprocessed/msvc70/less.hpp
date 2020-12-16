
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
9nLFjB7R+rCmkM8aJDGyPl2Z1GMu8gT1mBFnUA8+kGbZy0otQdxffutDn5Vcnf1Ezjk/6Hr6yZOttHPzeGBYXf2Ec97jaKycU8fRUzXbx3AfwTjpP7HIJmxh6exjC+0pE8A3YjMbULZujaaICP2ers9QdoJR2ZmOOybg8p8iH8r3Ku8ZKS9T2n0a8jzXJRqWR4sFMXZRnld9S9pyDyprhDyr3ZMyHrraY1QM13GNut5El4Z6m1SQttJQR1tJcW5ZjjU3MyuYtWhEV697Yq1JuQcMy9VGPfpvifWMyoxtJBdKeyxBXuC6Kq8yZZ9Cyu3rXPnBb5u43jm89qEUm1u0c9ne/WKN6NFS6q6dfJHrVnUx0MNx4/rvh3odvOu+6TzZN03q/iCylWsrlDKd96/D4lKs/zHVVa5y/8vzSj/GRBqMMVEGY0y0zxjjimffqq13UGqX55Pnnay1pV7ztdh0I3Ucxbm/anVS2mAX6ShTs4dXDHR8Y30M9Evae09XVwy0smRhkDHQh7t7x0BHxuhjztdL+c2l/GbIP0m3wV2+76t3UVmhJXAdTokOapmxTfR1/pHrKk3LdKy+FXSZRuPwJaJDeRP93xt9UKjKrcOUixMGuYPs/Zat5d1P8j7aRG/TvuRd7Z03hgzcjhdKPLtaztVN9Xa8iB+R3dRyHJ0m4HIqmnvbbprEzau2O2xQ7sX8SPAqVxotiL5CHU3braeUnSrr+LWQsiORr3gBTHOWzT3tv5+4xosTpMvM0FI49zCdLH7Cv3FeXSfAOD7e3L9rHDdv7qc09gfXXry7sZ/V3F9rHAdv7oc2jo8Pfj2AYOPmg/VPB7uug/H6DeZ+93yH37rgQ3vT8u2DU4Y+3eJfzW8aOdnc7268ToOZPz74+QcmfndZJ0C+rcgYGO8TLzVH4qUKYAQshKQjP/k2It9MtHQdHXE7Ev8r8VKXwCg4EMbCwTABXgpHwyFwArwMZsChMBcOgwtgIlwFk+C9cDR8AI6Bm+FYuAeOgx/CVHgUXgE/hxNF30mwLrpdCdvCybATnAI7w6lwALwKjoPTYA68Gs6GWXAJzIb3wFz4AJwFN8A89x538i0FLkLiffa46yhxULEwCsbBONgZdoNdYH/YFQ6B3eBU2B1mw3iYC3vCfNgblsE+cD68wB0fKt9M4N2iRzO43CeuezRsDcfATnAs7AnHwQSYKvpcDgfD8TAJpsEseAW0wnRYDjPgUjgJ3gavhHfCyerehR3RC9pEL3XvwotEr0tgKzgAtoMDYUc4CF4CB8Ph8FI4El4GJ8ChcDocBmfBRFgA0VniH+X7CEyWfqvGP+ZK+Xlih3x4IZwj5RTAcbAQXgGLpP7F8Fo4F14HS2EFtMMX4Hy4Ay6Av4ML4QF4LTwJF8H66FMO28LFMAYugR3gMtgV3gD7w+VwKLwRJsKb3HsbyvcP2BGJ99nb8DmZ5/I8bAgrYFO4GbaHL0g+K5ANks9qyacpLJd8joidqmBL+BGMhn+FHeDHsDv8BCbAT+EgeAxOg8dhEfwMLoefw5XwC3grPAHvgF+KPnkW+UYBy0SfRvBq0SdGxpuOMA52gvEwDvaGneEw2AVOh11hLuwGC2B3OBfGQ7GjfAcgDwM7viR23CZ23C722AFj4ctqfLfkc57B+Pq65LNb8tmj3ieSLtPgPnlbytsHW8P9YvffwR7wHdgfHoBD4LtwFHwPpsHfw4nwILwSfgCn+cTrV9ag96ui9y7Ru1KNn9en06/nIumeUNq3StJdb9C+d0t975X6roUx8D6p5zo4EK6Hl8MHoBU+CPPhw3AJfMStp/yNC1sa6Hmr6HkbbA5vl3QVmki6RyRdS7hR0v1D9Pw=
*/