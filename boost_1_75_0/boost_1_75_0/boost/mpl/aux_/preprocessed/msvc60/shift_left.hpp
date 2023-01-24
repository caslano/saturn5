
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_left_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_left_impl<
              typename shift_left_tag<N1>::type
            , typename shift_left_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
MbfsMqq+f1Sw+CMJm4UQ7TyrPlyj5uk6vEAQg9kmE7dewJ0RDX4Wm7u/XbpvAXwHgV4tlwDKbFmMS1NTS1D9V5eE2zt6GarR6ISpO31LM6AGokymDLFQvTvkPAp6Ur+Vy1s2EZwROHt6BZqH63a3SdauP669v0CQem2yI+3RDAjgUdsp0nuoNY5wywxBZDqGprAT+g3PNNYPu4eEoWyURrZ2Mblntp1T3+9hI2QOetvYKZJrp4QkWdv701MYCqaHsGmq8F827ooxrHW4g7v/tRt4rwSQBSt8RgpDbOx1rnUiOuKYuGu/EOzJElwdLHVhMBV3aaCFuVXTE87ln0NTEJj7PlFw/pFn1D2k7Bxehoz5UxyRneVpSBvIaQ+iLrqA7GB1bl3+xvFzx4OP3f6n8Q3rf+V4kb/F2ta2Xzw8/2Uc7+9rMuAl6wFO4jYUqeOJwZWtDmdeW04DOyDD7xNuCiqJReKsycr3RpdmwQFQe1Bzm4Pxw2Td0LmkOuFSsfjFNRYezTlC4bdqdKtvv8gbzRZroILfaKzKuWalvSZ/KENH13vgY2MD0qt7zZ0q24uwnvSB5UoixnMg4zmSbeZ3Rzm2spjpp1MzGXWxnIexFuS6qWDi2Lp5KvZ5OP2ARe28yb0iwDg1H4/81invxpIFdgK33yb7TF7zTIzKgCiHIKfqy1AaYYO5RE+beUr+VF2kydus998/PvaJJxzi
*/