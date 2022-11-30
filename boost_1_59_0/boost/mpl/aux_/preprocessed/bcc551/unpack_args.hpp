
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
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
*/