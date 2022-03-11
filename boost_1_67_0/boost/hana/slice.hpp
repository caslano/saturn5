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
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
*/