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
7vauP5oU73/limvnBY8v/YvOJ4btJDaiiUlRGu/vU0sHplFDsg2EOy3qF6Br/cUfjtoZMJdvx+8xkHWzkXV6KKvSrCWaMwzNWkMzwBm/WcDfhP32Awcm16UoYR86x9T7sH3lV4j/98Wabt5HqSe5/qC2hPKh/sB9YLdgHulZ8S0u+C3QOcLQpzmiQfs19ekB++LwoFHHT7KO9iiN77ebSZak83jHl8KGxBijGKN6VmMxzX1JtJYanNty8PuEwSneN9muPVH1o765xHYSfPhkQ/2cpHUBPnBkrgEefLKltn8PCSYWxtOH7GvSOA9j00/l79geFb4oA/+rHQ/mnNVe+fC/QqYpo9TG8GmnI5t249OmC/Lj6U2UfpLSjq9N72H42/RurEudb+1cOyzoV/sD5wtH2fi/yXbPmlLrvwvtULtOn1Ya9/8xfB2Vl/z4uUIqz/D1pfFvjicNiX9zvNKlcQ4V33V1nns4P76mfgH1d/lslz9KuBuA6/IZt6ggjnsOcF0+4z5AdM8Hrstn3GFE90vAdfl2X7Ehgc9m4nMRyrp8W/ayBL5bqeylKLtVcXU9wF5L0wq3vuIAfrK2wvi8dLnOJ+GZGbt/CHAm/UrYkw/TvZ9vl8bwBQ4fJPAfJfzvEf6jwP8+8F1bWfyrCL8I8lwN/AeI/o8I/wHQvwb4w4j+dYQ/DPR/DPwNhP8Twt8A/OuBv5nkuTGOL3D4FoF/GeH/lPAvA/4twN9K+JsIfyvwf27GrwPyfuwXERzjkeG/NPBHE+C3G3hRAv07DPyBhPK/MfBhCeXvNvANCfB7DXxzAv37DPyyBPjvDXxrAnwzlT+K4A/omHHw5Dl6K9HgOw8PE/xtgj+K8f421p9240uRvMQ7Mo+r/aJldA64zJTh926eNLI8MRbrvZHlT2YtEyH8vs1+N5K/w7N11O9cvqXzXKniI612oT9XO6woO1ddRvb3i8b+vrgA+xzo5mXTHlcVhzSkHHjBJ0P6Zj/AX0n2jM4JIfxvpcoT862lB5lMXbepzmydoDOj+9e1zZSuH+sX0/nSN0tzt99bVLf5o8g/o/BQTq77OzTe+Hvgu1oXtWE83kaqy/vaDg6e7I8ZUhbuhQ4y7wsMLYvvhYaVxXWyaxnkAyyj8y9sLdB8Lz9LcwTR3J1o7hHRBCxj5lzvc5G8qOxkrJkXY63d29JC2uq3kPpCQRn0ovrP4hRiDRldZtLwS9k2GbNv3LewT5kd237PKjiMNyzYl/DsuX3bduNMHYKEPnAAwfkc3IEC9+cpsUbZ9uGyG0g/EyMZAWcZL8N37UOIjuTH/SnQoZRHWuEYw5YPYvSas0sF0MURKPd+PvmxTbk96E5TCcn2PZKtlODsCyon+I0ErzTwIw7cvny1gU9I0HGNgbt6se6mlfF8ZeZR008+XBb3Q3zY+B0kD/5AKos5/KOGxzvAcXoCnp7RrtXxQnIYfc8knHcMHfnb49SVqWzoU8rX8IRPRHG5D9q5AT6RMvgRgIt7IUI3Sda84LiycL/Uj7tzsk3aFt3Fml/mcFbiLTAH69O4VAscDP8ODnp7OteWVZRWSXg6/0ZUZ/g9lnOnT/e8asHrV+Ytt6HmnTMni50nPobx21gWszH1jbSZ9G5DM/AXAX8S6tPkZfave2rsreMlb3iQ6urIBBpb/AStW+KbYov4u+vxoN/gy/X0tkpcI9AXvbl6dvd0t6X0HbUtgYuvFTi4r+/T7n1/fFdcLDReDsI3JI5BLLolRp5/qa6jV6K8SJyp3+dK6H30j5fxW3nynpDkWTi/gX6i9mfAE96WPqksR1yknegbTt5lZfyO1PbytJfF3wQcNQzx65EejvOcd0/Kzvc=
*/