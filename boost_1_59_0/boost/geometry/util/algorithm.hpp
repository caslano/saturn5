// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_ALGORITHM_HPP
#define BOOST_GEOMETRY_UTIL_ALGORITHM_HPP


#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Other implementations can be found in the history of this file.
// The discussion and benchmarks can be found here:
// https://github.com/boostorg/geometry/pull/827

// O(logN) version 2

template <std::size_t N>
struct for_each_index_impl2
{
    static const std::size_t N1 = N / 2;
    static const std::size_t N2 = N - N1;

    template <std::size_t Offset, typename UnaryFunction>
    constexpr static inline void apply(UnaryFunction& function)
    {
        for_each_index_impl2<N1>::template apply<Offset>(function);
        for_each_index_impl2<N2>::template apply<Offset + N1>(function);
    }
};

template <>
struct for_each_index_impl2<3>
{
    template <std::size_t Offset, typename UnaryFunction>
    constexpr static inline void apply(UnaryFunction& function)
    {
        function(util::index_constant<Offset>());
        function(util::index_constant<Offset + 1>());
        function(util::index_constant<Offset + 2>());
    }
};

template <>
struct for_each_index_impl2<2>
{
    template <std::size_t Offset, typename UnaryFunction>
    constexpr static inline void apply(UnaryFunction& function)
    {
        function(util::index_constant<Offset>());
        function(util::index_constant<Offset + 1>());
    }
};

template <>
struct for_each_index_impl2<1>
{
    template <std::size_t Offset, typename UnaryFunction>
    constexpr static inline void apply(UnaryFunction& function)
    {
        function(util::index_constant<Offset>());
    }
};

template <>
struct for_each_index_impl2<0>
{
    template <std::size_t Offset, typename UnaryFunction>
    constexpr static inline void apply(UnaryFunction& )
    {}
};

// Interface

template <std::size_t N, typename UnaryFunction>
constexpr inline UnaryFunction for_each_index(UnaryFunction function)
{
    for_each_index_impl2
        <
            N
        >::template apply<0>(function);
    return function;
}

template <typename Geometry, typename UnaryFunction>
constexpr inline UnaryFunction for_each_dimension(UnaryFunction function)
{
    for_each_index_impl2
        <
            geometry::dimension<Geometry>::value
        >::template apply<0>(function);
    return function;
}

// ----------------------------------------------------------------------------

// O(logN) version 2

template <std::size_t N>
struct all_indexes_of_impl2
{
    static const std::size_t N1 = N / 2;
    static const std::size_t N2 = N - N1;

    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return all_indexes_of_impl2<N1>::template apply<Offset>(predicate)
            && all_indexes_of_impl2<N2>::template apply<Offset + N1>(predicate);
    }
};

template <>
struct all_indexes_of_impl2<3>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>())
            && predicate(util::index_constant<Offset + 1>())
            && predicate(util::index_constant<Offset + 2>());
    }
};

template <>
struct all_indexes_of_impl2<2>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>())
            && predicate(util::index_constant<Offset + 1>());
    }
};

template <>
struct all_indexes_of_impl2<1>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>());
    }
};

template <>
struct all_indexes_of_impl2<0>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& )
    {
        return true;
    }
};

// Interface

template <std::size_t N, typename UnaryPredicate>
constexpr inline bool all_indexes_of(UnaryPredicate predicate)
{
    return all_indexes_of_impl2<N>::template apply<0>(predicate);
}

template <typename Geometry, typename UnaryPredicate>
constexpr inline bool all_dimensions_of(UnaryPredicate predicate)
{
    return all_indexes_of_impl2
        <
            geometry::dimension<Geometry>::value
        >::template apply<0>(predicate);
}

// ----------------------------------------------------------------------------

// O(logN) version 2

template <std::size_t N>
struct any_index_of_impl2
{
    static const std::size_t N1 = N / 2;
    static const std::size_t N2 = N - N1;

    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return any_index_of_impl2<N1>::template apply<Offset>(predicate)
            || any_index_of_impl2<N2>::template apply<Offset + N1>(predicate);
    }
};

template <>
struct any_index_of_impl2<3>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>())
            || predicate(util::index_constant<Offset + 1>())
            || predicate(util::index_constant<Offset + 2>());
    }
};

template <>
struct any_index_of_impl2<2>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>())
            || predicate(util::index_constant<Offset + 1>());
    }
};

template <>
struct any_index_of_impl2<1>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& predicate)
    {
        return predicate(util::index_constant<Offset>());
    }
};

template <>
struct any_index_of_impl2<0>
{
    template <std::size_t Offset, typename UnaryPredicate>
    constexpr static inline bool apply(UnaryPredicate& )
    {
        return false;
    }
};

// Interface

template <std::size_t N, typename UnaryPredicate>
constexpr inline bool any_index_of(UnaryPredicate predicate)
{
    return any_index_of_impl2<N>::template apply<0>(predicate);
}

template <typename Geometry, typename UnaryPredicate>
constexpr inline bool any_dimension_of(UnaryPredicate predicate)
{
    return any_index_of_impl2
        <
            geometry::dimension<Geometry>::value
        >::template apply<0>(predicate);
}

template <std::size_t N, typename UnaryPredicate>
constexpr inline bool none_index_of(UnaryPredicate predicate)
{
    return ! any_index_of_impl2<N>::template apply<0>(predicate);
}

template <typename Geometry, typename UnaryPredicate>
constexpr inline bool none_dimension_of(UnaryPredicate predicate)
{
    return ! any_index_of_impl2
        <
            geometry::dimension<Geometry>::value
        >::template apply<0>(predicate);
}

// ----------------------------------------------------------------------------


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_ALGORITHM_HPP

/* algorithm.hpp
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
*/