/*!
@file
Forward declares `boost::hana::drop_front_exactly`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_FRONT_EXACTLY_HPP
#define BOOST_HANA_FWD_DROP_FRONT_EXACTLY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the first `n` elements of an iterable, and return the rest.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` `xs` with a linearization of `[x1, x2, ...]` and
    //! a non-negative `IntegralConstant` `n`, `drop_front_exactly(xs, n)` is
    //! an iterable with the same tag as `xs` whose linearization is
    //! `[xn+1, xn+2, ...]`. In particular, note that this function does not
    //! mutate the original iterable in any way. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //! It is an error to use `drop_front_exactly` with `n > length(xs)`. This
    //! additional guarantee allows `drop_front_exactly` to be better optimized
    //! than the `drop_front` function, which allows `n > length(xs)`.
    //!
    //!
    //! @param xs
    //! The iterable from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the iterable. In addition to being non-negative,
    //! `n` must be less than or equal to the number of elements in `xs`.
    //! If `n` is not given, it defaults to an `IntegralConstant` with a value
    //! equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_front_exactly.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_front_exactly = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct drop_front_exactly_impl : drop_front_exactly_impl<It, when<true>> { };

    struct drop_front_exactly_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_front_exactly_t drop_front_exactly{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_FRONT_EXACTLY_HPP

/* drop_front_exactly.hpp
vNRoNdtZUcx/Z4IemETkDRPzd2/GdLr9bNI8j47klWpx2CwWKgYEc+qw9Ipe7EqpXrCKl7p4ygBita80tRYmdB6fshTpeCNbc5rmSXr9iPEb8TlhvyUr0X4Leorl2dWyoQk30nzyQPn4ujdp0Hg4ES0/gcvfDlpntzfspFXPXvZ2x1bIiW5Hmzu2WgNpEPZG+9m3bIXcab8ptCN3j6LpcvncNNzE96sDLX5m03ivfENbmftKtE9v/41YEYSlbzloAJh9lWpQUbh0j06E48hy9cCw7lwvK0ETMLAzFNvtFnIb41xSO7SWawrsL4TWGAhFxsQlT6w6RzsYmHO8go5KaeuSSVuXdNq6BK4kqFGmOEPTPJiiBh9zGELDbtH7zCqC7i6no6wx+ML1kPmkopynaWzMxBblVkZR3AAh3LjMlLRgkKgZuyROQeJNe8N+hEiTTUkrGPPgM+PQR21SaVwWKIUEov0VB6miG1hw9vxUZst4i8JjjDhtPGi48nzwmy0SF3OjoPD6ntqg4ExpPok0z6bWJ6eR9DSjpC90BaKmkLEddaqYRdM1E6/gNPmdOjtlv/ZZo/1n9lH1CahJLHkCCaiQxzZZxrjhXbWPxvWd3d2pweRxCWdZEeg9eWKT6ZDkukZWvzeO4K7pRSO9Pa802Z7K+SnvNfnxd90+wwjw6wx0gesw7+JJZM+ezbKxj4TqTr+p48T+chHIEu1rrLDcRGociv3RrR7eVm4W2v7FYXQAtpd5g01k+slDeEJOJxlhfIqtL9uzhCSUS/L4Y14R8aW0pAhwsHbagsHe5XOCkbkEVi+nxjrV3dLYogrbmtG0W6qg3RLiHgBPrRZXhpOlPlRcTkJxmVxcBhfnatEi5GlZDKKAIrY7AQR4irGq1pgeMIndBO23hP0Kce62zagSlFW/rbPRLSItLxjLKa4WVevdSa5Iz1h38GKwpHT2QVsT6iUANTipjfb6LyEJ27evsxnkOVbNOggdPdcFyJ+H3wiF7Bs+l+AHtJAdpigPZgu3x350ggHtB+h0IpgTOg6ySUwoFfsA0l43ZkfRHvv1j1MQijVvZZ66NatUhTYnjPcir612E6EyFSmsutxTzGfixarVcbpYfz+qZLL8Ozx4KJWqcJ5bpTwwTHVQmYW26Ec9xCPXzQcTjCt0FyU04sqT3Ii/D9IbgcrLPDg/yGAwp4h9b+40cMQMI56L5thq/xi1L+AtK/c68hSSVRpTsI9HGdCP1wR08kAx8nonnxQ+1PK0wVqTZXLMHWRyNOM3G7+5+N6C56JB/328qd+QpKxInj2TZFUScD45yXFTYhI2pVlK8/FMucRJ+9S5ial51xFZbyJ9C5x3p4e+aTEG+oRwkm2h+9ne4rRgP9mIwzu2SVUYHYwEJ+g5mAlFi/GhVgsCTXLhnNBJiN+/xeL3P24YAlJiJFNyy23tdKzi2unqaCcFc9kI9As4qJDAIACTGfpmlqEuk9UH6THw90bMWLKoJTxAfdG1l5Rhps7Ls9nLtrpj45Vzpqs3srvE2IaqMetQEDoFUs/hHRU2R4C2fiSy6IPrTMKSazOwFjViwsqT1Eg7yeC8EL60foupNymy/MVpcoxGW+z4Tsf3ObzvcNKz/kX8Z4tzQr9xnLjwllXtrcJpQIKVcZq72vGs4kCz2OI4tSl0zBEYEDo2IICnzkDGI9yfJtdh8qdsFQuDNRI6eTLYj4mlqwPT1IoEO5mHhJSWnZvby/aRXTVMSj7K85AZnOuH8LonHOURtZnMCmg3iFmaK6g/DMCV8PIJzBGU0wN+PEecBMLrNVdvnBx9vWYBmZH71PQHWf8VY3kladEu9RFxoq5iyWUOEdpr08RViyw=
*/