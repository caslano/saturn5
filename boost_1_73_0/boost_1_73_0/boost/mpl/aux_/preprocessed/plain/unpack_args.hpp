
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
b0wEAvwbA4FY6TGRQLR/875eaiuF8W8sBILSYzKBKP9Gu2MTKkXl33gIBKbHdAJB966QCaTwb1wEAvwbA4Hg9JhKINq/NdYKl1IY/8ZCICg9JhOI8m+0OzahUlT+jYdAYHpMJxB07wqZQEr/xkQgwL8xEIiVHhMJRPs30h2bUCmMf2MhEJQekwlE+Te/tGKXUlT+jYdAYHpMJxB07wqZQEr/xkQgtX/jIBArPSYSiPZvXmnFLqUw/o2FQFB6TCYQ5d/8r5faSlH5Nx4CgekxnUDQvStkAin9GxOBAP/GQCBWekwkEO3fyHPGKqUw/o2FQFB6TCYQeRYY5oxZMx+ZCASmx3QCsWY+Egmk8G9cBFL7Nw4CsdJjIoFo/0aeM1YphfFvLASC0mMygSj/Rp8zhmc+chEITI/pBIJnPlIJpPRvTAQC/BsDgVjpMZFAtH/zSit2KYXxbywEgtJjMoEo/0afMwbpw/96qa0UMD2mE4g185FIIIV/4yIQ4N8YCASnx1QC0f7N+3qprRTGv7EQCEqPyQQizwLDnDFIH821wqUUMD2mEwie+UglkNK/MREI8G8MBGKlx0QC0f7N+3qprRTGv7EQCEqPyQSi/FtzrXApRenfmAgEpsd0ArFmPhIJpPRvTARS+zcOAsHp
*/