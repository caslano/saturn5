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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_TUPLE_HPP

/* tuple.hpp
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
*/