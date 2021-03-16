// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

#include <cmath>

namespace boost { namespace geometry { namespace projections
{

// Functions to resolve ambiguity when compiling with coordinates of different types
/*
template <typename T>
inline T atan2(T const& a, T const& b)
{
    using std::atan2;
    return atan2(a, b);
}
*/

template <typename T>
inline int int_floor(T const& f)
{
    using std::floor;
    return int(floor(f));
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

/* function_overloads.hpp
2t4Gxp7i0fgZDSdMM9H4GqMRp8SyvsoT/EKda/3MlOLrHUdNqaXS609NHbuioorp2wvy6DbJ2mi3LcZmcHf3qNtYR8PVQN/URDRLa3g8qRr24JfFu6iEOZazVb3mVhaVLykXj+pRA9qRW/kQzWeO5WwN52S6EmnHgLxa+MPU7GPlYpavtJzOmx3mdN7jaDmdK9mlCfTIFT2uR7sAxgLHaecHgU/hdx1+K/D7BmOHCty88zoL/tlUIU/nLzbz120=
*/