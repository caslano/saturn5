/*!
@file
Defines `boost::hana::zip_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_WITH_HPP
#define BOOST_HANA_ZIP_WITH_HPP

#include <boost/hana/fwd/zip_with.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto zip_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S>
    struct zip_with_impl<S, when<Sequence<S>::value>> {
        template <std::size_t N, typename F, typename ...Xs>
        static constexpr decltype(auto) transverse(F&& f, Xs&& ...xs) {
            return static_cast<F&&>(f)(hana::at_c<N>(static_cast<Xs&&>(xs))...);
        }

        template <std::size_t ...N, typename F, typename ...Xs>
        static constexpr auto
        zip_helper(std::index_sequence<N...>, F&& f, Xs&& ...xs) {
            return hana::make<S>(transverse<N>(f, xs...)...);
        }

        template <typename F, typename X, typename ...Xs>
        static constexpr auto
        apply(F&& f, X&& x, Xs&& ...xs) {
            constexpr std::size_t N = decltype(hana::length(x))::value;
            return zip_helper(std::make_index_sequence<N>{},
                              static_cast<F&&>(f),
                              static_cast<X&&>(x), static_cast<Xs&&>(xs)...);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_ZIP_WITH_HPP

/* zip_with.hpp
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
*/