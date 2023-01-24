
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
y4H9PeUZjrhKLBsbyU+SSROQufcnjj8rfYjIHW83od1h5YNUH2zLB494K1Rk0KgoPrKfWmZHIPMIiOT/ioat5NLTZxRM/qiYK3u/JU8XX/2Wo9mQmYDyBz9MVELlmvQ8QNxqNV3xOijh7e/jys9kirSjkePcBDLiF9r2GGgR+5t76PH7HDBMjGWiCNx8EdG+dgfqg/BMeNC7kKk/Xr7fLrpPtcy7WBUgxxM3djzqcZXEH1SidcpbziBSJ/sDnni+C4j7Gwlm1F+cHjAID5skIPnaSPXBN74QSJiSn+XABm8QbHlI4BKsWyZtXYZyk8l/qTW5G/+Akrq0GPB1W3UzR42vB2WiRvU53IQ7DRb/u7q6QsubllYe5b5diS0viu45m+tb0XHmwoHtdYMLpzv4sVVB0xjSUt9UXVnv3JA7vr4ye2xha2t3za1DBiRNS/ThLzZhI9zx1CzechjsmhGKD3VTGWXBW7SWvkGNyjto9PEFuce0KOVb/8ytLu7FE3SSNY05S5OG/BnpaES14NVQlee48x8mX4GTT2ZzJarpZcKUpxpXm3ZJi49Q7gzeJtYZe7EsXsc/ci2sNgguEP1BHF+JlUJgx+HE5hiFvxyYElkLTqarOaI/bR7ctDgKL4zkj4ZWKNEaHVuqBWIwdDtQO0sxuV9gs92qvfo70kWgroQlLp09m11KUxOApRNj65bFJbvTBaM03P4Rl3OP
*/