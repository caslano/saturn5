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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_UNPACK_HPP

/* unpack.hpp
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
*/