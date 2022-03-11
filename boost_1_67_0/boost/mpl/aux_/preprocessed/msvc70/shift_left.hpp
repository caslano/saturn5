
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