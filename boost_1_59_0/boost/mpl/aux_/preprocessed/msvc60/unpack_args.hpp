
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

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
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
*/