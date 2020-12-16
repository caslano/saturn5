
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

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
B7wMHoHXwW/gLfBb+JzGRL4Bj8Ja+D38Fv4AEToWVdoISE/6rnx7PKPVPhm7Svn07Z/23x6eCvvAnnAMTIDzYR+4GPaFF8HT4A1wAFwLB8H18HT4PBwMX4ZD4CE4FB6Bw2BX8hwOe8ARcCwcCVPgGTAdjoKz4JmwAI6GS+EYuBwmwqthErwVjlX/Hger4Hj4DDwbvgAnwo/gOfBjOAm2pp1NhpHwXDgQpsIsOBXOg9PhcpgG74Qz4HNwJtwFz4M/wPPhCdg1A/aCF8A+0AbPgpkwBc6F58NsOBfmwEK4AF4Mc+E1cCG8Dy6C22AefBHmw1dhge5X2FS+Nvqo2l+sY+yw81iuev017AYvVv2ugEPhJTARXg7z4RWwCF4JL4RXwevg1XANvAbeB6+FD8Dr4J/g9fAtuAZ+AG+En8Kb4OdwLYxEt1tgN3gr7A5vh/3gHXA4vAtOgutV/xtgLtwIy+Dd8GK4CWrMtfxi1C1yxGvMdU/drxNgC9gLtoS9dd/tAwfBvnAC7Kf+UoGUK90esqvxe22laS5He9hG9+tIOBJGwSQYDW2wPVwAY2A+7AgrYSe4HnbWfbkL3A/j4HcwHkaRZ3cYDXvU6yXfluHz8tVrjJ4zSTASjoUd4Th4JhwPU+HZcB6cAAvgRGiHk+AKOBleBs+Ft8EUuAFOgQ/AafBBOB1qrpL8T7zvSi/zXKUB0muw9BoCh8KhcCIcBhfB4dJjBCyCZ8CL4Sh3PvIjwSKLfH6rMeTXwxbwBtgSroEd4Y2wF7wJJsGb4Sy4FtrhLe49neQ3gnblY97TaZ3u67frvn6H7ut3wv6wEg6Hd8GxcD2cDDfAmXAjtMG7YS7cBPPgPea9kJR/e+Vv3gvpXpVzC2wF74Pt4P2mMfs1in+p4pvH7D8k/R+GI+FWOBo+AleY5oZVhclPA9uqH0Qa+pvG1LeHT8Bu8EnYBz4FJ8Kn4TS4HZ4Pd8DV8BlYAZ+F98Pn4B/hTvgYfB6+pbH1++GL8EO4C34KX4ZH4CuwMTrVwHD4qrv88sfACRbl363yvwGj4ZuwK3wLJsM9SmdBmPwnsETpnAgzlM5Latevql2/pvvCbjgKvgGnwjf1/vYWzIN71O/eUXvfq/Ydh+xXfvqUrf20nAc6usKhmN5TjxkOSaxPr9orXJwpXKLCdWggXKbCndhAOHuA+Va4ytFAuKpjpJdsClfjUw7rcHXmcvgPx800sHzjFK5dA+ESj5HeALOdFa5DA+HKk1SOBsJVBJhvlU85rMPVBBDOjtQp3O+RI15z9PaqH74HI+H7uk/vhwnwA9gXfgTHw4/hDfAAvBN+AjdoDtUm+JnyrWjk+rZmvJM58zXmDK2ExhGvfHvCWJig+3hvOAX20XOhr+7P/eBS2B+uUPkuhwPhtXAQ/B08HT4AB8OH4VC4Aw6DL8Hh8BU4Uu/vZ8B9cJTub2fCz+Fo+CUco/f5RM2tTIId4FjYBZ4FE2EynAjHwUw4Hi6CZ0M7nACvhxPhbfAc+BCcBB+Hk+GT8Fz4HpwC62Aq/A5Ohd/DabCx8V4M28M0GA9nwF5wJhwIz4MzYDpMh+erXngP0DdB6lrPk+56xzIOm+olE3aCWbAPnAMHwmw4Ds6DM+F8mA5zVU8L4YWwAF4BC+HN0A7vhovhNlgEq2GJ7F8KP4NLYCN0WQqbwmUwDl4I+8OL4Di4XPa+GE6HK2AWLOe/MngJXA4vhSvhSrgKXg7XwStgFVwFd8Cr4PNwNdwDr4F74bUwpkn93LE9b4c3OH8sPT/cPYesjvCHRxLunXCfuWTLCVeJ7MgPb3Be2YB3wv9tc8vSyNt3fhnk+lr+roBbEc01c88zq3nHue/iYeg=
*/