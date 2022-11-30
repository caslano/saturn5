/*!
@file
Defines `boost::hana::detail::ebo`.

@copyright Louis Dionne 2013-2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_EBO_HPP
#define BOOST_HANA_DETAIL_EBO_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/intrinsics.hpp>


namespace _hana {
    //////////////////////////////////////////////////////////////////////////
    // ebo<K, V>
    //
    // Building block to implement the Empty Base Optimization (EBO). We
    // use a short name and define it in a short namespace to reduce
    // symbol lengths, since this type is used as a building block for
    // other widely used types such as `hana::pair`.
    //
    // When available, we use compiler intrinsics to reduce the number
    // of instantiations.
    //
    // `ebo` provides a limited set of constructors to reduce instantiations.
    // Also, the constructors are open-ended and they do not check for the
    // validity of their arguments, again to reduce compile-time costs.
    // Users of `ebo` should make sure that they only try to construct an
    // `ebo` from a compatible value.
    //
    // EBOs can be indexed using an arbitrary type. The recommended usage is
    // to define an integrap constant wrapper for the specific container using
    // EBO, and then index using that wrapper:
    //
    //      template <int> struct idx; // wrapper for tuple
    //      template <typename ...T>
    //      struct tuple : ebo<idx<0>, T0>, ebo<idx<1>, T1>, ... { };
    //
    // The reason for defining one wrapper per container is to avoid any issues
    // that can arise when using `ebo_get`, which casts to the base class. If
    // `tuple` and `pair` are inheritting from `ebo`s with the same indexing
    // scheme, trying to use `ebo_get` on a tuple of pairs will trigger an
    // ambiguous base class conversion, since both tuple and pair inherit
    // from `ebo`s with the same keys.
    //////////////////////////////////////////////////////////////////////////
    template <typename K, typename V, bool =
        BOOST_HANA_TT_IS_EMPTY(V) && !BOOST_HANA_TT_IS_FINAL(V)
    >
    struct ebo;

    // Specialize storage for empty types
    template <typename K, typename V>
    struct ebo<K, V, true> : V {
        constexpr ebo() { }

        template <typename T>
        explicit constexpr ebo(T&& t)
            : V(static_cast<T&&>(t))
        { }
    };

    // Specialize storage for non-empty types
    template <typename K, typename V>
    struct ebo<K, V, false> {
        constexpr ebo() : data_() { }

        template <typename T>
        explicit constexpr ebo(T&& t)
            : data_(static_cast<T&&>(t))
        { }

        V data_;
    };

    //////////////////////////////////////////////////////////////////////////
    // ebo_get
    //////////////////////////////////////////////////////////////////////////
    template <typename K, typename V>
    constexpr V const& ebo_get(ebo<K, V, true> const& x)
    { return x; }

    template <typename K, typename V>
    constexpr V& ebo_get(ebo<K, V, true>& x)
    { return x; }

    template <typename K, typename V>
    constexpr V&& ebo_get(ebo<K, V, true>&& x)
    { return static_cast<V&&>(x); }


    template <typename K, typename V>
    constexpr V const& ebo_get(ebo<K, V, false> const& x)
    { return x.data_; }

    template <typename K, typename V>
    constexpr V& ebo_get(ebo<K, V, false>& x)
    { return x.data_; }

    template <typename K, typename V>
    constexpr V&& ebo_get(ebo<K, V, false>&& x)
    { return static_cast<V&&>(x.data_); }
} // end namespace _hana

namespace boost { namespace hana {
    namespace detail {
        using ::_hana::ebo;
        using ::_hana::ebo_get;
    }
}} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_EBO_HPP

/* ebo.hpp
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
*/