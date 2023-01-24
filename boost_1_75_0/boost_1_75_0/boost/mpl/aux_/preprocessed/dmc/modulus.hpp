
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
blK7VK3GHFWaOuvxy7Vf96EsA3AWRbWnWrTWaZnJLOZ9+OMmSJ6tTXYlkZc0KQfN7nIhfhAci1YP+PEae7Wqp+droXAx9w5pOOcvraz99Yfxzy68YKl9THhwOG//V7Ig+t2EUPq434nfLE4XydMQw31+erSksG1po+5pKleOuHQHCeI4/owiNi0ar6uuJhDln1ozsg8ZQ95cK73l1WqelhOmgUVxaGYF4ty6USXk4A4pfdwtplajx5bkyGYT+Bv1KkjjppswF+6iXqG/ZSWWw5kTUHoZwGVFO+rTu/CuRUvh8ufjz0gYmLXhrQlmKM2Wat6ztZ5FYzPhm59L+xzxMsvW/zHW9pcWZdhmMxxbt9go9Y7ZjvpOsv2qZ9nQUZlHeu8k/Vqv7qpdleGKwrBmqjdgTV2gJi2BdNJhvTTl8KY8bWJoZaCLRxv6CGBLM/NSGIKk2Nu1PuyUuOVYId/rf/ZK3RQLqL1rMbSuv5Em9KRSsNwV/V6fl/bjgyzmgZfYTJPE3xV0plfjnK89cjXuyM3RhID6lwOz0LB7niQWQsl+78RdSJ6df+3yWoAPzNJmi1Y45Icz83jEwueQWL4Y14+GIvywNBsDqn0NSooV+QmghnT8OUsIi0Pey6sncAlo5++sHd1TtdOVgLopBP+44QIMQ4BnpkxE9Lf+XvmOpfrE/cVUEv06EYMC75rwPf47QRkQy/AZLH+djjGl
*/