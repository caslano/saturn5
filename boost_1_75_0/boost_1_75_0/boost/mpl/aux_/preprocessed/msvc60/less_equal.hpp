
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct less_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          less_equal_impl<
              typename less_equal_tag<N1>::type
            , typename less_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less_equal.hpp
0xnH+/R7fjAjWCjoKzQcmgaNgyZCM6CpveE9+133lP4Igr9hM6onZfdN/JaE8bCv1IMw1vJnoBbk+Dgkvtyj/wfDI7QgWjZP8wY0ckpSrz50F8qQO6ItJFoyjWK7+NKveRyavviyE//np3kaeK3PQ3q1ZX8cMr5ipH/sLzBDf2aEEudYrLz8peLbNmMOQwvw5jo5WhmcQdDbfvpaNxVgYrew5EjcrLzWs4Zfo70+mVtQ44Sk8gU5KMw+ktrZjtj8Yk18rUZZLWEzDF+TeIFi7c6gbinyD17SXeXCUvPcWzDxGtMAt+mtDgfgjKsDbPt5HwCoZ3AXvI26Pm/6vV5yGAhzC2foA/iygP3PkyfAj9/L/ly6Jev3qQSRfymsSQzCoe3kAp/JWQZe3Hi164HjEyCPBUlQctIV8uAgwm24mytTiCsPviLMPGlbRQ480dKtpJwPBC0xfYXCjXmxgFzRYEKPiytZipDLYVVIsFgR6EqFgDMckNLaq2QKhnnMPoWZoppGb8b1vMdk+Zr8kJB3VRODzwoLkA8u0pAHWMKmVnpHe6El/jubE9cwOuUJGOAvbOyrAnAZ/I/djFT/no3/1Y5jgP4XKobajuHKy6fQRSdZC+tiJydRJwol+WukjAaoyeoX25FJyyd+8Pdqo1rm35rrCiik0x5raADDKT2/Y7RDx1V618Wc+cfYed2ZUhmDdrsZ/BNGe7VmsRwt
*/