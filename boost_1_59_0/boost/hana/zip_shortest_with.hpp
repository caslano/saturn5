/*!
@file
Defines `boost::hana::zip_shortest_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_SHORTEST_WITH_HPP
#define BOOST_HANA_ZIP_SHORTEST_WITH_HPP

#include <boost/hana/fwd/zip_shortest_with.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/take_front.hpp>
#include <boost/hana/zip_with.hpp>

#include <cstddef>


namespace boost { namespace hana {
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto
    zip_shortest_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_shortest_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_shortest_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S, bool condition>
    struct zip_shortest_with_impl<S, when<condition>> : default_ {
        template <typename F, typename ...Xs>
        static constexpr decltype(auto) apply(F&& f, Xs&& ...xs) {
            constexpr std::size_t lengths[] = {
                decltype(hana::length(xs))::value...
            };
            constexpr std::size_t min_len =
                *detail::min_element(lengths, lengths + sizeof...(xs));
            return hana::zip_with(static_cast<F&&>(f),
                hana::take_front(static_cast<Xs&&>(xs), hana::size_c<min_len>)...
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_ZIP_SHORTEST_WITH_HPP

/* zip_shortest_with.hpp
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
*/