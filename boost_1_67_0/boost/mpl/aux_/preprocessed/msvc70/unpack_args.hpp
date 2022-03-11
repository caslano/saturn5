
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