
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
    : tag< T,na >
{
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
7/4UoqPHYjbGDsUrHWOhhY2ENNvdTZTFLLaCbRry7af8WbuLLfF+enpIRQyx1AF3QhlXE38/OPTkq7ATh6LIpgeSNP/I0lMhkpfj+2f+JpS8YUrOk3dwQn9BvwmmQqE8du0wqkvB+mtr0MVFL6eGgTBN7UQTY8f4XwvKaYtzCqjJ245ChN7EBqwJwbhvqE2LzMkZBFWStdpVs9VWyvWBMx+z7Xr0yNK8kL12UT7ewyYBS/S8PxPxyuscl0sqTvuF3tQDVDpq0HVED7FBGA8GjQ5wRnSwCg3FlVCXiWUD9J58SRXneXhiv3+9kldK3s7+C1BLAwQKAAAACAAtZ0pSSW242c8BAAATAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQxMFVUBQABtkgkYI1T32+bMBB+t8T/cErESzVm2DJNQR5a1VVN1bSJCuvLtAcXjoACmNlOOv77HSZtJu1lEgLO/u77cQZh0dhcGkyYqLtS0WOPw4vShUnYKsu2qbvDzXXGBD9vCT6h2ZzNIUV9RB2YukAmNPbNQIBCWjlR8Oh9BB/CEDZ37Ju0GENWHd5BuIQHdaSNKIRoES+WMUFu7jM20cUwWguMK3gp98iuVGexs8Eau52tYvjM2L1SdJGdSU7w
*/