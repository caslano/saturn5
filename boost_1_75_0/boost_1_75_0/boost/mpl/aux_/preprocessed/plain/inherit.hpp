
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
9jBzH4WXROXOfegFt5OElANeOZDKtZ1znBFwOHc8401ml909mEvOSgQgP6s/YvgRgRFYJTghytckN8hyxh/PCeB0fiEvUX9fz/YU94gqEsBZpEJaOinbft4k/jhbvaF8ZPU2KIJOb05vzgKmADMAont+tj56xdpRucaut6DzsDnc6R7xRe1tUcUVx5fk7PmG7mRoIlSNtcpwYZb/68dVsMt2WQT+PWdnaAlmz/yygV6wZ3qqS0+42poxBiFQI/2VUF6gtSTsOgVcz2+Ytd9NoGdVzg8YSH9SzObVzMLvnp2Vhy2GsnnW6R5xznqJOwjwBkE5owSIZPc5BBbdaVKRhpj5553e/ySo5xEX0WFeB49Y5HJ2Cpzl37yadv3NSyWrXSzps6DI7PCJ5riDfi2SAiaYp8/qoT2qKOurqId/ZUl/q8UOnMqTZsWkvsJoHO4VCLS8UY2t8WxLb1HwNSqRYO1K3TkWEzj+6Urp1gkjTL1+/W9BGOMwo48VxvUK0WarZ8J5TTjdByeygpTIYd1eh6RLqckGN7fweAxrU/n7TsYEJdmsNqzEgA0RUhtqWWo8V6mZbpclLuZK1OPWiSJsN1KjXXLYAXUjAcvaW/ZwG9F/F67p/l24/iR8bWtTMZZ2/E7X+3CKFn3ClG3JesbzuuSZ71LLnLJqYMSFparEYUm2/EhqzclrV6Tt+50ZDFuNIWDUS5VX6VHdneR2
*/