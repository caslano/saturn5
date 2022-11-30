
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
{
    typedef typename T::tag type;
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