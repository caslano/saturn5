
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
L3Rlc3RzL2RhdGEvdGVzdDM1NVVUBQABtkgkYGVSXW+cMBB8t8R/WBHdS1RioEmVs9yTTmmai9rmTjmadxeWA9XYCPsu4d93gft4qIRkeXc8OzOs9Oh8rhwumKxNaen4i/277Qq3YKss27Cl9tH2kDPJLw3JJyy7Ylewxe6AXeTqApnssNU9AQrl1UTAk5sE0jiG9Q/2TXkUkO3xE8RzeLEHaiQxJLfidi4I8vQrYw/WeDQ++olm5ysBX4aKwdzX1gjItXV4xmR9S3wePzyvfKPZ970xfVShKgT06OhjLCqtjUjxpEjyo8JR+oOuB5pJej5eCFKi8vsOyaci7270fqlJN/pdsMr7ljqnK0ijGopRW1XAMTQoO9tAWWsEZQrYk3SQfMKBzG3TUHliEpzPVutt9rwRsyG2zfo145/v7iCKjiogDGnc+ZEcaQeur6G2O04oAkX0JCTGBPBDNa3GG3oA9zFQ5cgPZ34I0zidx2maQpqKZC7S+xBiiAe/RD6kdQpljOsNu7rsYUgSVOmxA18hDBsElXLwB9FA6CrrSehhxBJF21lvc6sX7Okxg9HSaS0CtrLOC/jPeMB+U6zRckez6Z/vO81nb4+v2+f1S8CWeY4tla/5dcAC0niZIPl5LL8s9j9QSwMECgAA
*/