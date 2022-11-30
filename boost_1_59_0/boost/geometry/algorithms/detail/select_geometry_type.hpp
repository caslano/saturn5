// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SELECT_GEOMETRY_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SELECT_GEOMETRY_TYPE_HPP

#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct first_geometry_type
{
    using type = Geometry;
};

template <typename Geometry>
struct first_geometry_type<Geometry, geometry_collection_tag>
{
    template <typename T>
    using pred = util::bool_constant
        <
            ! util::is_dynamic_geometry<T>::value
            && ! util::is_geometry_collection<T>::value
        >;

    using type = typename util::sequence_find_if
        <
            typename traits::geometry_types<Geometry>::type,
            pred
        >::type;
};

template <typename Geometry>
struct first_geometry_type<Geometry, dynamic_geometry_tag>
    : first_geometry_type<Geometry, geometry_collection_tag>
{};


template
<
    typename Geometry,
    bool IsDynamicOrCollection = util::is_dynamic_geometry<Geometry>::value
                              || util::is_geometry_collection<Geometry>::value
>
struct geometry_types
{
    using type = util::type_sequence<std::remove_const_t<Geometry>>;
};

template <typename Geometry>
struct geometry_types<Geometry, true>
{
    using type = typename traits::geometry_types<std::remove_const_t<Geometry>>::type;
};


template
<
    typename Geometry,
    template <typename, typename> class LessPred,
    bool IsDynamicOrCollection = util::is_dynamic_geometry<Geometry>::value
                              || util::is_geometry_collection<Geometry>::value
>
struct select_geometry_type
{
    using type = Geometry;
};

template
<
    typename Geometry,
    template <typename, typename> class LessPred
>
struct select_geometry_type<Geometry, LessPred, true>
    : util::sequence_min_element
        <
            typename traits::geometry_types<std::remove_const_t<Geometry>>::type,
            LessPred
        >
{};


template
<
    typename Geometry1, typename Geometry2,
    template <typename, typename> class LessPred,
    bool IsDynamicOrCollection = util::is_dynamic_geometry<Geometry1>::value
                              || util::is_dynamic_geometry<Geometry2>::value
                              || util::is_geometry_collection<Geometry1>::value
                              || util::is_geometry_collection<Geometry2>::value
>
struct select_geometry_types
{
    using type = util::type_sequence
        <
            std::remove_const_t<Geometry1>,
            std::remove_const_t<Geometry2>
        >;
};

template
<
    typename Geometry1, typename Geometry2,
    template <typename, typename> class LessPred
>
struct select_geometry_types<Geometry1, Geometry2, LessPred, true>
    : util::sequence_min_element
        <
            typename util::sequence_combine
                <
                    typename geometry_types<Geometry1>::type,
                    typename geometry_types<Geometry2>::type
                >::type,
            LessPred
        >
{};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SELECT_GEOMETRY_TYPE_HPP

/* select_geometry_type.hpp
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
*/