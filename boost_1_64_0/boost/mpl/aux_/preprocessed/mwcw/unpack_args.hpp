
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
1GyjwYQu1k9ALFbX07hcLbmhcyMjPCMYJ0ehvu3B926JWn/YUphWmPPoamBp7bSLgvPfEbKq6Ggo7xntvFN0ifw4/BFNo5tNkiiAFfipAS7cYRz/BwDJgLgg6FN5Z63UzS1Qkx4XYIPBx49yTwYZoXl1hR3CwNoFdWFFNPSSaOAMRn+O7CCMDylZULhYum/QX/tx5qafQ+X/AG7SExWF5eB7Cx6LVjyNmTSkwMLqx0D1IPQbBxVBJOnwrozafYTI+3axr+DqV+Csv546Mh9LD9/bDNclFC9SOoY+vewgEzmo6VCMR3uYLKWyKxKz1NuVAK4Be4ozzYB0PgYq1l+a65b5wugOgISDc7LGDSkGUzLTXmeeYfXk/EtNFeK5dqcXv+8AaqAS7ACRO01uScPLHXLnmnMv+pN9Py5IAcRVlb33AamMBUxuYWw68Haip+y/8R2Ch/yne5ACAH2YIsdbBo1IVfKqqsnqzJGDqdf380HLKB/k3I7yncpINGB+cQbxDR/YeWfHbNr0d+g8khPlF6T4NcpcGPPvUcsobv8UTtOvQSe2Xsh+IlQ0jw==
*/