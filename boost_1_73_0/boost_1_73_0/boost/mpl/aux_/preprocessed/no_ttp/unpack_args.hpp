
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
EG4B8INDA65CCJRQcQsFYgMzWyk3I+zUYT3FictXUwfxZW15IUM905r/HoF0+jP/AlBLAwQKAAAACAAtZ0pSz0slfoYBAADTAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDYxNVVUBQABtkgkYI1S72vbMBD9rr/iSPFHRZSxwYJmKP1BA4MG220/BkU+16KKJU5ytv73k5wlHqOFfpF0uvee3p1ORgxRq4Alk2boXNpe8e2XozaUrL5rNtMCfozs7mr987G6ZVLMCCmOJHbBLuDaGhwiD6ZFJvUUJERAOiCVLHTRJ/wplJ5Q96hfS+aRLBR1dX2zroQ1u2xJ5OXb5Zelt5CQXhFCsXm+Eda9/M19XbaGkuIsBHJQeyzPloFw7yJCp4wdCVNeHAEgtdvv1dCWjPNUDeiR7PZoeZtjzv24eyexTNfARyge69tqBbyB7KczFrOf+DtCLnMlRHH/UDfrzaqo6/vNQ9XkffuOf0Eusycq52YIqLNTKc4GpXfphz7ZqQT15DSG8GG3ZjWZX4bckR+L/8pYlKxJNGhVVKxzBCH0MHrrVAtZLwlldB6A00dPI/CEZLq3iQaqi0gQe5wY0KsAO8QBFqF3ccHkYcImCSRypF2b5L4nwX9CeVD2hUxu
*/