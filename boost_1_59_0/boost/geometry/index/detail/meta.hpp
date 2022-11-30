// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_META_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

#include <type_traits>

//#include <boost/range/value_type.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

//template <typename T, typename V, bool IsRange = range::detail::is_range<T>::value>
//struct is_range_of_convertible_values_impl
//    : std::is_convertible<typename ::boost::range_value<T>::type, V>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values_impl<T, V, false>
//    : std::integral_constant<bool, false>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values
//    : is_range_of_convertible_values_impl<T, V>
//{};

// Implemented this way in order to prevent instantiation of all type traits at
// once because some of them are causing problems with gcc 4.6 namely
// is_convertible<bg::model::segment<>, std::pair<bg::model::segment<>, T> >
// because segment<> is derived from pair<> and pair<> has copy ctor taking
// other pair<> of any types the compiler tries to instantiate ctor of
// pair<segment, T> taking pair<point, point> which results in instantiation of
// segment's ctor taking a point which results in compilation error.
// This is probably compiler's bug.
template <typename T, typename Value, typename Indexable, typename ResultType, int Ver>
struct convertible_type_impl
{
    typedef ResultType type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 0>
{
    typedef std::conditional_t
        <
            std::is_convertible<T, Indexable>::value,
            Indexable,
            void
        > result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 1
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 1>
{
    typedef std::conditional_t
        <
            std::is_convertible<T, Value>::value,
            Value,
            void
        > type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type
{
    typedef std::conditional_t
        <
            std::is_same<T, Value>::value,
            Value,
            std::conditional_t
                <
                    std::is_same<T, Indexable>::value,
                    Indexable,
                    void
                >
        > result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 0
        >::type type;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

/* meta.hpp
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
*/