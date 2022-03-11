
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