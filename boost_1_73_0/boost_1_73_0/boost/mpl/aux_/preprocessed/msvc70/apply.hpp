
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

/// workaround for ETI bug
template<>
struct apply0<int>
{
    typedef int type;
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

/// workaround for ETI bug
template<>
struct apply1< int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

/// workaround for ETI bug
template<>
struct apply2< int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

/// workaround for ETI bug
template<>
struct apply3< int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

/// workaround for ETI bug
template<>
struct apply4< int,int,int,int,int >
{
    typedef int type;
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// workaround for ETI bug
template<>
struct apply5< int,int,int,int,int,int >
{
    typedef int type;
};

}}


/* apply.hpp
rNMbCOA6XiB5XAgy15sNiWmYzqBHho1Ko0yQ3GAv5G/zHLdOHMnH7O90Goqns7Bg3GUz4iNgrfUYLlLnwXUUnKe+CLjQj8aX8ddx9dxo47t7DoLz/my+yh4Wou93t5gvMz76xxSBO+6Whge2gfoTmmrdgj8QUGtiCK7EcM5QKgt/EBvo2VK7HpP7oKUSW6OdznU9YXRZgVp3dyphM+0JfPCQsF90dOntM3UWdDKm5v2nu+XqYf6YsI/sE/aee8LeMRc+c8a7Cw94E5b83+YkP1GU/IiWn34Sb1BLAwQKAAAACAAtZ0pSiXyBZ/gBAAAnBQAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDQwVVQFAAG2SCRgxZRdT9swFIbvLeU/nIE6bbDWadYbolCEGAI0RiuacW+cE2Lh2lHsNuq/38lH6cTYLtZJi5QPx37PefyekyQenZfC4ZQlyuSWbs+4qW2VuSm7TtN5e4Gry5TlVmtbayuFV9awhO8WJrzTHrJDWGC1xmroVIYsqbDUG5rPhBddPD4ejeFzGMHsK7jaSW0dBuy2jxrDaMSX1o4Kv9T8zIglnmYgwCjU77eop3wS0hEBHQH7IjzGkK7wE4QncGfXEIXjEMaTeHIShyFcfUsDdmGN
*/