
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value !=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* not_equal_to.hpp
Hu2vIL/9gW9QSwMECgAAAAgALWdKUnEGpek5AQAAOgIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MDJVVAUAAbZIJGCFUjtvwyAQ3vkVJ0cZCVWHDhb10ofSKVbstmNE7HOMSowF2G3+fQHHtVRV6gLc8T3uDrhD6yphMSNcdo322wdePrWpbUaK5zKPC/SDI5wtN5xNYLIiKyjQjGiolTUSbrBXlwC4HiLiQUns3BVRxcBDbORlxDau94Q5BN6JM2aLMXA2ZYBX+nwWXZ0RSn0xUA1GHSa9Q4gp7YfjHxcbnwY6wPq1eNqnQEtQ+sQaqfDu5nbjvhyEGlLG1ttdUb7k6bootvluX4b9kL8/soAfeqVFvfEUbyQ7i97F98N+iuJBEUKt98kvgyQjpZ801MIJ0mgD1rYwCUJ4Ai8T0GFw83zi5N7QyOYSaSAahwZci5EBrbBwROwgsa12CeFjxHqJSfd/xxnHR6FORoYWamnFUYWulpw/z8ps+S7fUEsDBAoAAAAIAC1nSlKOsPc1OgEAADsCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjAzVVQFAAG2SCRghZJNT8MwDIbv+RVWpx2zICFxmEIvA2mcVq0FjlPWumtE
*/