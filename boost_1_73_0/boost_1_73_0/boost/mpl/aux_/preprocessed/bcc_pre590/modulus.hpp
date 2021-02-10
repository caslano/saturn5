
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
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
nKnqSW+xgLyV2pbYjmZamaLWGyb4qUbwCHPBLmCF7TOds3WBTLS4bzraL6STEZpPriYwHY+hJOAOAn73KWGxLIVSbrF2fHz1tZ+uZUE144S9opBCzy7s1Y0vj3gjF9cJuzNao3K10SnsjDEJS9gXApPvHAn7TCjrN46ETSffKmzRSv8KbjwjoqTODOJMzf6WlkKFssAWvLVeleDR5OC1qlBtP4zh7zX7rTaf9fO/VkYjewcF7yMcsn3X1Khdn20VFnTEBiczVjm3p4LDEoSWO8yO3xK81K6Cf35QIHVx3O2ZEQaPICCU2e3oSGyTcj6cL1b5/TIdevzl4iHn0+trGH2Hxmy4F2RpTXSOdTTtGQctj9jWZRc0gywdyXcVgo8lVNLCGlHDwFbGDZh4DmcJYt8aZ5RpMuYFhY6HjCVsbqxL4RWvhP0iS0a3G+pNeXlqGz58nD2s7hc/E3arFO7p8SW/jCE+dRAlWQBe/s3gT02DD5PrMzHy/L3tB/doevrx/gZQSwMECgAAAAgALWdKUuKlZ2J9BAAAmQsAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNjdVVAUAAbZIJGDtVm1v4jgQ/h6J/+Cy6pe9TcNbb/c4iuQAhayA8pJScV9WxjFJ
*/