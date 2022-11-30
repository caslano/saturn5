
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
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
*/