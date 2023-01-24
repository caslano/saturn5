
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
KyBB6HJxze74d4E3Jfoh8I5DyTf0+yHCqz/yHahvruoJY1y+oOZgZPblRY5bXUY8ZK+vYIdw/ukDzcjLT3/syxM4U5JTR6ojdi0HM29r3Oqk4836mK9W5NiJUO3Eag35DlNg6k8aphMmAcvjAiVuEXtfmT+HZDDb43IVcDkAMn9Sp3+jcxPaeE/MuC6wPUMmYDxO/bqjuww/QIZf3YQztDUEVNPaa/+R7SCKU0Bn/Kl8/3lFsEitogn+z3fc/GCFmGuHT1/bRrdfENsG3LLXbrotR5KEzLmZ7PU9YCj/8LYhD/5u4JQx5quW6s+Ej9GaVwmUQUw79TIBk5GyRFJmhEGqqUwp5NZC8uoRv14B3n7CIbt4La1qzh3adbHDwYjRk6v6o37yZ+BKJOj2nDI4iDPUljdY7SOe/KUZZ1a/2gy3yDclE/1vGhbS7a2EFMvsRm6mPIGKj82Kqb2CYAuv03CN+nUtwAZcZiWP70GUsjc7woxKt+ljtR+4BzPOujP0oxP4cfWZ6m7tmUT0Zo8K4NvmybnZLAJYilfeI2C7fBO3eQm4NDTdUr6gQOFm+QONr50d72FFnfq+l3OjMP3UpYvVG2eZgQLEyUjvGMg0qBijU2Y7/Ws/H0nIluYVISG6B28wZ/Mq9eYrF2q4U8kdCMybB6wjVHNH3J7DDZ+vxU9t7srldp0+O1o/ZS2YhFKQeMn4NH24nyLxyvPp
*/