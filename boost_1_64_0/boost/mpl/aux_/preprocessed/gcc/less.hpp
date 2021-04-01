
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
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
XwH++A16u/KPN8NBeP1viJO3rzi2380OXvNIVQO93pWFkn1NyJY1OYeYoXE4zVIVV/HnwpDJWR85V1ka3vR+81XQPGiBvDlQcoBSvCy5UUG4jhoANz1wfu6L0gJh8Lmk1lncsU4rHo0Q4tnMyqGFRdRASfxAb8egws6tPIrjLKDGAmhP9o2AwrXATP5Lyzpx9WD1B0w1XkLdPrRIYQUsy9JN9mmh7qEYktOiUKM76EhvPzPJk4AbAbH16X7EDMfMHg2PsOiRk1Re3oV+2xzGAHYI35e2FimGwYpOLP4phD+AzwzZk4ckC/qD3U12lQEiFQo6uJV8+xoklESwxkb/ODc3MIJHlcipnxGN7FVDeqF8UkpuHL20O3ojz1yRlztcUHiEVx9+PqqFcvsbCHWqeabdsuIpAo3JPrSGtA7usLdmuJtFOpQ9fTBvBttz3rTjknEbbgRAFAWl+6piAhA4lXvoZDdFvbH8+T58EWeO2eN4h4mbnQWgrkIuy0S0LpvuLZm+/Rqt5CBCe/Gv/qz9zcw2s3MqqQeorLMN0rbq5KFBvaVxP+OYJIWbVg==
*/