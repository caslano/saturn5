
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
    : tag< T,na >
{
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
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
*/