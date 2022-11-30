/*!
@file
Adapts `boost::mpl::list` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_MPL_LIST_HPP
#define BOOST_HANA_EXT_BOOST_MPL_LIST_HPP

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/mpl/integral_c.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/unpack.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/size.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace mpl {
    //! @ingroup group-ext-mpl
    //! Adapter for Boost.MPL lists.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! It is possible for MPL lists to model a couple of concepts.
    //! However, because they are only able to hold types, they lack
    //! the generality required to model concepts like `Functor`,
    //! `Sequence` and other related concepts.
    //!
    //! 1. `Comparable`\n
    //! Two MPL lists are equal if and only if they contain the same
    //! number of types, and if all those types are equal.
    //! @include example/ext/boost/mpl/list/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding a MPL list is equivalent to folding it as a `Sequence`.
    //! @include example/ext/boost/mpl/list/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over a MPL list is just iterating over each of the
    //! types it contains, as if it were a `Sequence`.
    //! @include example/ext/boost/mpl/list/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! A MPL list can be searched as if it were a tuple containing
    //! `hana::type`s.
    //! @include example/ext/boost/mpl/list/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! A MPL list can be created from any `Foldable`. More precisely,
    //! for a `Foldable` `xs` whose linearization is `[x1, ..., xn]`,
    //! @code
    //!     to<ext::boost::mpl::list_tag>(xs) == mpl::list<t1, ..., tn>{}
    //! @endcode
    //! where `tk` is the type of `xk`, or the type contained in `xk` if
    //! `xk` is a `hana::type`.
    //! @warning
    //! The limitations on the size of `mpl::list`s are inherited by
    //! this conversion utility, and hence trying to convert a `Foldable`
    //! containing more than [BOOST_MPL_LIMIT_LIST_SIZE][1] elements is
    //! an error.
    //! @include example/ext/boost/mpl/list/conversion.cpp
    //!
    //! [1]: http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/limit-list-size.html
    template <typename ...T>
    struct list { };
}}
#endif


namespace boost { namespace hana {
    namespace ext { namespace boost { namespace mpl {
        using list_tag = ::boost::mpl::sequence_tag< ::boost::mpl::list<>>::type;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::mpl::sequence_tag<T>::type,
            ::boost::mpl::sequence_tag< ::boost::mpl::list<>>::type
        >::value
    >> {
        using type = ext::boost::mpl::list_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::boost::mpl::list_tag, ext::boost::mpl::list_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const&, Ys const&) {
            return typename ::boost::mpl::equal<Xs, Ys>::type{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::boost::mpl::list_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c< ::boost::mpl::size<Xs>::type::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::boost::mpl::list_tag> {
        template <typename Ts, typename N>
        static constexpr auto apply(Ts const&, N const&) {
            constexpr std::size_t n = N::value;
            using T = typename ::boost::mpl::at_c<Ts, n>::type;
            return hana::type_c<T>;
        }
    };

    template <>
    struct drop_front_impl<ext::boost::mpl::list_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs const&, std::index_sequence<i...>) {
            return boost::mpl::list<
                typename boost::mpl::at_c<Xs, n + i>::type...
            >{};
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs const& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(xs,
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    template <>
    struct is_empty_impl<ext::boost::mpl::list_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&)
        { return typename ::boost::mpl::empty<Xs>::type{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Conversion from a Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct to_impl<ext::boost::mpl::list_tag, F, when<hana::Foldable<F>::value>> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            auto list_type = hana::unpack(static_cast<Xs&&>(xs),
                                          hana::template_<::boost::mpl::list>);
            return typename decltype(list_type)::type{};
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_MPL_LIST_HPP

/* list.hpp
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
*/