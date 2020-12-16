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
p4rpemrLiLV9PQE57xXTNdP2POxzhpieB23fwF4WaHPvYWb715iDxPor07afWLc23YNiXdr0vIvpemrLQdwksLJYP216psXazjTk9HzZ3rrE7Bnc/hTTddG2q5jep7a4mK61tjE6zq2Z2ABl2p4Q82vTdRELWNMmb7Pa78UvptfTtpOYX5ueMTHd19rOEtMzre0isKvF2r42FdP3ru0pfT53xiDnz2L63rV1ftV+vf5iumbawmJ6L9oOg5xJndOtC+QsivUo0/aOmO5dbU0xfX/aOhrK3H4R661M20Ziup7aBou1/fwnps+n7XTYyxWw3kTI+Szs5T0xfUfaGmIbKdPW9+v2nx8Giul9attWTNdT2x5ibT/HienzaUuL2TO4vSSme0LbZLMXv7+8hWNT1T6Pc+wVtZ5rM8DmgHm+ab9ebzEdp80v1qVM2yCxvtp0rSHnMIg7FeLGgl0n5lWm7S6wR6Euz8PZa7CXb8AWwHrLftt+n/3A1hPTObWFxJZVpm0nsU5l2vYGOxjsGG3u3YKNAbsUzn6jjnPvXUzfg7YS5KyI6f7U9gnkbIrpftHWa3b7O+ojpnNq6xHT96dtIzF9dm1bQ9xgMXs+927FfNr0/Ynp82m7SJt7R5DzQYh7EexDfQb3HsCW+q79PXSBDRDTe9G2hZjuJW27iumzaztMTN+ftuPFdE9oGw12hVh/ZdomwV6eB5uhz+7WWpvb83P+ew3m2kCwiNhAZdpGQFwW4h4V0zXTVhFrO+9i+m61zRFTZ1cmb3Pb17OfmF5PW1BM71PbTmJ6PW1DIS4B640R82rTvQQ582Kd2nSfQc6pkPN1ON/nUM/5YH2a7c8eANterJ8ybTEd5/anmJ4/beMg7nYxXTNtD4r10abnFuLeEdP11NYQ69am5/b79nfrFeutTFt/sT7adF+L6b1oG6zNrTXYiWL6jrRdBHvJ6Zxu74KVIedbEDdLm9u7cIauH9rbRmK657XtCnaYmL53bWfBeuPFdO9qu1ebWzMxe3a3P8V0L2n7HOJ+1nFu7/6o5sGtp5i+P20DIW4LsWWVaQuL6bNrGyqm70HbCIgbK6bPri2nze1dMV0XbU/AGZ7XcW5fi7Xta21uX8PZ+8xrb+uB7QR2MNipYJeC3a7NraeYvj9tVW1uzcS82nRfgy31k3zvUJvuXTF9f9oGieme17armJ53bXGd0+1dMa8ybWMgbhzETYC9PKrNrbVY21rDXubBXnr93D5nPzGdU1tATM+Dtm3BomDDxbqVaUuL6bvVdrVYpzJtt8AZJom1fe0GNh328gnEzQH7A6z3L/A9KzEdpy0opu9W265gwyDniWCjYZ9XiOk70najmO4JbZMh7gk4Q1XM3rt7R5DzG7CfYb3OVvu6dIvp82kLirX9GkhMr6ctJuZTpi0p1k+ZtkvFBmjT8wB7eQrO8BbYLLFua9rk7df21l9M11PbRmJ6n9rCYPuJ6XpqS4CNgZxZMV1PbQ+K9SjT9p6Y7k9tM8F+APPMb2+9tbn9CbaemL4HbVuL6fvTNlSsvzJtI8V0zbRdB3uZKKbvQdujYnoetL2u9+nOO9hSv7U/e1+wgWJd2nTNIG4PsIPF2r7mE+vUpnsX9nI1rHc7rPeEWNvnXb2e29eQcwFY14L2toGY3ou2ncR0v2gbIqb3qS0hpntC21iwvN6L259ibfsTbFbb9eTt9/bWX5vbg2Jte1DMr0zb8WJ6brWNE9Pzru1esX7KtD0Pe3lHrO3XzGL6brXNE9P11Nb5R/t9rgcWEdN3q+0wMX0+bSmIuwLWmySm709bRUyfT1tdx7kzBnFdf7aPC4q1/X6WmL4HbUPF9Nm1nSjm06Y=
*/