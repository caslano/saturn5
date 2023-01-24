
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
MgIN+JB0wHxOjwjv3HD3N7V1f2wsfAReorMITPkU99EDFYlUwTzAVpP0/dMdK57lAH/ejE9onaQ7HQh7Y5zg08SVaSbah3N9jQyO/jiGxkK1rLndo1vWDzLQMvUm6Sk/+SH61DgH6jVEKtM7R6eJcNotnVdvyWwwm3gSwXMrcsP0DYwbrwg5YF4fB7J2JZEh1DN+HbI082a3Ypq/cn+t3hkheaqtKHQFDGL4YEQr/d91nwtNZp++7JTF3PbzE+uMJwdG9jIkXxnSbkAiF7elpsF7wl0kpZci25o9L0tdWFT2jjh368AKGj69Y7wbD/c+mGjtxEjGB/9Z6ete0/j1i9Id3ktDpJ2l69KXkropjTv/5hv0vuBB/QNVOxrzb80HhSvJvI+vnz17xv2/mg/Uf93arlIWTnaOXgAP129Odu5WNg6OZt8tzN1cudjd7MyKdfHtKIdI/H1aW8DOeCrHbXFnfcu7I/ns2bEc4W8OMwzfCDWb84k2yLxfjnPcEWq7qwH6DGqr773RwyRq5Q8JkpRkpv/5BlPfOmZFhv0FD5t2SpNN5Ed14k8VJRFmWtonz4rZzruW+Vp9fGyxm+lE1rv4Lrod98/4GhshK/UfNp/h1O1NPGKTZxySPnuXrLcoF/pTSdTjEKX33WFRVS0m+jFIiTFj4fPOx2QyxhxWhyD5hJt1FZEn731X9nd52HjdjIR560W4vvmEE4K5
*/