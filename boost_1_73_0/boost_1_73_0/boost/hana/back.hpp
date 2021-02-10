/*!
@file
Defines `boost::hana::back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_BACK_HPP
#define BOOST_HANA_BACK_HPP

#include <boost/hana/fwd/back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr decltype(auto) back_t::operator()(Xs&& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using Back = BOOST_HANA_DISPATCH_IF(back_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::back(xs) requires 'xs' to be an Iterable");
    #endif

        return Back::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename It, bool condition>
    struct back_impl<It, when<condition>> : default_ {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(len > 0, "hana::back(xs) requires 'xs' to be non-empty");
            return hana::at_c<len - 1>(static_cast<Xs&&>(xs));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_BACK_HPP

/* back.hpp
dgjW9kv234UDZ687J5RH0R0Uo7qSybe3l6XYKiZUlZmx6967i/6od6L0qgJndDHBQPQoAyVHrNTusQre6YuvZqhR75fhzw8YSrbbZCgNYRsPp7XdZMjBcGJNRpfjyQNmqLXdZMjTy8nlqLfxaKJZNlBhvV70eiPrtNM/650I522/S+63bNmqPdiwhrCobOHr6ydrCnybb2w3Qj0t2oXycDYIFfyGwbTnT398dpwL1R1xeBGhAJUsdBqyqhY4fySqaAkTmtS+nFjDU+u8dz4cvc+bGLKOpmFD9NNS0AB2dxjYF2o6TfaKtY12ycliHlG+Dk4aS45+D6RxImE7zkhtan8p7oLBS32gp0KSlJfr+nvCkSQEe8x5Q+tb5cDpqkUmFwKBZwFDKdJRDCxpKpgoKJ6pF/3+VjkX+UEjRkb8T59Y9gMUFPt2LzI8w4PwSy1Pd0GImXsJ+dToxIGGoCUmaKY6gd4EC09KVaz6WYCLZqgjuOog21/BmtR5K1qbrcyZbJHqDDdp3O5sukMKT+2Hi1gphApnV9yx0eW07Iiu3BPRj4BO5SAMdkUvUKFF59KD8HYv8ynJ48PXYLgtrvCirv3O6Bz735eD7ANmFzzZf/r35wb3QymjDgBoRPmSkHQtP0CiLqcq4mA5OSsA
*/