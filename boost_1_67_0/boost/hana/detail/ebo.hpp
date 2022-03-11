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

BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        using ::_hana::ebo;
        using ::_hana::ebo_get;
    }
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_EBO_HPP

/* ebo.hpp
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
*/