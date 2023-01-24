
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
CGRlF2oUFKv1SKra326ndnokMb7USaCLzIqi/WYJgSXgNIDcn7wYfZphITa0SlZsdwRO+wLHIR5BLpIt/YMeV5inaZlwH2ttOLXBs5raveKTFFS4vn1s7Z5c+JMKDPTKwCIt1KCRAmWSt854QxLoxt/aih1DoZZAi3FsRvUUKucNAleGgBVAGBmK7pIAT77NlfdW4ZV+k5uqcmR7fL12Zk23QwHezApw27XnXvz8lj6bEqOrF0SQrD3McmoTk/HzVA5U/dc3LK5fXxFfP4KmnohmHDqo/WztbkkfZPRLtRVyQ/lZ6m+Boi6/KmiunLarpq9BOZNALCr2sEi7vCnfvcG3R0Z0o+cVX546fk6FXIQ6BGMUKje6Yt1Q306Dn/l1kLpTnUmrB+AODG1As1c433Yh6BxE+af9SYd/R4C37AkMkIe9jlOJTPUGgCyCWolARWu/JtkEGpK7YJbBXUI4DcACSedRL78TQbZFpkJpfqMXwOjPGFDqbweaA7ntXvJJWgZQgpR53d7/QB2eiBOuYvT3YW4PAPuDtTqoCB/K0vbCGM8Hxph63vqQCbzrRPeRboqm6Ubm0fQj+EFh9bYGcYgoGgpB7xoMEjSOohunEs5RTqMZk102RdRItJhWLmJMoJmjdK0cSTJnFJaBclsx7hGp3ArfFx0XlbAbtZkNaOzhzpGRq7iWqMfwJiinX/h7siyYk5U1mg4+ZbUe
*/