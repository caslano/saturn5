
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
2SPExr66HIUFsTJlsSo/ElHlwA/WZolVR7I/GhxFW/bp9SNB+EV/r01BeBR/rNUqgSafa5++9bJPd2jByO3ABRgUXUSfC64eBZQfHA1MxEWCdOdUOfqWDFVa2fGDW40EpPok1+hdteSFUlzQfeKh8z7DA9hvqz6ckpvVNoT0NkM8rCk2pQvf1mi0aVWAKdShSmHhDj30XwZUt1wJX+z/iLbg6XfYFXaMnCpLPoDpfLtS+nPZOz8EsYQBXjCTjtiOLeD2lnAghKdGC7IUiiWuPP+L80zLowPHicBj/s/fnCZQsr0z0y4X5QW8zqDDi0pD5PiBnk3i0sHLr4HVwFQwZV/dr4bYR7rXrJjd8WGK2XgxjVTrVmWJKFPr+i9aGQYQ+T5+rTTG6QzrFZsJz6Nkx3MKdiXzpDQnkX7TepFgTFipFh4NXolt6q60hiCK/8cFkw304DX2M0cwi3fpC2mrWbp8YanWGNkf0mxzMstXH3rFUbyIAH4fgwW/OGCNvHoTjzr8PvceO/5Hh++fzmFac48pNvPXhpK+oqEV3BpedDDmDWZuKd8SrmWteaEN5hat+Wqw8sGUzaE1S88mv8xiolbiYk+Pu40PXd4MvOle1sum3tim6xZ7Q+XULux3+8Z1q9pkfs9ZUcnuPqt1P8NI+elAt4aRd7FQCJnBJMhKaF22LdbZZnMduy2bBzcZ3aMpamINrQ1rjXLBuS4u
*/