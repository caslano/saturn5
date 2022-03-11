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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_MPL_VECTOR_HPP

/* vector.hpp
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
*/