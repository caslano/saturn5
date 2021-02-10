
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
AdCcwXLxADyPMN0MCqpi5BknIriRyDLEeK86qOHiwcgwOl/nQTjzRx1U8eeL0NgksmPZylBxZ+hIZlj9voGmLjfhsrGN5ay4TDZHqPuLbhSXoGIOVV9DTEtYc55Dq4yFahF3V2PxgkIKJSKRemQZTBdYg8iPmdiWWtXwQeXrMz/QrEh5F1Xx9HmikakfrDQS/vCnMNbIwywIAZ22K5/JyaVGvi1noYYGrwKucVE1rn+b31BLAwQKAAAACAAtZ0pS8lSYSm8CAABQBgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI0NVVUBQABtkgkYN1VXW+bMBR9R8p/8Jj6UpWCE9IkjESKukmN9pGoydpnx1wKC7GRbUqzX79ryEenTdPWPUzaC9j43uNz7j1XxAa04UzDxIlzkUp8bWBXS5XoiXOzWi2aB1nMl6t29TZ/wAzCKpM5sX+Kjf023XlNlqAeQXk6T8CJFZTFDo8TZliL6NNLSsKANhggTM6ZyaUgZQHIg+har2UlOHScFigiH3OupJap8WazpX91GXSc+/t7b3rKh+hATAErtmPXymqW7gUREtHGLg36vasgpGHodpxrKQzmeqtdibkGnoyfmW3xhvCMKQ1mnGvpDYf9kUdPwR9APJgs
*/