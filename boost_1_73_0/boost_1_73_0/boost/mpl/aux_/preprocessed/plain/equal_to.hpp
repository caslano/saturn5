
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
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
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

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
u5A+YCG8a0YxvQ+0uhkjD6rxaMG3GBXQKgclYgeJa3ufMHmKLI2gyPZWByu1dqo0wd2tR+crKG6/xA9QSwMECgAAAAgALWdKUjQxenRMAQAAPQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MzRVVAUAAbZIJGBtUstuwyAQvPMVK0c5Eg59SImoL30oPcWK3fZoYXsdozrYApLUf9/FThqpygXYZWZ2GCE9Ol8qhzGT2tQdbd84nDpbuZilb1nCtsrskElxbUsxIdmMzSBFe0TLna4IZLFvBwJUyquYhZXVnQXnGghziDndSHFGjhLPrUbjzxLlWBDEjcIxc7XviXApQRq1x8kbWPRW41G1cNK+gWLwCDb4hV45D2gq6GqodYvEExMRZNnt98pUMeOcHgXlwbb5NDYPNef9obhxsaA28APMP9LX7QqCr5UQ8/Umzd6T1TxN18lmm4U9T75eRNvtRJj8eHe/8D8euIUHvlySvDYOSTuE+mdFBigEh0/RP2YUs4zCg1txBliI85LamOcnWl0PIx5U7dGCb3BkQKMcFIgGItd0PmLyOGJJgkLcWR2sVNqpog3urj06X4Di+mN+AVBLAwQKAAAACAAtZ0pS0gb8SU0BAAA5AgAAHgAJAGN1
*/