
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
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

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
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

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
ZXZaj+G1ft/ptjqS249ugcD/kzftAoE4kTjpEVyNFwY7XN4yaOCDEL8G2NT8WdDHCVgleH69GmTN1Fc3OPpI6Gw0tXONLgbo9lldr6bOz5M+kSti9LDNaMpyUKwe3+AbQuGWZrbVc8J67EUu2ljxQ25bFjnmB5S38eKdJRlLz/PPf2+ieovyq2kRu5c9t62EmODXN+KuIMPoEiQpdV7UPqelV5e2FS3UW/gL/QHBKs9mhDclTrWzcbedvWimIEXhU/jdRWiLLmUVy8md9mYRQfrqiZ2QkgosrvDA+NnBpyHTjq/jpqKePvT5s4vJLs1qnWKx37Luy5/8f0vDpl5Opv+Ciqu759J7upqhmelYoHaSAZlfwu08s65P5wVt5dZWz/acvV+SOA92Ex6iCU3NFmRNIHVbLaE7n3lnljrEO0ymtksj5BDg3MlL3k+SVvqXo0gAIkzmWjusNebdszqiZomNGZ0b/brKN2LhnFL1KUDFkq7liLGETBqvcPNcFbt8sUF0K2gn10sn5It294bnnM3AQSmr3dZVLFMXeZdBV2b61IlP1GKp01/rGhSPoDrHDhxm6SolOn+5zIj6C2rjVwyahnFog0L1jgtb6ig4LsGxpudO8gtb77Fa6j3IyYHef4jxT3b3JDvtImVr0dybhZGtkan18qPnmAhuibtvfte9iN6M+beyT4M846juwIpmeg/NtOwLppkJ/tv5
*/