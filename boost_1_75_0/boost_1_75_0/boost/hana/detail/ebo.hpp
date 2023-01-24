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
FJirMFzFq4TqJxQ4Q+Gyiv8kVCmhQE5hrYothGoiFHiONcyL3FZ6LJ2qIDTgExZwjNt6Jw3YoAa0soAfclvpMWuqdNCA3yusw229GgOK2in0WYVnuK1JFLqPQgWFWbitX9MrTjsBWvEIcgi39RSFvISQdcgd3NY/Ucg2hDiRM7it71BIHUJsCldwW3+FQKpLIHy6yhETQv5BBFFm4LbWslvLyAYzLmKD60lRL238Rmz7qslKg8/Bs1f2mNwJXU+L18TUcsmhOtlr7Hf3gECdoAjUmyfQ6eJ6XDmwMwFJ3D0oRw9Jh1fTKSMoJDhr3O8trX0UZ43Lbfth1rjfu9x26okZ7+Mc0Hbq8Ws1k3k6YewaMmGcAhPGibZTdLI4GiYwk7P2Q3RxpUk7WzwJUzmZ7yxxSe8Z2GwxDsGuDrPFsnXaY3N4edXst1uKrX2AN502Nos16B5Z5AcaUhfUl96ts3jNC+rvhif/AChEP12Cc2diH8irT8U7sFEjfxzPYvyyNDa/tND5Zbr0MEStNzYYFzy5nuXy5AbMZQ7EXgVBjnqjMJjA01MO90Nqj7FUOdOHztTfhG4OVe7B91cy8IY7niEL+k1+PCca/vO3qQC3O7XcVr8JCwcuqK/F0iugtJFLaHNDJYSAoVxk9Ujk27Eeky6ux6nF2KxGbrex3PZkvZLbk9swt2xIEYBgXCkXoTop/IdYneMlw6tj0VTH
*/