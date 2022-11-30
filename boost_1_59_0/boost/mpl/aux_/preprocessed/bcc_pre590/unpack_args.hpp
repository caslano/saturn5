
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