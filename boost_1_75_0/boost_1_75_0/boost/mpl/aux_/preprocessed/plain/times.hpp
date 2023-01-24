
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct times_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct times_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times
    : times< times< times< times< N1,N2 >, N3>, N4>, N5>
{
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct times< N1,N2,N3,N4,na >

    : times< times< times< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct times< N1,N2,N3,na,na >

    : times< times< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct times< N1,N2,na,na,na >
    : times_impl<
          typename times_tag<N1>::type
        , typename times_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , times
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {
template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  * BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* times.hpp
GVxML3gSOkypSgAFRaxSTpOmVl6MkwSw1ZVqdKRHvvx5dP+SPM+pa1o9OHCdsRxN/YcBmOvV5JLDATz9FTlKG4G/42WXTShcK1XEVAxHlH85KVwcBTNIArcmB33wCp53hr2li+8fJCZwnxpEco2BYjPUyzV33m2xZYK/NaFhGgltSKVjfT1B+ZkTj/R7tMzH/FkNg8zA+pYVmPxVnYb8jm0NnpWDCRjr8f0gJMjZXMzAFnf0auTPS70RD/eTXcS7TVrzSztjLTTXsJ8iVwNXvv5MU0OtnkIbn4TsYE4lRrbksMVjQFjthfV5S/6d4TWS3P0Nw+QVGuXndI2YLqCi80ztIeCom5sqEOsIro0jgXjDp5l/x11LOZLkHsuswKzIo9AgehbJoqDlorCexM/IppmWCJx/VxrG46TyDcyToXQ8Nc83yqPAO8eZyj04zcl5EseDZliAKGKxVhpOHsfnyR3zEciasE5voDw0UraqCuEwp2OgOZsIeUKnVu4rLUudsEiv63jz/V5Sc/K4DD1rVFo31h8FYnp/FjyTp0GUNcZq8D6r76CRa5b8SBn11AG3ESWax+J6saOWa05v9nyBXxzDWxC3S7GkKUIF+4xKJvZJyrcfJUGTHlmG1sagWJdJPJVCACHijqGQGdTg7hCPffdep0cX5W3a0OUKcUsqhT5pe7IJ/uofQd8XfjfsD9dKdWVW44D6un4vDakz
*/