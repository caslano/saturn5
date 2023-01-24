
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less
    : aux::msvc_eti_base< typename apply_wrap2<
          less_impl<
              typename less_tag<N1>::type
            , typename less_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
WFBuKbrwlduPb+g6g8wCchEnZ/eYYOzbE56gZGhyr/R2KazwSmswYxnHx/+PfjqW5yxgWjBm9RnBSZ9b4TM7hR7nePycq6Uws9F82X2FmMgX4S89WjMuJ2Hv3QMr234OqLAa/BHbF71OV8SwVAEpo4W4O3YEafzOF68yxm7ojxTycjGF2HeJJE1tMxxDlgQyBIZ8wtIZI6SiRC0H0ucvB7f7JZHWugFhQk2WtP7oJY6+wTLmx/svGurHSSaMeOI3NvJTxOPpiHU9O9hrDPf4itKjMeXlxotIeDHd+D9jCJbwpF61avOLe/BZs3vSunT23MgbU29t7zq6F5abaX65uhm4aFsgk7qnlP4x1FUimqI5dOMH/59R2OX+NhFJ1EFxZ+OV26RuMFk9Z0Jvr+mYP08Q0Xq6Z0dtob+s2LgaUrOJoeSgCxpgnqF6Zu53GGq/h6/NKnTlNwX2SLvg7Uik83EeSAuzWh8JyYGt3z6UBFMFG10TsiLSFMzTF1B/GfFi8dJjuM3tL74CJKjEjBrj8jD9QQmUupH54lWP/uQK2p+nzcKvqCK+9tTDLyMeVf92MEPgyVXTFebYEmnk2BB3KYHYHrE0j5+N3TYbuoLqrRnZaYftHc0mPdE1Ka9gVuYXPT33h5ITeGFl+5uWEMX0Ew7jgqd5qqAQkcicE4Y3fGFZ4DzmuXzfD4SVCU9cwXnymZGGGZMS0RLRItVZ
*/