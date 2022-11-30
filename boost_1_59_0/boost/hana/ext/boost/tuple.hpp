/*!
@file
Adapts `boost::tuple` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_TUPLE_HPP
#define BOOST_HANA_EXT_BOOST_TUPLE_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/length.hpp>
#include <boost/hana/integral_constant.hpp>

#include <boost/tuple/tuple.hpp>

#include <cstddef>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost {
    //! @ingroup group-ext-boost
    //! Adapter for `boost::tuple`s.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A `boost::tuple` is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of Hana's tuple.
    //!
    //! @include example/ext/boost/tuple.cpp
    template <typename ...T>
    struct tuple { };
}
#endif


namespace boost { namespace hana {
    namespace ext { namespace boost { struct tuple_tag; }}

    template <typename ...Xs>
    struct tag_of<boost::tuple<Xs...>> {
        using type = ext::boost::tuple_tag;
    };

    template <typename H, typename T>
    struct tag_of<boost::tuples::cons<H, T>> {
        using type = ext::boost::tuple_tag;
    };

    template <>
    struct tag_of<boost::tuples::null_type> {
        using type = ext::boost::tuple_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::boost::tuple_tag> {
        template <typename Xs, typename N>
        static constexpr decltype(auto) apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            return static_cast<Xs&&>(xs).template get<n>();
        }
    };

    template <>
    struct drop_front_impl<ext::boost::tuple_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::tuple_tag>(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::boost::tuple_tag> {
        static constexpr auto apply(boost::tuples::null_type const&)
        { return hana::true_c; }

        template <typename H, typename T>
        static constexpr auto apply(boost::tuples::cons<H, T> const&)
        { return hana::false_c; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::boost::tuple_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c<boost::tuples::length<Xs>::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct Sequence<ext::boost::tuple_tag> {
        static constexpr bool value = true;
    };

    template <>
    struct make_impl<ext::boost::tuple_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return boost::tuples::tuple<
                typename detail::decay<Xs>::type...
            >{static_cast<Xs&&>(xs)...};
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_TUPLE_HPP

/* tuple.hpp
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
*/