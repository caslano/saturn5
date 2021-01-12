// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP


#include <boost/geometry/strategies/area_result.hpp>


namespace boost { namespace geometry
{

/*!
\brief Meta-function defining return type of area function, using the default strategy
\ingroup area
\note The strategy defines the return-type (so this situation is different
    from length, where distance is sqr/sqrt, but length always squared)
 */

template <typename Geometry>
struct default_area_result
    : area_result<Geometry>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_AREA_RESULT_HPP

/* default_area_result.hpp
BWSUs/HN7Y52XQcuXUTwJ8q5y2sEdPk2X4I8TUnv3GR5BtPBaEuGhM+wMdgTocyKBGo1LvPUldZRCadq/fwm8q1E+y76Y5TH1/N14Dvhs/DI7PTkwmQXYgKNzNx/8qj16zz4E3WYamXXJF2zs9MePDczLWWFPus8fbRIRBupf33Sd2QW9Iczs/JGfp/m24zxIzhVxTFcC/zWZPfY/SeHpw6hnkXxTfpZwC9KMLtTB69QjMWS
*/