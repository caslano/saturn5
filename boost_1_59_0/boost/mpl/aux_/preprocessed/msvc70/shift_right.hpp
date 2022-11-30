
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
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
*/