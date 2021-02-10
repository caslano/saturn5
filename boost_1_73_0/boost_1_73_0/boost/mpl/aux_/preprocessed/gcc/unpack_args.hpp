
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
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

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
U7o1ofH6XXUusRdHMpYSx//9TlZ+wKD7NgbG9ume3r17OiQdWpcpiyMmC70y9Nlg25h6aUdsmqbz7gUP92n4qWpzaFlmzKZAyyS/gCUP+9kHWGC9xzq2xRKZrLEqW0ovlVOBkvc/9WGQJDB7Yl+VQwHpDj9CcgfPZk+JfgL9oRjeCYI8/EhZoBPgpca2C/hKbZBNjHaoXZy2Ffr0wfHcbcvz+nfUa5cLGBKFiyedaAFbY760aD8zluMvkh2EdfoG/0lgwr7ttG7jHNVSAImjB2xjs9JYZEeNA+/x0U0yeVIWniKYnHUBAUL1Ecudqwh+CkFqtcXQHTSFyyEcIexsodeQG+vAI+Ca3LkmOA94kJnZbpVejlh8AE8qOO9NZ4v0cS56nm0+e0lPCdrLG+SN0o7f3vYhfgNtNL6TTpJkQBLPBeQKldvVSLMUpkzyywrhji1S669YF6sWvCmgVg5rcDl27kOuLLwhariyuXFXTO47LBEQpzOZKUeMhvk9xafTj9iULOlmJWI/ycV4vKbqArJdXfLe6/3L4nH2HLFxlmFFyzf8JmJzr5rGTGvMXGG0gCfEKh6XxR4jFv2lrrfiX9b+Y/S9GMkvhkh+dolf7oPfUEsDBAoAAAAIAC1nSlLWiIL7MwEAAPYBAAAe
*/