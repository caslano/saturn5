/*!
@file
Defines `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <boost/hana/fwd/append.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_APPEND_HPP

/* append.hpp
oz8yVtnusR7prHo2aXZ12OoqZlevtvLGSTmFY7Eb8COT/Sl69bOdLJYC5rtP33L341OAAXRugeLyidN4Khlmj5CJ02OdFDOZM1gT/HDC4zwb4GIxZTqVlc7TYfi0E0RE2eUJ/8lLfVaI4s2qKx5a/SVPrFgW5ceTP2vm5EF5g4iCiPKRQkCgV8XszeFgJrQT8xs2E3ISyhjSPqlluZpf9D24mKrHFbAy4nStHJfvCeAVmiGQzyRMFOg5WAGeV7Cl3kFKD3AFqi9MnDY8TCBYeGNVWGrZqV+YxYJHigu7yPTIkaVjKiNUifcPeW+XEpxCIelvIZMB3hLJuhIXawtLzaMgOasD7g5VQZKgpbc1semzDhhsBeRwffaaJgEMDnSoPGjxegkl4+b6YtVNiPjtetdNRG+x4GHuh+sGSBqO3z0f+F4+d8uZ2XN3/RCi468Ye3AE+lxbbJqIoEYM9hIirpsdmmqyCYh+Uos8y94n8hT1pDP11Bwcctr2AByZPWk+A44lF1ziQBU/gRdb3//UmdogW72PgCKzIN3IUCKHp16Jq/iD4Qgak+x37MhsaHoYrZSOqMyZhrhayFpvL5E1kG2QKpAFUOxnTauoDdYkT5AEUBdR+ZGOkcj4YshWGcpMl3886SKzB5wFUAxYkuXrB2hsDIvkXSBKGiHkje0TOeFNS+dykpWiy1HLcP1+CY0OChnsr6galUtv8Qb7
*/