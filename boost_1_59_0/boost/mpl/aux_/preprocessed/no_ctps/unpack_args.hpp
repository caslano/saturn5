
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