
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
Yu5TcIP7VIp/KiaYf+P3v3Hsc8+od7bP9d2P6YdrAh4e4RHOhuXoG8/bYInm8Hj47UsKbHg6qMaqk9Tborzp3T/IeGXqI8GHwEvdAsV1ukrGh6IPkXeHs3fQHw9uP8PCk2v1QJ0P0NVJ/FRN/f4h11n37Um7afw8bvGpbjOD/7+g4f91xGjqT0asOl/99QNFkBRD/IlIHeFR7K8fJYrE6fqfiFIX+KFjBn/9QNE0Q5F/IlD2EzzqZ/9NnO5GLnv9261Q9eX23e3Y+d7zct8Je5dvuKePu8LtXgJpni8pIGAFa5kirbjhmj9CyG2gmZ2uPl+QqvaBkmsXbZ7LpOuXZTSE268PDaG3T8ywebpShMrYpahq2ufLqjMfrKV+6w51Qx49/1YRjYaagZEUjj49ffeh+g0EmxefT7OZgtRflejp47S5ykF6unupKkgUniJQC5aI6JeqSPyCNHcn3WpCOTyVJ2Z1DMmwf/1wvfqM1v7A3o0dDgesmvsNWd3c5bEdw0qvmvzJ6evV8gPSjbP8GX03tQdkAsP3xLtwBs/o6aTw21TSdHk4eEDORp/RP7A/rp3vPaiuYrGb2Sb2NiPs9v3//wBQSwMECgAAAAgALWdKUlDG+QAXAQAA4AEAAB4ACQBjdXJsLW1hc3Rl
*/