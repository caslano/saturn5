
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