/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename hana::tag_of<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            hana::Sequence<Xs>::value &&
            hana::Foldable<Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take_front(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_INSERT_RANGE_HPP

/* insert_range.hpp
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
*/