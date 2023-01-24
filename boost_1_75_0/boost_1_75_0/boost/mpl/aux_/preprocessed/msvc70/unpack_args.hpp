
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
2z+AocAS8muwExnsXQAiHBncq+z6KhYnHOY9mMvzbZhS/SZ8f0aSILyGcfst6zaylhn0nPsFs1rt5nt8FEMAgXKHhh9/9d43haF8S42ujpK9Rfkvht0/fsGq+90+vXpH0qQHCDZO+NhUj5PbqrIXKxWvfcIClKcV5D5ftBK+XWtkfVVKtqlsal7zsW9uUVmvsO8dMcFLmUXrDwSV8t5X1oWsvdZrrr/rbFJx2jFYMLUhz9Dz1bWdlzPBylqmWLwKc4uECJe8NDHz+bomU4QrW/FftvU7t/M0j3dsTCfa4zUxh3kWvXkl683BVIXG7t7rQyAhkld6V8cGnmk3VdZC28Br01IQkPeq+5Lklns7VdhRCfqGUYsOjm6/BSPIbE41v+TeQlcgxd7+kILnY0E4ZjBw8mib9MbOnaeTJgf6rDUHXfWso0xjhqOKvuYpwIALa3uvNwI9ontgxzRHWQooQDSg8/PL9PLtd92yZ6KDPvgfZYRpXmrtt896/MGALeFH3qOXNxxIJrL3tfD7WzKCMWD3uQFY2Gt7/K6TBsCaE/4mKFJHN2R0BS8VAF28FpxnPaU8RXufmhBM5oIQTI0EtGBdi6CfQ8BscEXr6ubFuCdqVdoIdHVi+nDge0oSGxwL8MYChaP+NcofPPvwBP5nlP/HZ+8c3P80d3FHBwtrF/t/TXX3wl92F+LQzW/FljEO8o4JZe2lShiUb/mj
*/