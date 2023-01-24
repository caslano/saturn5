
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
BQOpsDI+e5r2sA+vjgvWX7mjnEPs7kH8z4z48KLtVrufA4MynI82V3v5JhL2lhw9AlU/TPoWzbcEG/DHh/vvo5MoGhECgSOd0dU2qqhrP6Oq0SADuoB6Hy9ez+rlOfBAvEdpi3IOqdhMO38bYkim8je8lLlT3YZJ8sZULPnX+RoMbd9M1FBWr9b/UoE+9vNeJ033VHvMXs4m2gf4uSRb5ZFd8l2wc1IHSZXlJWdd0kg7ACvlDij2s+OuPWrE73enyiZhYIjiw1BGh7p4717Ozq7KJlvu0FyYzYONTTrg5crGwNMno2QsjlMddJcHqVvYHdIrMroJHjy57/zSOkbnDsbPCf4CqsxcqKsX2142cXO3u470xtf1GIbRHOhpYD70Whye0mhg5WjRdlcuDj9vWoDmain7v6uAfzgMwcXXTO55L/zusPDIap2H2eDaTb5ndCDIke6LGsAOAZvLfXxhs1rxbg/8oTVUq3V8/1mJplupfKxLSYT95X5Vuq+holZiyBvw7GdJYRVYum8VSE4pQurDsxo6VdZiyw6WuNS6Ltw2maH63U7PFdsZI9zytGvWE3FfmcT3tXEParE0qwEZhhs+3HcOFE1CuUVYuWMewMwEn/8EoGV9TR5mErL4bpXaV+KalvkgUaRJzAGPDv0UFy7vJH8SPZ0/jdOUSWpInRnTgeqHjc3+dkq83p5XUxc9x+6m0Ma3mXth9Fgf
*/