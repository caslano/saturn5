/*!
@file
Defines `boost::hana::detail::variadic::take`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP
#define BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/variadic/split_at.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/functional/reverse_partial.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace variadic {
    struct take_impl2 {
        template <typename F, typename ...Xs>
        constexpr decltype(auto) operator()(F&& f, Xs&& ...xs) const {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)...);
        }
    };

    struct take_impl1 {
        template <typename ...Xs>
        constexpr auto operator()(Xs&& ...xs) const {
            return hana::always(
                reverse_partial(take_impl2{},
                    static_cast<Xs&&>(xs)...)
            );
        }
    };

    template <std::size_t n>
    struct take_t {
        template <typename ...Xs>
        constexpr decltype(auto) operator()(Xs&& ...xs) const {
            return variadic::split_at<n>(static_cast<Xs&&>(xs)...)(take_impl1{});
        }
    };

    template <std::size_t n>
    constexpr take_t<n> take{};
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_VARIADIC_TAKE_HPP

/* take.hpp
PTvIjinj2PdkY/dvIXqg+x8Us9iJ8Mbj3qWIlgVNUQqvxuAYHy4GLg7GG+GB0BJsY3nAEQ582yCWYeyplbHZ4/Fgh7y7Qz5C27KxpCcxD57zl8RaknPWm+aMYtvY9q6+ZBciOWamyJ6T6WFzA3N1ybLtkSZ/RqqT/CRJd4iRnTKT6pTtkf+4tx9lF+hZtrVjttPuzvZZGKdL3PUGAZAvEZ35yHveBhA4Ne3TO7O5SEvi3vP0LrQhYUOM+tuFYy/frz3YaObnUtwjf7ZsGx5+1bAMS5/9aaaxuJaDyBePxkg2tCa8KIFNTND0756cYcGMKO5iEN27zjLqL6k16iypdb2tf02Ge16H0rwOI7rJ5XdQk+yj/H4X+t5qZwTSnNZ2pXZGUjnlrmuNDObF7Oa1HCJbsc6gR2Ub5ckhELyS9hK7u9eYsdcwH/6P0pszdSrQvkPbIpxYTdaZ0FnpsqaWmSXkU+vwudaWIPku7iF5G9m5DiC/xJxsbrMaGpD8oCiELUy4BX5GQ6Ft4syzoANcJ5BruhFtogx6yfs4uIt9zPXo41jWx1Gb6OOEJPo4Qemj6GIf92R9tPy/x7vmU2ne6JMCQx887fNJfmu8BUm0eXAi+RmoxsvBxtMQpeFQXIaf6FAq3lQhW85OYnJ2b2r3gM7bhdyJQLqZ0lVGykB9udRqZ0XsNiezNqdQm8td/K2VfHO5fhSjuG/cD7ShkS57G7CJRl0tCp7N8vsgL0O0GPhgmUbeVOQNFi3GQf8BdFcyj8370C02dpxR0Hg5nfbrIp0WeqylItbf7M7X0piJm15LYyYqa2n7LvaxxKOP01gfh21ivY/ZdB9zxyh9zOhiH8s8+jidz/sm+piTRB9zpP+Gurfgssb7nN6UK7PHj1O0ASUzz1WJ+W4Dl9PM75hgMt7RXPKzlnuBcgATNk1rDWXwz4YLM25ieuoMib8kZKaMLWHul7EG6O+cdOfvFAbfJ+VrO05hpdFuUaiF4vxWGema0ML2kB1fZz/A0pQ70tUSZvgomDEG5pEuX8N5+Z+E/0kixfNNSOwUXPaemY65B5mmbWF84m/rg42BBngaGJ9aCfrS4CszSS+1/j6J6UCzs52Y4TJvFn5kPPH9CR8oh28cnnwg/h7Fvj8owfd/oe8tm1qG+Ta2R1lYZKismsdjl2fJ2OVo8ADA5e+DjT5hfy/TcqeE39QntGXWJevBDxks8UKfdzvcJmziiMYoyzVl83I2Xrzy7DH3pb7Opb42WzhK5eWd92ykDUBk+ESdhAPPvUGR9fjbnljMv7RTNwIWkEfPpi4daELQtYAZ4hwG1TYI8gjewemuhVDucPtjWR9u1QEmn0WSEmeykPX5jHIB88ghsKjJ9ANoQH6gIRJrhYA12+2nzaNxwXwbaigKRYpQRualSmyJOkmb6N1wfT6Vi+D3wCRoc1LnNC3XU7iRvrSS1rfTE38bgOYcDcTb2sKBmBS0ZuMbQZ21JecmJvGj0grRQ4ytn5iyfuKM/mXeQqL/VrZ+AHf8OJT1syjB94vpe1eeul6IztqIzpbQmuhQ6/Sg8Rij8UOzeTm77555ixUaP4zaPtymcSqv0PglRONRA27Sc0sS9Nxb+jcb5dRJRR2g9UMkrW+cadD8ESrNg5aXedOyQU89QMNHchreTHoq6Jyu3bzeBaE66AzkaEZ3Ryt0dyybY5l3DNHNckZ3gNt0d7xCdyck+H4Ffa/kES92091xNPcnEg8+Sa3Tg+4At+nu1Gxezu67Z94Khe5Oo7ZPt+mOyit0d47KW0FPJ+NvF9qJlk4hvulkmHR0hgfvPCVJ3nlmAnorIHo7i9PbZtBIhNnSMEbbllbH5v48Ze4=
*/