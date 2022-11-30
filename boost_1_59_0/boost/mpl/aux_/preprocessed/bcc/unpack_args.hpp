
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
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
*/