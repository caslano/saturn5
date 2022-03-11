
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