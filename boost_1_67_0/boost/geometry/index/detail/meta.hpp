// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_META_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
struct is_range
    : ::boost::mpl::aux::has_type< ::boost::range_iterator<T> >
{};

//template <typename T, typename V, bool IsRange>
//struct is_range_of_convertible_values_impl
//    : ::boost::is_convertible<typename ::boost::range_value<T>::type, V>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values_impl<T, V, false>
//    : ::boost::mpl::bool_<false>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values
//    : is_range_of_convertible_values_impl<T, V, is_range<T>::value>
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
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Indexable>::value,
            Indexable,
            void
        >::type result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 1
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 1>
{
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Value>::value,
            Value,
            void
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type
{
    typedef typename boost::mpl::if_c
        <
            boost::is_same<T, Value>::value,
            Value,
            typename boost::mpl::if_c
                <
                    boost::is_same<T, Indexable>::value,
                    Indexable,
                    void
                >::type
        >::type result_type;

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