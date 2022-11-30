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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_INTERSPERSE_HPP

/* intersperse.hpp
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
*/