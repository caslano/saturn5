
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
+nu5LzIhMJAJSMA573NNMqfN/r2vJvxOZUCls9233UhcuaaIuRQDG92nwfTgOkonNfr+QLW4F2pBbMUcPnHh2b5yCLHQQ3XaHmA8DV1aZc/p3DtZjHHYt90o3EBQhs9439JKMrWHFZ1fQiVt/uqPvN9bc2VUoQE9hSYqDRMPyzqnD88Z2/gY3ZHP2bxn0AbZgVmvIp+7bUDnIfryG+vujlYde6G9cakvWoCT4z5V4sdCNhdNF4Pnj0leHQmib7K8aZio2nX5fpRm81hcTRQDbcM6vF4wprs+dzw8+/tpMNN4hEpAM1DQHXwAk4osBzbPan2qkzz+eJmrEivAxWvuVxN2hP4vDYQ687YNioVYkxPJLWzWWXvA798pK2as3SI2U/pA1Ep9m8wCyj/H9Zt9k2SOoE40fd+3fZlu4IbFVf+Gmi3Qv4lnonwj2DDzU2SVXjC64ttgqmtal3+LzP2ihlzwHy6hsVTMTr3/yLgI29GdtEPEZUZgDVd0VTwORktDmgzYm+slj6aot/3/8wUKvSWUeMRCS+pVNUWdOw/GL2LI0sY1pf7qVLApjg==
*/