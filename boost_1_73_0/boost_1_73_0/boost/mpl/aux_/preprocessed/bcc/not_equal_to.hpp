
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
T6hztNkmXPJW2oITgsN/iiYzpCUbRZT0sXVVpOPGQzjK4Og9+/e9/ZANyorSdNJIY5mSOdwFzrzBJXJvj7rML5BJK0HmFnXngXsqKKSBL8QGfFMo6zNx6rDUoNXKqlRVIdvFqy0Qy+ZSq6PxWPQax07dC/7Kuq0wIMZ0e1h6bHFYguw3p7I/EWGPraJ477HkM1rB2mNxstnCqGdId9dBcOeIxz5268QjRSMjwW80+fjj/gBQSwMECgAAAAgALWdKUj8GFUwXAgAA8wMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMTdVVAUAAbZIJGCVU++L2kAQ/b7g/zBY/BhXj14Lsg2IhHq0VYmenwqSJhMTLu7K7kQvlPvfO/mhuY9XCElmeDvz5s1bRegojhz6QuU6Nfx5wepqbOJ8sdztNs0Lvge79mexXq2CRRecrXmtRPOmUmssRGqKwlwLE0eUGy0872pzQs+UJJTsCyvZ9hKfYIv2gtZzeYJCWTwXVZOmLHfAj0UqrcYE0tw6ApfrGOGKcEQCbVoGXlRSJlRsmEJcp+MM45dvwwrdsB1CTsdT+Dx5hF9ImUlgZQjmNVMu7K4uLozDgRiIuU6gMiW4zJRFAvlRG4stlySiaMzEuy5MUsme
*/