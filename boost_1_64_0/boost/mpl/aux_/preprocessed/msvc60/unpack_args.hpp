
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
PbgnMWom2DsI/bD/EAoIRcTZb8F3CJBd0gEPUaEirOBOIUvktT0LBpbvUsitzSmNjVphpO12wppx1BtciG2ZZi+gUCNP6jUBH0xxfyhjyUnWm57rw06t1eJOWaEf4jEH+kEzhaMCaBog5CMF74zvcH5LOLAPPMfCEEuPFopq/sLVVd+X0v+Y8Ry09g+/vtuGnO8bMHF7oFrfDbY1qe/gvCgHz0w9e1IKC7k/5MZQtfPJPdDLiOvUMvHcb32o1VjVikPtyy4U3kQyQ9+zJf23YMBy9HRwRJrZZRBKRqAukSH85kry+TE+n2mQljeqlYJqrXM78lNeAtk0RZLJV0tYtQ2yp+TZIwSGAOobINkXSuPA1Rb/6XWvITVvCw4Ps182GpSMCQ7qVNBXTTr7yf5ztjeNbrg0Dk7+fzJ//Z9CQimZrr645TEDlMifqVbfDg5EaNd3JpKTeAyV1Lf2/+7s9jSnmo59hfvFlfALnqQsp7NRzDMrCHJBAPyTdZO9I3IgfzMsyT1/8a9a8z5D6f+VF4do64KLgafIi/V4BPaG4DOHw40wSMRn1sxJCw==
*/