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
ihsKPW3XUNXKlcRF7Eg8QqGgRD10AqbTSvGgpKVqQU/M+SeOTqkX4KC3v6kBPmU1r39FQ3E3+wkBQRMgAsiP7Fv7eAptHCjt1n1EFkNCyuViZVrBiXomBws2eRPrwzgVlqQZDGxXWDDYYb7FgwRAtgLtxzqJYq5GprTOLAcTH/wGbW11CxDosHgu/nQ7eXw0K8sbe/bsEmIn/0yDpNvt6aRc7/O1BndUbO70PU+7LNvJy7WER3y5NCxElj7vi9OWPtsQ1vceXSBtREbXZbHV/E3SudW8Tqtm8BmoEJeKQRJGkbaz/roHKZhTZzBBGwlqM3tgsk7Vtu+i6tJe9sNBgbbMgHjL2+ryeBYSRfWwAzA1qKP8eMSo1amTkxd4aCFN6XzpkvqumP3WPKS/0bb5P6gFFgCJ9ACJBQWg3MRc6bS/KMTlA39Krj3gNRaWKyY1HqE6FwONSd4rVro8LVgF+MCuM2u06OKAuYAz1aUtMCWYjXoFJpmHEk/wUu2DZWjN1PagqGdvMXEHtsYIeeZMom2VM+ovPQM0lzKZn2jRChgDjUV1oKMU9k+hUtqmFDClQBO7+tsnBOx9/W0gYk1yMDu5krqaHJ8J5CFBfKKFLPJKwbGtjs9wiy56n2YdFB+kUxNJ9sGQaW3shQv0bk9wsVV/GjIPA4nc9d8QljRSreiYHQDBos7xWbDajX4/n8bS8c0DUTp+xajRsYUK
*/