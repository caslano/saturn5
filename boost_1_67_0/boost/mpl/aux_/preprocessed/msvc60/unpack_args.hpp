
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