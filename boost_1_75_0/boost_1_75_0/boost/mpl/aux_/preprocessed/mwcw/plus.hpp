
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
F0nOA9Imt85VQp+vK1BPyS3Q696STSVeHk+Y3g80lSXWAlBhQ/SSsUdvDOLIHE8DZw5cUXfAicDrnVR5qqBJUPQgK2RO4lX4seHPfb/yBvoPgg7jnm4Je8jdfVuOZk8jmbIR0QPn3YZ/PKBRvHXFrD+DqdoN5pfpXyUgSgRudqUOL2vZEJnFhgMn1PTUngeqS6G3q4Kv01mIqw/wHmAL843JjGD+JWz2QOaNuFKoksIlxRWsn9QPww31RnPP+sekwiVmrfwTnLgI2wjT6c/1KCZIQSSNGB0gPxc85z+bYGz9eevdFrITWhv/69Ptuz+1I2+G/vWECYVe/ijA3nb68g4AitrW2jAKf2hHaUC9Qif/kwm68Jsg9N7vD90oTZ8P3C78BtZc7yvxZPnJlb6iRMtFJ6bkyOPQDsrWzMbhbLpzrS+P+o8p3492us1xRmNNkvfeFvANPV/+rMKl+NTa7bQZR6G2KXvW6L5wxWvhs8EZ0NACw2IGkb4ZSedwhMqzpMpeSw3aLMhv9BqviAe8QVU41Lk+f4jb77CGrlfwbDz7WELNpsgj3rRZ02VU9c4YXiN9SSCONT/ZTl98vRKmbi9WyolcYNwk1Sw941jUpYCaYX1qO+MjRo7NgMXoCZK240VtmvpuKa5fKa3x4yrR96yqs6zb0uTvB6IokHHUffxqTKKEXWaJMvL9NoOMW41pWE29+iHY/EQghfub
*/