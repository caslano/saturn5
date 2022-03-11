// Boost.Geometry

// Copyright (c) 2019-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP

#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/tuples.hpp>

#include <boost/mpl/and.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_void.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// true for any geometry
template <typename T>
struct is_geometry
    : boost::integral_constant
        <
            bool,
            (! boost::is_void<typename geometry::tag<T>::type>::value)
        >
{};

// true for multi-point, multi-linestring or multi-polygon
template <typename Geometry>
struct is_multi_geometry
    : boost::is_base_of
        <
            geometry::multi_tag,
            typename geometry::tag<Geometry>::type
        >
{};

// true for point, linestring or polygon
template <typename T>
struct is_multi_geometry_value
    : boost::integral_constant
        <
            bool,
            ((boost::is_same<typename geometry::tag<T>::type, point_tag>::value)
            || (boost::is_same<typename geometry::tag<T>::type, linestring_tag>::value)
            || (boost::is_same<typename geometry::tag<T>::type, polygon_tag>::value))
        >
{};


template <typename T>
struct is_range_impl
{
    typedef boost::type_traits::yes_type yes_type;
    typedef boost::type_traits::no_type no_type;

    template <typename U>
    static yes_type test(typename boost::range_iterator<U>::type*);

    template <typename U>
    static no_type test(...);

    static const bool value = (sizeof(test<T>(0)) == sizeof(yes_type));
};

// true if T is range (boost::range_iterator<T>::type is defined)
template <typename T>
struct is_range
    : boost::integral_constant<bool, is_range_impl<T>::value>
{};


// geometry tag of Rng value_type
template <typename Rng>
struct range_value_tag
    : geometry::tag<typename boost::range_value<Rng>::type>
{};

// true if geometry tag of Rng is the same as Tag
template <typename Rng, typename Tag>
struct is_range_value_tag_same_as
    : boost::is_same
        <
            typename range_value_tag<Rng>::type,
            Tag
        >
{};


template <typename T, bool IsRange = is_range<T>::value>
struct is_tupled_output_element_base
    : boost::integral_constant<bool, false>
{};

template <typename T>
struct is_tupled_output_element_base<T, true>
    : boost::integral_constant
        <
            bool,
            (is_multi_geometry<T>::value
            ||
            ((! is_geometry<T>::value)
                &&
                ((is_range_value_tag_same_as<T, point_tag>::value)
                || (is_range_value_tag_same_as<T, linestring_tag>::value)
                || (is_range_value_tag_same_as<T, polygon_tag>::value))))
        >
{};

// true if T is a multi-geometry or is a range of points, linestrings or
// polygons
template <typename T>
struct is_tupled_output_element
    : is_tupled_output_element_base<T>
{};



// true if Output is not a geometry (so e.g. tuple was not adapted to any
// concept) and at least one of the tuple elements is a multi-geometry or
// a range of points linestrings or polygons
template <typename Output>
struct is_tupled_output_check
    : boost::mpl::and_
        <
            boost::is_same<typename geometry::tag<Output>::type, void>,
            //geometry::tuples::exists_if<Output, is_multi_geometry>
            geometry::tuples::exists_if<Output, is_tupled_output_element>
        >
{};


// true if T is a point, linestring or polygon
template <typename T>
struct is_tupled_range_values_element
    : boost::integral_constant
        <
            bool,
            ((boost::is_same<typename geometry::tag<T>::type, point_tag>::value)
                || (boost::is_same<typename geometry::tag<T>::type, linestring_tag>::value)
                || (boost::is_same<typename geometry::tag<T>::type, polygon_tag>::value))
        >
{};


// true if T is not a geometry (so e.g. tuple was not adapted to any
// concept) and at least one of the tuple elements is a point, linesting
// or polygon
template <typename T>
struct is_tupled_range_values_check
    : boost::mpl::and_
        <
            boost::is_same<typename geometry::tag<T>::type, void>,
            geometry::tuples::exists_if<T, is_tupled_range_values_element>
        >
{};


// true if Output is boost::tuple, boost::tuples::cons, std::pair or std::tuple
template <typename T>
struct is_tupled
    : boost::integral_constant<bool, false>
{};

template
<
    class T0, class T1, class T2, class T3, class T4,
    class T5, class T6, class T7, class T8, class T9
>
struct is_tupled<boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
    : boost::integral_constant<bool, true>
{};

template <typename HT, typename TT>
struct is_tupled<boost::tuples::cons<HT, TT> >
    : boost::integral_constant<bool, true>
{};

template <typename F, typename S>
struct is_tupled<std::pair<F, S> >
    : boost::integral_constant<bool, true>
{};

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

template <typename ...Ts>
struct is_tupled<std::tuple<Ts...> >
    : boost::integral_constant<bool, true>
{};

#endif // BOOST_GEOMETRY_CXX11_TUPLE



// true if Output is boost::tuple, boost::tuples::cons, std::pair or std::tuple
// and is_tupled_output_check defiend above passes
template <typename Output, bool IsTupled = is_tupled<Output>::value>
struct is_tupled_output
    : boost::integral_constant<bool, false>
{};

template <typename Output>
struct is_tupled_output<Output, true>
    : is_tupled_output_check<Output>
{};


// true if T is boost::tuple, boost::tuples::cons, std::pair or std::tuple
// and is_tupled_range_values_check defiend above passes
template <typename T, bool IsTupled = is_tupled<T>::value>
struct is_tupled_range_values
    : boost::integral_constant<bool, false>
{};

template <typename T>
struct is_tupled_range_values<T, true>
    : is_tupled_range_values_check<T>
{};


template <typename Tag>
struct tupled_output_find_index_pred
{
    template <typename T>
    struct pred
        : boost::is_same<typename geometry::tag<T>::type, Tag>
    {};
};

// Valid only if tupled_output_has<Output, Tag> is true
template <typename Output, typename Tag>
struct tupled_output_find_index
    : geometry::tuples::find_index_if
        <
            Output,
            tupled_output_find_index_pred<Tag>::template pred
        >
{};


template
<
    typename Output,
    typename Tag,
    bool IsTupledOutput = is_tupled_output<Output>::value
>
struct tupled_output_has
    : boost::integral_constant<bool, false>
{};

template <typename Output, typename Tag>
struct tupled_output_has<Output, Tag, true>
    : boost::integral_constant
        <
            bool,
            ((tupled_output_find_index<Output, Tag>::value)
                < (geometry::tuples::size<Output>::value))
        >
{};


// Valid only if tupled_output_has<Output, Tag> is true
template <typename Tag, typename Output>
inline typename geometry::tuples::element
    <
        tupled_output_find_index<Output, Tag>::value,
        Output
    >::type &
tupled_output_get(Output & output)
{
    return geometry::tuples::get<tupled_output_find_index<Output, Tag>::value>(output);
}


// defines a tuple-type holding value-types of ranges being elements of
// Output pair/tuple

template
<
    typename Tuple,
    size_t I = 0,
    size_t N = geometry::tuples::size<Tuple>::value
>
struct tupled_range_values_bt
{
    typedef boost::tuples::cons
        <
            typename boost::range_value
                <
                    typename geometry::tuples::element<I, Tuple>::type
                >::type,
            typename tupled_range_values_bt<Tuple, I+1, N>::type
        > type;
};

template <typename Tuple, size_t N>
struct tupled_range_values_bt<Tuple, N, N>
{
    typedef boost::tuples::null_type type;
};

template <typename Output>
struct tupled_range_values
    : tupled_range_values_bt<Output>
{};

template <typename F, typename S>
struct tupled_range_values<std::pair<F, S> >
{
    typedef std::pair
        <
            typename boost::range_value<F>::type,
            typename boost::range_value<S>::type
        > type;
};

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

template <typename ...Ts>
struct tupled_range_values<std::tuple<Ts...> >
{
    typedef std::tuple<typename boost::range_value<Ts>::type...> type;
};

#endif // BOOST_GEOMETRY_CXX11_TUPLE


// util defining a type and creating a tuple holding back-insert-iterators to
// ranges being elements of Output pair/tuple

template <typename Tuple,
          size_t I = 0,
          size_t N = geometry::tuples::size<Tuple>::value>
struct tupled_back_inserters_bt
{
    typedef boost::tuples::cons
        <
            geometry::range::back_insert_iterator
                <
                    typename geometry::tuples::element<I, Tuple>::type
                >,
            typename tupled_back_inserters_bt<Tuple, I+1, N>::type
        > type;

    static type apply(Tuple & tup)
    {
        return type(geometry::range::back_inserter(geometry::tuples::get<I>(tup)),
                    tupled_back_inserters_bt<Tuple, I+1, N>::apply(tup));
    }
};

template <typename Tuple, size_t N>
struct tupled_back_inserters_bt<Tuple, N, N>
{
    typedef boost::tuples::null_type type;

    static type apply(Tuple const&)
    {
        return type();
    }
};

template <typename Tuple>
struct tupled_back_inserters
    : tupled_back_inserters_bt<Tuple>
{};

template <typename F, typename S>
struct tupled_back_inserters<std::pair<F, S> >
{
    typedef std::pair
        <
            geometry::range::back_insert_iterator<F>,
            geometry::range::back_insert_iterator<S>
        > type;

    static type apply(std::pair<F, S> & p)
    {
        return type(geometry::range::back_inserter(p.first),
                    geometry::range::back_inserter(p.second));
    }
};

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

// NOTE: In C++14 std::integer_sequence and std::make_integer_sequence could be used

template <typename Is, typename Tuple>
struct tupled_back_inserters_st;

template <int ...Is, typename ...Ts>
struct tupled_back_inserters_st<geometry::tuples::int_sequence<Is...>, std::tuple<Ts...> >
{
    typedef std::tuple<geometry::range::back_insert_iterator<Ts>...> type;

    static type apply(std::tuple<Ts...> & tup)
    {
        return type(geometry::range::back_inserter(std::get<Is>(tup))...);
    }
};

template <typename ...Ts>
struct tupled_back_inserters<std::tuple<Ts...> >
    : tupled_back_inserters_st
        <
            typename geometry::tuples::make_int_sequence<sizeof...(Ts)>::type,
            std::tuple<Ts...>
        >
{};

#endif // BOOST_GEOMETRY_CXX11_TUPLE


template
<
    typename GeometryOut,
    bool IsTupled = is_tupled_output<GeometryOut>::value
>
struct output_geometry_value
    : boost::range_value<GeometryOut>
{};

template <typename GeometryOut>
struct output_geometry_value<GeometryOut, true>
    : tupled_range_values<GeometryOut>
{};


template
<
    typename GeometryOut,
    bool IsTupled = is_tupled_output<GeometryOut>::value
>
struct output_geometry_back_inserter_
{
    typedef geometry::range::back_insert_iterator<GeometryOut> type;

    static type apply(GeometryOut & out)
    {
        return geometry::range::back_inserter(out);
    }
};

template <typename GeometryOut>
struct output_geometry_back_inserter_<GeometryOut, true>
    : tupled_back_inserters<GeometryOut>
{};

template <typename GeometryOut>
inline typename output_geometry_back_inserter_<GeometryOut>::type
output_geometry_back_inserter(GeometryOut & out)
{
    return output_geometry_back_inserter_<GeometryOut>::apply(out);
}


// is_tag_same_as_pred
// Defines a predicate true if type's tag is the same as Tag
template <typename Tag>
struct is_tag_same_as_pred
{
    template <typename T>
    struct pred
        : boost::is_same<typename geometry::tag<T>::type, Tag>
    {};
};


// Allows to access a type/object in a pair/tuple corresponding to an index in
// GeometryOut pair/tuple of a geometry defined by Tag.
// If GeometryOut is a geometry then it's expected to be defined by DefaultTag.
template
<
    typename GeometryOut,
    typename Tag,
    typename DefaultTag,
    typename GeometryTag = typename geometry::tag<GeometryOut>::type
>
struct output_geometry_access
{};

// assume GeometryTag is void because not adapted tuple holding geometries was passed
template <typename TupledOut, typename Tag, typename DefaultTag>
struct output_geometry_access<TupledOut, Tag, DefaultTag, void>
{
    static const int index = geometry::tuples::find_index_if
        <
            TupledOut, is_tag_same_as_pred<Tag>::template pred
        >::value;

    typedef typename geometry::tuples::element<index, TupledOut>::type type;
    
    template <typename Tuple>
    static typename geometry::tuples::element<index, Tuple>::type&
        get(Tuple & tup)
    {
        return geometry::tuples::get<index>(tup);
    }
};

template <typename GeometryOut, typename Tag, typename DefaultTag>
struct output_geometry_access<GeometryOut, Tag, DefaultTag, DefaultTag>
{
    typedef GeometryOut type;

    template <typename T>
    static T& get(T & v)
    {
        return v;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP

/* tupled_output.hpp
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
*/