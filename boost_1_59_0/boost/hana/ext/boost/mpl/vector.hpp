/*!
@file
Adapts `boost::mpl::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_MPL_VECTOR_HPP
#define BOOST_HANA_EXT_BOOST_MPL_VECTOR_HPP

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace mpl {
    //! @ingroup group-ext-mpl
    //! Adapter for Boost.MPL vectors.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! It is possible for MPL vectors to model a couple of concepts.
    //! However, because they are only able to hold types, they lack
    //! the generality required to model concepts like `Functor`,
    //! `Sequence` and other related concepts.
    //!
    //! 1. `Comparable`\n
    //! Two MPL vectors are equal if and only if they contain the same
    //! number of types, and if all those types are equal.
    //! @include example/ext/boost/mpl/vector/comparable.cpp
    //!
    //! 2. `Foldable`\n
    //! Folding a MPL vector is equivalent to folding it as a `Sequence`.
    //! @include example/ext/boost/mpl/vector/foldable.cpp
    //!
    //! 3. `Iterable`\n
    //! Iterating over a MPL vector is just iterating over each of the
    //! types it contains, as if it were a `Sequence`.
    //! @include example/ext/boost/mpl/vector/iterable.cpp
    //!
    //! 4. `Searchable`\n
    //! A MPL vector can be searched as if it were a tuple containing
    //! `hana::type`s.
    //! @include example/ext/boost/mpl/vector/searchable.cpp
    //!
    //!
    //! Conversion from any `Foldable`
    //! ------------------------------
    //! A MPL vector can be created from any `Foldable`. More precisely,
    //! for a `Foldable` `xs` whose linearization is `[x1, ..., xn]`,
    //! @code
    //!     to<ext::boost::mpl::vector_tag>(xs) == mpl::vector<t1, ..., tn>
    //! @endcode
    //! where `tk` is the type of `xk`, or the type contained in `xk` if
    //! `xk` is a `hana::type`.
    //! @warning
    //! The limitations on the size of `mpl::vector`s are inherited by
    //! this conversion utility, and hence trying to convert a `Foldable`
    //! containing more than [BOOST_MPL_LIMIT_VECTOR_SIZE][1] elements
    //! is an error.
    //! @include example/ext/boost/mpl/vector/conversion.cpp
    //!
    //! [1]: http://www.boost.org/doc/libs/release/libs/mpl/doc/refmanual/limit-vector-size.html
    template <typename ...T>
    struct vector { };
}}
#endif


namespace boost { namespace hana {
    namespace ext { namespace boost { namespace mpl {
        using vector_tag = ::boost::mpl::sequence_tag< ::boost::mpl::vector<>>::type;
    }}}

    namespace mpl_detail {
        // When `BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES` is not defined (e.g. on
        // MSVC), different MPL sequences (like vector0 and vector1) have different
        // tags, so we need to take that into account when we compare them.
#ifndef BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES
        template <typename T1, typename T2>
        struct is_same_mpl_vector_tag : std::false_type { };

        template <template <long> class Tag, long x, long y>
        struct is_same_mpl_vector_tag<Tag<x>, Tag<y>> : std::true_type { };
#else
        template <typename T1, typename T2>
        struct is_same_mpl_vector_tag : std::is_same<T1, T2> { };
#endif
    }

    template <typename T>
    struct tag_of<T, when<
        mpl_detail::is_same_mpl_vector_tag<
            typename ::boost::mpl::sequence_tag<T>::type,
            ::boost::mpl::sequence_tag< ::boost::mpl::vector<>>::type
        >::value
    >> {
        using type = ext::boost::mpl::vector_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::boost::mpl::vector_tag, ext::boost::mpl::vector_tag> {
        template <typename Xs, typename Ys>
        static constexpr auto apply(Xs const&, Ys const&) {
            return typename ::boost::mpl::equal<Xs, Ys>::type{};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct length_impl<ext::boost::mpl::vector_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs const&) {
            return hana::size_c< ::boost::mpl::size<Xs>::type::value>;
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Iterable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct at_impl<ext::boost::mpl::vector_tag> {
        template <typename Ts, typename N>
        static constexpr auto apply(Ts const&, N const&) {
            constexpr std::size_t n = N::value;
            using T = typename ::boost::mpl::at_c<Ts, n>::type;
            return hana::type_c<T>;
        }
    };

    template <>
    struct drop_front_impl<ext::boost::mpl::vector_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs const&, std::index_sequence<i...>) {
            return boost::mpl::vector<
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
    struct is_empty_impl<ext::boost::mpl::vector_tag> {
        template <typename xs>
        static constexpr auto apply(xs)
        { return typename ::boost::mpl::empty<xs>::type{}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // Conversion from a Foldable
    //////////////////////////////////////////////////////////////////////////
    template <typename F>
    struct to_impl<ext::boost::mpl::vector_tag, F, when<hana::Foldable<F>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs const& xs) {
            auto vector_type = hana::unpack(xs, hana::template_<boost::mpl::vector>);
            return typename decltype(vector_type)::type{};
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_BOOST_MPL_VECTOR_HPP

/* vector.hpp
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
*/