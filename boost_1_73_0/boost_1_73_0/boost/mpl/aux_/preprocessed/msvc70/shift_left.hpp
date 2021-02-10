
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
1hI3BLxSbxixR0UnT7bUlcbywJNdw++dCQrEMxVZeuK5z9VGQDzN0ulNUhZfkuv57HY6m3+NI/a9KLD1ybMyG3QCXnsSi9idNR6NTx7RbHwt4HY4Mlh4bY2AorEOz6i8bzG4/PC89tsmYj93xvRJjYq89ej6QBmxpLI2oYmNI5H8MCKa3F2jA884uWIICDB2vGC19y3Bj+EEvLUNaAfvtfIUwM4haOM86YGt4LLYdc0lkwG2YI1+vUlTqh9DBtKoLW3Z6W3bIFA6wOG43YGcQHxEgSzsdqtMOdoQnF8sVy/5r7W4CBXr1XPOiR4au+G6HYVOFfR56GW4H/+w01UPoX1QlccOfI3DcqFWDl4RDcSutj5mcj9giaLSZDJ4+RafNOIFIwNwcEIyAUTYtrPeFqHL0Mjg63jxIra0zp9qzu6PN0DAFb8KW5L8TCP5yQc//x//AVBLAwQKAAAACAAtZ0pS65cngCEBAADWAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDUwMVVUBQABtkgkYE1RwW7CMAy95yssEOI0ZdO0C4p6QZOGhAAB2z207hqtjavYBfH3c1sGO8XP7/nZjp0gS+4ZM+NCLEmfH7xeKBWcmSYwh/gNn/u1cfaRd3aUTs0U
*/