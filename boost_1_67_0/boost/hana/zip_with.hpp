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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_WITH_HPP

/* zip_with.hpp
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
*/