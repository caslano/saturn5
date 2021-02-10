
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct equal_to_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to
    : aux::msvc_eti_base< typename apply_wrap2<
          equal_to_impl<
              typename equal_to_tag<N1>::type
            , typename equal_to_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
AQAAdQMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzNDdVVAUAAbZIJGClU01v2zAMvRPwf+Bc5FLAldMWGOo5AYoiWHpZgsbrXZHp2LAjBZKawv9+lJ0sHXYYhupgiiIfPx7p3JPzSjqaQ97oyrBoqX83tnRzWBbFevjg90UBubhYcjE6X8EVbsgeySauKQlyS4euZ3spvURtVE2qncU9uXgMJ6Y3U7xNU6zedNujqoP4EsEYJMNKttR4kd48nK5bWTImjaCwUruKEy20MmWjd9mIpnKwNV2Aj/ESP+oRPBmtSfnG6Az3xpgIFoVkJEYQwX0K8pMH7lLY/ueB2+m3miw5GbifhbIMqH8cgBT+bC7DmmRJFgPVwBMJMkzmNIJhNk9dQ9qfZqMGhV3cQPYcau8PDDiruZZ73oMkIS93iZNHwvfG17jtpG6xYdr3TPspLeNG95yf91KXY7hMiMlytSme19kkzHu9einE3f1X/Bi1MzsRNH7nML/xfD1VONT+Srap+qE9lJXnTn1NGDjDWjrcEmmMXW18DPlx8OUQB2u8UaabA68sDpnPaxfB0jif4V/1RfCTKUged5ybV+jNdmLyunjZPK9+RPCoFB34+Vpch53JxSVDXvEcMLAwiz+0FIdO
*/