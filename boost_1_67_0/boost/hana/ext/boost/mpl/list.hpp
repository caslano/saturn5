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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_MPL_LIST_HPP

/* list.hpp
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
*/