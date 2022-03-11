
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