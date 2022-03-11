/*!
@file
Defines `boost::hana::unpack`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNPACK_HPP
#define BOOST_HANA_UNPACK_HPP

#include <boost/hana/fwd/unpack.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/fwd/fold_left.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) unpack_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Unpack = BOOST_HANA_DISPATCH_IF(unpack_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::unpack(xs, f) requires 'xs' to be Foldable");
    #endif

        return Unpack::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename T, bool condition>
    struct unpack_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return hana::fold_left(static_cast<Xs&&>(xs),
                                   static_cast<F&&>(f),
                                   hana::partial)();
        }
    };

    template <typename It>
    struct unpack_impl<It, when<
        hana::Iterable<It>::value && !is_default<length_impl<It>>::value
    >> {
        template <typename Xs, typename F, std::size_t ...i>
        static constexpr decltype(auto)
        unpack_helper(Xs&& xs, F&& f, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(hana::at_c<i>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return unpack_helper(static_cast<Xs&&>(xs), static_cast<F&&>(f),
                                 std::make_index_sequence<N>{});
        }
    };

    template <typename T, std::size_t N>
    struct unpack_impl<T[N]> {
        template <typename Xs, typename F, std::size_t ...i>
        static constexpr decltype(auto)
        unpack_helper(Xs&& xs, F&& f, std::index_sequence<i...>) {
            return static_cast<F&&>(f)(static_cast<Xs&&>(xs)[i]...);
        }

        template <typename Xs, typename F>
        static constexpr decltype(auto) apply(Xs&& xs, F&& f) {
            return unpack_impl::unpack_helper(static_cast<Xs&&>(xs),
                                              static_cast<F&&>(f),
                                              std::make_index_sequence<N>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Products
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct unpack_impl<T, when<hana::Product<T>::value>> {
        template <typename P, typename F>
        static constexpr decltype(auto) apply(P&& p, F&& f) {
            return static_cast<F&&>(f)(
                hana::first(static_cast<P&&>(p)),
                hana::second(static_cast<P&&>(p))
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Structs
    //////////////////////////////////////////////////////////////////////////
    namespace struct_detail {
        // This is equivalent to `demux`, except that `demux` can't forward
        // the `udt` because it does not know the `g`s are accessors. Hence,
        // this can result in faster code.
        struct almost_demux {
            template <typename F, typename Udt, typename ...Members>
            constexpr decltype(auto)
            operator()(F&& f, Udt&& udt, Members&& ...g) const {
                return static_cast<F&&>(f)(hana::make_pair(
                    hana::first(static_cast<Members&&>(g)),
                    hana::second(static_cast<Members&&>(g))
                                                (static_cast<Udt&&>(udt))
                )...);
            }
        };
    }

    template <typename S>
    struct unpack_impl<S, when<hana::Struct<S>::value>> {
        template <typename Udt, typename F>
        static constexpr decltype(auto) apply(Udt&& udt, F&& f) {
            return hana::unpack(hana::accessors<S>(),
                hana::partial(struct_detail::almost_demux{},
                              static_cast<F&&>(f),
                              static_cast<Udt&&>(udt)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNPACK_HPP

/* unpack.hpp
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
*/