// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP



namespace boost { namespace geometry
{

// TODO: move to detail
enum overlay_type
{
    overlay_union,
    overlay_intersection,
    overlay_difference,
    overlay_buffer,
    overlay_dissolve
};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

enum operation_type
{
    operation_none,
    operation_union,
    operation_intersection,
    operation_blocked,
    operation_continue,
    operation_opposite
};


template <overlay_type OverlayType>
struct operation_from_overlay
{
};

template <>
struct operation_from_overlay<overlay_union>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_buffer>
{
    static const operation_type value = operation_union;
};

template <>
struct operation_from_overlay<overlay_intersection>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_difference>
{
    static const operation_type value = operation_intersection;
};

template <>
struct operation_from_overlay<overlay_dissolve>
{
    static const operation_type value = operation_union;
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_OVERLAY_TYPE_HPP

/* overlay_type.hpp
gm53jUEIKWqeUKguVXPH6t4f3CGAuVKUcnm/97+cOC7zNbUZlwNg/wnpD4tpWoTCsAKaidHAQUAf2MahzNmNURdeY2rB81786uoyYF3fLZ+T8a8BYcVTMBV1zUk5ge/Naj9SD8RE7sC1n/JKMGnx8XTgMptrlnHw5Jd64OKSNfh90X22Dk2ZcqrJ8eXvpZrtAJ0V2ARxV510Xfc+QQFpBi4K4hYZbcyYaopx3A8of9Pq+RgIDf0UE9Gn4iYOlc/T7R1FwOFo8MQuqAM5bJ8Cz22+Vi0D7D/ZRonKCJrWzoglU3xS345uu9Caa7o/VG6iWBaA/S4KzYRu2k4KI+ZYBo5bI1uoo2nthQdPfLfhGpXPwSfIRjfEhHdO/Twtrd5KEFDqr6nhRJJPsS80h+pBWVCwCaf9Wl3wYwFvGnwFnIh2rCIfIDYacJJJBeZJSwSlBiCLUPepWWpwCyvvYqpSDbW1qTExrLH8ot8h0HC0CEMUWuRezVjup8sDsP34ZcckfuanLqYAna8j2LdwvhljILBAwubuJvrwP/Uw0ufrX1H15USfhU14jjpdzA==
*/