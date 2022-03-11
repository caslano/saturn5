/*!
@file
Defines `boost::hana::intersperse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INTERSPERSE_HPP
#define BOOST_HANA_INTERSPERSE_HPP

#include <boost/hana/fwd/intersperse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Z>
    constexpr auto intersperse_t::operator()(Xs&& xs, Z&& z) const {
        using S = typename hana::tag_of<Xs>::type;
        using Intersperse = BOOST_HANA_DISPATCH_IF(intersperse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::intersperse(xs, z) requires 'xs' to be a Sequence");
    #endif

        return Intersperse::apply(static_cast<Xs&&>(xs), static_cast<Z&&>(z));
    }
    //! @endcond

    template <typename S, bool condition>
    struct intersperse_impl<S, when<condition>> : default_ {
        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&&, Z&& z, hana::false_ /* odd index */)
        { return static_cast<Z&&>(z); }

        template <std::size_t i, typename Xs, typename Z>
        static constexpr decltype(auto)
        pick(Xs&& xs, Z&&, hana::true_ /* even index */)
        { return hana::at_c<(i + 1) / 2>(static_cast<Xs&&>(xs)); }

        template <typename Xs, typename Z, std::size_t ...i>
        static constexpr auto
        intersperse_helper(Xs&& xs, Z&& z, std::index_sequence<i...>) {
            return hana::make<S>(
                pick<i>(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                        hana::bool_c<(i % 2 == 0)>)...
            );
        }

        template <typename Xs, typename Z>
        static constexpr auto apply(Xs&& xs, Z&& z) {
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            constexpr std::size_t new_size = size == 0 ? 0 : (size * 2) - 1;
            return intersperse_helper(static_cast<Xs&&>(xs), static_cast<Z&&>(z),
                                      std::make_index_sequence<new_size>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INTERSPERSE_HPP

/* intersperse.hpp
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
*/