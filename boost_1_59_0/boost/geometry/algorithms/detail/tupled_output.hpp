// Boost.Geometry

// Copyright (c) 2019-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP

#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/core/config.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/tuples.hpp>
#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename T, bool IsRange = range::detail::is_range<T>::value>
struct is_tupled_output_element_base
    : util::bool_constant<false>
{};

template <typename T>
struct is_tupled_output_element_base<T, true>
    : util::bool_constant
        <
            (util::is_multi<T>::value
                ||
                (util::is_not_geometry<T>::value
                    &&
                    util::is_multi_element
                        <
                            typename boost::range_value<T>::type
                        >::value))
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
// a range of points, linestrings or polygons
template <typename Output>
struct is_tupled_output_check
    : util::bool_constant
        <
            (util::is_not_geometry<Output>::value
          && geometry::tuples::exists_if<Output, is_tupled_output_element>::value)
        >
{};


// true if T is not a geometry (so e.g. tuple was not adapted to any
// concept) and at least one of the tuple elements is a point, linesting
// or polygon
template <typename T>
struct is_tupled_single_output_check
    : util::bool_constant
        <
            (util::is_not_geometry<T>::value
          && geometry::tuples::exists_if<T, util::is_multi_element>::value)
        >
{};



// true if Output is boost::tuple, boost::tuples::cons, std::pair or std::tuple
// and is_tupled_output_check defiend above passes
template <typename Output, bool IsTupled = tuples::is_tuple<Output>::value>
struct is_tupled_output
    : util::bool_constant<false>
{};

template <typename Output>
struct is_tupled_output<Output, true>
    : is_tupled_output_check<Output>
{};


// true if T is boost::tuple, boost::tuples::cons, std::pair or std::tuple
// and is_tupled_single_output_check defiend above passes
template <typename T, bool IsTupled = tuples::is_tuple<T>::value>
struct is_tupled_single_output
    : util::bool_constant<false>
{};

template <typename T>
struct is_tupled_single_output<T, true>
    : is_tupled_single_output_check<T>
{};


template <typename Tag>
struct tupled_output_find_index_pred
{
    template <typename T>
    struct pred
        : std::is_same<typename geometry::tag<T>::type, Tag>
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
    : util::bool_constant<false>
{};

template <typename Output, typename Tag>
struct tupled_output_has<Output, Tag, true>
    : util::bool_constant
        <
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

template <typename Tuple>
struct tupled_range_values;

template <typename ...Ts>
struct tupled_range_values<std::tuple<Ts...> >
{
    typedef std::tuple<typename boost::range_value<Ts>::type...> type;
};

template <typename F, typename S>
struct tupled_range_values<std::pair<F, S> >
{
    typedef std::pair
        <
            typename boost::range_value<F>::type,
            typename boost::range_value<S>::type
        > type;
};

template
<
    typename Tuple,
    size_t I = 0,
    size_t N = boost::tuples::length<Tuple>::value
>
struct tupled_range_values_bt
{
    typedef boost::tuples::cons
        <
            typename boost::range_value
                <
                    typename boost::tuples::element<I, Tuple>::type
                >::type,
            typename tupled_range_values_bt<Tuple, I+1, N>::type
        > type;
};

template <typename Tuple, size_t N>
struct tupled_range_values_bt<Tuple, N, N>
{
    typedef boost::tuples::null_type type;
};

template <typename ...Ts>
struct tupled_range_values<boost::tuples::tuple<Ts...>>
    : tupled_range_values_bt<boost::tuples::tuple<Ts...>>
{};

template <typename HT, typename TT>
struct tupled_range_values<boost::tuples::cons<HT, TT>>
    : tupled_range_values_bt<boost::tuples::cons<HT, TT>>
{};


// util defining a type and creating a tuple holding back-insert-iterators to
// ranges being elements of Output pair/tuple

template <typename Tuple>
struct tupled_back_inserters;

template <typename Is, typename Tuple>
struct tupled_back_inserters_st;

template <std::size_t ...Is, typename ...Ts>
struct tupled_back_inserters_st<std::index_sequence<Is...>, std::tuple<Ts...> >
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
            std::make_index_sequence<sizeof...(Ts)>,
            std::tuple<Ts...>
        >
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

template <typename Tuple,
          size_t I = 0,
          size_t N = boost::tuples::length<Tuple>::value>
struct tupled_back_inserters_bt
{
    typedef boost::tuples::cons
        <
            geometry::range::back_insert_iterator
                <
                    typename boost::tuples::element<I, Tuple>::type
                >,
            typename tupled_back_inserters_bt<Tuple, I+1, N>::type
        > type;

    static type apply(Tuple & tup)
    {
        return type(geometry::range::back_inserter(boost::get<I>(tup)),
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

template <typename ...Ts>
struct tupled_back_inserters<boost::tuples::tuple<Ts...>>
    : tupled_back_inserters_bt<boost::tuples::tuple<Ts...>>
{};

template <typename HT, typename TT>
struct tupled_back_inserters<boost::tuples::cons<HT, TT>>
    : tupled_back_inserters_bt<boost::tuples::cons<HT, TT>>
{};


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
        : std::is_same<typename geometry::tag<T>::type, Tag>
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


template <typename Geometry>
struct output_geometry_concept_check
{
    static void apply()
    {
        concepts::check<Geometry>();
    }
};

template <typename First, typename Second>
struct output_geometry_concept_check<std::pair<First, Second> >
{
    static void apply()
    {
        concepts::check<First>();
        concepts::check<Second>();
    }
};

template <typename Tuple,
          size_t I = 0,
          size_t N = geometry::tuples::size<Tuple>::value>
struct output_geometry_concept_check_t
{
    static void apply()
    {
        concepts::check<typename geometry::tuples::element<I, Tuple>::type>();
        output_geometry_concept_check_t<Tuple, I + 1, N>::apply();
    }
};

template <typename Tuple, size_t N>
struct output_geometry_concept_check_t<Tuple, N, N>
{
    static void apply()
    {}
};

template <typename ...Ts>
struct output_geometry_concept_check<std::tuple<Ts...> >
    : output_geometry_concept_check_t<std::tuple<Ts...> >
{};

template <typename ...Ts>
struct output_geometry_concept_check<boost::tuple<Ts...> >
    : output_geometry_concept_check_t<boost::tuple<Ts...> >
{};

template <typename HT, typename TT>
struct output_geometry_concept_check<boost::tuples::cons<HT, TT> >
    : output_geometry_concept_check_t<boost::tuples::cons<HT, TT> >
{};


struct tupled_output_tag {};


template <typename GeometryOut>
struct setop_insert_output_tag
    : std::conditional
        <
            geometry::detail::is_tupled_single_output<GeometryOut>::value,
            tupled_output_tag,
            typename geometry::tag<GeometryOut>::type
        >
{};


template <typename Geometry1, typename Geometry2, typename TupledOut, bool IsFound, typename Tag>
struct expect_output_assert_base;

template <typename Geometry1, typename Geometry2, typename TupledOut, bool IsFound>
struct expect_output_assert_base<Geometry1, Geometry2, TupledOut, IsFound, pointlike_tag>
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        IsFound,
        "PointLike Geometry expected in tupled output.",
        Geometry1, Geometry2, TupledOut);
};

template <typename Geometry1, typename Geometry2, typename TupledOut, bool IsFound>
struct expect_output_assert_base<Geometry1, Geometry2, TupledOut, IsFound, linear_tag>
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        IsFound,
        "Linear Geometry expected in tupled output.",
        Geometry1, Geometry2, TupledOut);
};

template <typename Geometry1, typename Geometry2, typename TupledOut, bool IsFound>
struct expect_output_assert_base<Geometry1, Geometry2, TupledOut, IsFound, areal_tag>
{
    BOOST_GEOMETRY_STATIC_ASSERT(
        IsFound,
        "Areal Geometry expected in tupled output.",
        Geometry1, Geometry2, TupledOut);
};


template <typename Geometry1, typename Geometry2, typename TupledOut, typename Tag>
struct expect_output_assert
    : expect_output_assert_base
        <
            Geometry1, Geometry2, TupledOut,
            geometry::tuples::exists_if
                <
                    TupledOut,
                    is_tag_same_as_pred<Tag>::template pred
                >::value,
            typename geometry::tag_cast
                <
                    Tag, pointlike_tag, linear_tag, areal_tag
                >::type
        >
{};

template <typename Geometry1, typename Geometry2, typename TupledOut>
struct expect_output_assert<Geometry1, Geometry2, TupledOut, void>
{};

template
<
    typename Geometry1, typename Geometry2, typename TupledOut,
    typename ...Tags
>
struct expect_output
    : expect_output_assert<Geometry1, Geometry2, TupledOut, Tags>...
{};


template <typename CastedTag>
struct single_tag_from_base_tag;

template <>
struct single_tag_from_base_tag<pointlike_tag>
{
    typedef point_tag type;
};

template <>
struct single_tag_from_base_tag<linear_tag>
{
    typedef linestring_tag type;
};

template <>
struct single_tag_from_base_tag<areal_tag>
{
    typedef polygon_tag type;
};


template
<
    typename Geometry,
    typename SingleOut,
    bool IsMulti = util::is_multi<Geometry>::value
>
struct convert_to_output
{
    template <typename OutputIterator>
    static OutputIterator apply(Geometry const& geometry,
                                OutputIterator oit)
    {
        SingleOut single_out;
        geometry::convert(geometry, single_out);
        *oit++ = single_out;
        return oit;
    }
};

template
<
    typename Geometry,
    typename SingleOut
>
struct convert_to_output<Geometry, SingleOut, true>
{
    template <typename OutputIterator>
    static OutputIterator apply(Geometry const& geometry,
                                OutputIterator oit)
    {
        typedef typename boost::range_iterator<Geometry const>::type iterator;
        for (iterator it = boost::begin(geometry); it != boost::end(geometry); ++it)
        {
            SingleOut single_out;
            geometry::convert(*it, single_out);
            *oit++ = single_out;
        }
        return oit;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TUPLED_OUTPUT_HPP

/* tupled_output.hpp
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
*/