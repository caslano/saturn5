
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
U+9sbM59ULor2LOzbQ5K1zU6UpUwYXNqYEODLmEJ21p1TKK4EQ68sm1LA0bVeZY9vJQbsVjlD1HuqlyL7Mvj49cP5t/IPC0yI/03eYeV7qNFs3Cw3/CPbGn1Gc2dZIfGIU5Wartz0wW9PzNq2h88dgrd7SgBKa193paOp2sbLvQXOl0fQckgQdYBHZBhEJ8QNNLDFrGDO9/YcMf4fsBSi97ZYCtrCvbj5bWE6FPClvPFKzyvy2XO/5VRJGz9tBIgypxf2XWd/tCtKe5g1lQhejWZJ6so/30u5gn7+bYQ8S1c9uC73lip/vcZzSL7ncKzszHZ5d/7C1BLAwQKAAAACAAtZ0pStfJ2WKcBAABRAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMwMDZVVAUAAbZIJGB1U8Fq4zAQvQv8D0NLYffgulCyByNMSzalgWSdddxei2qNsVhZMpKaNH+/Yzttsqx7subpzcybNzIP6EMlPGaMK1Nb+vzBw9466TO2XZcbxpMTwJORwy7ZJWzR7dDFXklk3GGnDz3heBgYc63QhCOjGgKi+CEvY74NHSV8hMCNaHFsCnsVGmjfdFCdRlBmJ7SS8E1o/R3iuBVKx67qAggjz+OYCHZfU+ipXjIW5D5I
*/