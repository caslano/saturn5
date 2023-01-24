/*!
@file
Defines `boost::hana::slice` and `boost::hana::slice_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SLICE_HPP
#define BOOST_HANA_SLICE_HPP

#include <boost/hana/fwd/slice.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Indices>
    constexpr auto slice_t::operator()(Xs&& xs, Indices&& indices) const {
        using S = typename hana::tag_of<Xs>::type;
        using Slice = BOOST_HANA_DISPATCH_IF(slice_impl<S>,
            hana::Sequence<S>::value &&
            hana::Foldable<Indices>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::slice(xs, indices) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Indices>::value,
        "hana::slice(xs, indices) requires 'indices' to be Foldable");
    #endif

        return Slice::apply(static_cast<Xs&&>(xs), static_cast<Indices&&>(indices));
    }
    //! @endcond

    namespace detail {
        template <typename Xs>
        struct take_arbitrary {
            Xs& xs;
            using S = typename hana::tag_of<Xs>::type;

            template <typename ...N>
            constexpr auto operator()(N const& ...) const {
                return hana::make<S>(hana::at_c<N::value>(xs)...);
            }
        };
    }

    template <typename S, bool condition>
    struct slice_impl<S, when<condition>> : default_ {
        template <std::size_t from, typename Xs, std::size_t ...i>
        static constexpr auto from_offset(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(hana::at_c<from + i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename T, T from, T to>
        static constexpr auto apply(Xs&& xs, hana::range<T, from, to> const&) {
            return slice_impl::from_offset<from>(
                static_cast<Xs&&>(xs), std::make_index_sequence<to - from>{}
            );
        }

        //! @todo
        //! Since we have the right to specify the same index more than once,
        //! we can't move from the elements of the source sequence even if it
        //! is a temporary object: we could end up double-moving. Perhaps it
        //! would be possible to determine the indices from which we can move
        //! without incurring a too large compile-time penalty?
        template <typename Xs, typename Indices>
        static constexpr auto apply(Xs const& xs, Indices const& indices) {
            return hana::unpack(indices, detail::take_arbitrary<Xs const>{xs});
        }
    };

    template <std::size_t from, std::size_t to>
    struct slice_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::slice(static_cast<Xs&&>(xs),
                               hana::range_c<std::size_t, from, to>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SLICE_HPP

/* slice.hpp
Zn1q2BNpid0QQF7WVI74VLGnOiGu5SeBOUyOLMvbZ/Oga1xeUBBqRIhJqzBph/j9wEQWwjKlYS2bqYRRlQs6Qidh6C5qYFB4bFYVkkIaoJmc24Glncv1PFLts0IxTW6HEfBYbJ4E4oUyPR5FNMy2Ur0mF8aG3TeZE7UnJ0JU1oSdh0jr9VDOnkC4HBlQDvYwAuXCjhQZBTZwJlp0Q0B4b4HvdrgEBp0dWFcCn8nWa/bhKQCEpFG8ILm8OSWUwx9nvYT5AFOPbEM4nq5NzOJFa1U44ZPjXIqmT2/cxj7cb7vw/21UEIn26nOAy1M6EdFxcpR7I0Il36jOQR6l7GdWMBeychFYOdQ8R+T+HesUbVSlWdH0+hTcWDL86o/gJhFOplYD9y89YDEiGluMqErNAFvfBExXaECRhCZsfBzaYpZs02XrA9GyyFOfJ8vilZtVchVIcihPq8mpa/h8ET9QqsUy0uMWpaz/R1ishMgQpEG2KQ2yTWk5+B7YDIKFWoDa97qMxmf7eS0easT2Ck7P1ZWrlRFBQUDgH5A4LkivATFQam75evl/2/KngraXh5ZY6biWLztotjVFdhiT0esNnLY1DdTrs7DFMkIrer0RA5AVKA9HYyHVJkFVNigMe7OciSLj6aAZC05CJd9BMwzdyOrsxWBTWhYW1nbMFdCUL0HEolpK2TczMCGuTK+Pxp3qWoGGGo+P+hzUtnDQ
*/