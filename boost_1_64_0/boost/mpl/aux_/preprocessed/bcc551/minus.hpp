
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
9EA/Ud7zeLfeqK+DE1+OmrgYFWwATzPHqrA2wcxOxK+cYy91VjhHu/1R4spiv4TTHOSP4y72I3l1G+mt60OTXNnD9P2BgnPa1OO0aZqOf381DHWRZ5JcXu9/7J+T6IQvDhReP1jtAfrYlxTRHdZUXIupVEb07tgjOQVVAoq9EwXiwfjjOHW/wPPby9/P741bfzDq7AQ6wdl0gmv8G2A8j3BW6Es4qkYqYzJZ6Equ6SnhMh8G09GkFzKjvkTV1BKTucrFiQfRcQcqDVKrB6lxMqxlaG1D0VlPp/Y2az3pveP1c/Vq/T09YUyDI5aBgGbhBs9FJZhnVBmLuk4/VLM3fkk/7EZqbAYIqJUziSrY98f2SnTyd1Gw0hycA+bFePyGaez5FWCit8huHICKMMm7Gma6HtS/MBbGp4B53+EcwPf9ozj3VeunBe8Eh8C8pqCZ3BAeynOdH/kAVQPFw7kaBfI+HOYvVYv0Yy+6xZkoHFfoGezfKq7vTqOO5H4fNOEf4pHdDlr7hdlpzrfW4oTvsL5vx+knz9pvcWryGUd187m+l70BMS12FOh4YWyQr4J0Z6AdLvH3EOZYEMzEvVmDT99KhR5Jfmh/lBsLr+t8+t/9MJnnE28n07E1AwVz7qXmqLbqq+OYa5dLcv5BSYF00BlV8hEnsdrnM6fZI3gYQwzdKGJaf2EMh5VMZ8rUma2onvsws2PWySCr5612+Y7bKfYsUNtV4KtOZ293sjvHPQhseSsp+aNxtO/l3IkWn8nOuct/AC+hncTsCbgYdwdNIJjfkuxQZU0rwvdhpvszAT8U3D9QyYeXD1FH02Emq3PkzVMh3fASFP467RNNoUrOpjoU9DjbGc9+rXEeoO4N9zCe7RR3BgxsIWzmYTTjV9xN7qcwmj5kiA1wzXgcxhn4Kgu9O+jWT6EcbfI+9brF+oCBjdhhsfF4jjPArgvJvj6M8/hKbBPzoVu8T/yAuIFTXcTkuQQnfUG8GlXuIVS5F5iub8KQPonv7fdEDRjO04qhzk0kGX4uWkAFlbEouJnzt4Nh7UXhD+FNF/LE5oRz8WOr8CmXhHeGtTD3lehxjeDbdeHL8Pa36Lmb6brbYex7wNd7wtYHwtUPhqnrCZc5lSczbwIM/Qz4+XTY+aVw86th5jcl3sFDG6hsk3MHF6iz1B/BNJ7mia9XN5Bl2sST/0jdTjIvhYRiH22QdhAdyZUTwMdpP2CtLyPHu1gbCPY5WB+p67qrJ/Sj9OP0QjjJGfrZ+Dsz2d/z9AX6T5hI99Gz1uiHGqphG75xuOh4E8Bsxca5otdeYVwLvliC334PDsm75GgOYGLta2faw9Fbp6O6vGm/S/de4TzqbAaBplKlV8jcH+rZXsh0ne5tABWncKL5Hf80MrQDEscmzkzcBsJ9gL3+Mj27TfDHQGVRV4b2ONDui9r7msPkf07foZfvTvTsbfZgmpxmnidnmR/DzV1nHoY6/qz1ovUr6xN48772EDuQr8f8Jony3GfZRWfBFmZ7V+EXNaDXrkdtHB8/NT4Tz+26+CZc/W14VRn+YH9v2LFLYqmVPrGB61LaBiqF7OeL1CVqk/o8q95N66n104ZpMbKhE7R7cVNTcJ1z9EX6nczPJv0dEgoprGQMF6TEmE7Hu9SokLPwN9FLloKW7qWfrAIpPY1Cup57esNoAx9vMT5BC/8S96m7mW72g30cyCqPMk0zZuaiQ44Vv2AyJ8POMUvJCM9CJ68EMSwybzFrUMuXo7DVsxpN5guci36Nmn+HfrqV80C/MxU4XZrV28pER8+xDoX52paPmp5vjbMKcRWKmMTTrAvJa86Bf15H/11sLbHutGqtB0h+P241sro=
*/