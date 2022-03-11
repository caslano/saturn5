
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