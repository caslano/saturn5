/*!
@file
Defines `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_HPP

#include <boost/hana/detail/nested_to_fwd.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_to_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(Algorithm{}, static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_HPP

/* nested_to.hpp
Y6Tf7avWEdXjrjT5G32L6+9O9QwNpnDd3+CHgJ9g8X3Kz9+bziF8EcpqpXlpgM8TPn+YPnbJDXX3ZfR5RTGkHSNThB8qRzq6mvZIq6jug0zPJ8s3PpTnfcozRHlWV5U4dy11p9+8bzM2jPSKtSn+urvyvpgbeDuR6R/qZ+8nQg4UqmF2Lj+Uz+WfIjbeCrZ+PUz0rW9U4SP61uGkgyOY3jppzD1WJHalztudzaobvbY+Ii6GL76j3g/441mqGXA5dMphaby7wAsjrBf8tN2ZArH1w7M9hbTFMHgOADf8BqF4nsKc2QT1xaMcBqPHTsPg3f05A+PxM9XSCdSyPOAKPeo0DrBhvDOHpnuH4VZn8hlPcs5n2dwgHahFhz+N0HYDJlbXN6tsu2gnN73ZR0cvP6pqZPvRuiL70aORX/rOj+FjXpeLDHYzagGmz25JvLXvK9Xeh9vfK7J9eLjkxQX4NuMJm5TJdg8tc7npr+Bj/N0iLiT19Ym0Bj+e+vp3hB19TMwBJxDdiWxMRJlv6GQxrtZX4SPG1SnE43uirB2FzT6N6E5nZb0p6vF9wztEZymU5yyzl+D+10+5HzK+2B+6utI59iP9n10V5IsVnNwGKYJjb3zOEfU/h+pyLqv/h8yGnS90fUEVPkLXFxKPHwtdXyra9SdEdzErq17k+RnxPo/miEsoz6VE18x1/RnW2UbfP2f6biV9Xx6ob8lMK7wIUvts5J7AO6NlYgbAWXudL9YzV5A+rmQ6nMPGxlWiva6uwke01zXE49dEe4DPvnh+6jBSZWrezMNQWhi9OySYfbcHWH4l349p33Yz3R28luk08qniNyHWnliDXGf2+NRXrqd63cDWXwewve5NbN33O6Gn31fhI/R0M/G7pWrD795Hfg8SMRCZfPhu5btDjIU7SZ7byX7eRfLcLejeF+PsHuBdfbE+sljYtPuJ96Wkuwcoz4MsT6vI87DYLzxCeR5lebYWa75tSbbHqQ5PUJ4nRR1uF7yfJrpnGO+pIs9zlGcU2eXnKc8LLM9NIs9LlOerlOdlyvOK8R+O4I56tAMDvaGzQ1+8KIKjtn6N+P72M93ZpdtdXX127fE6+OId6FBhhfvo0dLWEi1d8WVrFXNPRuM5n1lYP3mc3rdxDOc6OoZhM73feoPvrT/F7wTsxW33RtpDY6//yOx1A9nrPwXba3FBJgBObdQm+vnb1Ecepj77DvWRP7N+tZLtwd8TtuT9KnyELfkL8fir6I+rhH3/gOg+FHTXiTH+EdF9HDQvfoZ71EbPnwTMi/8svQ5pLL4QsUhry7dhc9a/hf6ciP5w/Y2K6PqOjmhaspeWR1nEz2NsBB/Bo5x4jCPa+sB7fClzd2/Obm5VWNqcCQgbtwmVcwydmWxK5UyIiLeJwsZtTnRbeHSh19l8VSnyh6mcN8h2VVH+CNFRHquTaqGTSRF8hE5qiMdkxmN6SPjSKU8F1W8ryrO1kA94X/22JbpaxntH0a/riPfXiPdUyrMd5dlnw3d7lLsi2IlB7TWNeJW4J6QDGHSvKwh2EmH77/SI/0xnh4jihbLZ3cQdI+5aqZtg9q7cjAjrb5/inpLWsb0TYdt3M3kvAe37RZTF4/je6XjxO3LlgBE98rr0syJ+fmHBr972H1u+vU8xKqTzOCImwu6UJ0z9IhEyeBtnoMj52lCGbgiYuYUDbFvsSW0xYGOndMZxOt7WGnModopKtyfaFrV3eLFTAKMo6gY2xoU1tLWpOISOhpUpmL7+SnFUkFar/bYEZB7n+pxVPfaOOMDYpSt22HkdOUUAIXSRN4ip5nhLrCNO8WZsiuJvrKL2qxiN9mPprdCe5aP4He3eNc2ZvnQ=
*/