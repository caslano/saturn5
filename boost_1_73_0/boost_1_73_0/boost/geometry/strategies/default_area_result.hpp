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
frIlwRpRTjV7UeDtVbPd7DbOQJN1YfPoWduLbrOwebvTd0Dedd41T4vbNPvvOt2fYEtA8J28Rqe7sC1GllZqKOUp/mpWt/kSdFTx+P3+mdP85bzVXdDmpPPmTQN0N66nd3GOduaC1vgAZ7PXc8DNaBZ1+WxEHJE65Y7g7hi+smyQ/ACGuKx1iXdbR1FyzX0eupOqbAk0pZ8jBe7Q53xL72TmhkCB+ADX1R1SkpqIfDI2MM5pUWpQ8zOJOPHbe9gKbSB8CpoCDcSCkYLmoud8FaHI95OfvoA5fOSTmn6M9sFPtD74IdqHj/jQR2gf+AQtvMhRVV8ChgcQftxXHiI9O7v7pJosFwNE6I4aPQwnt04P0T61O/wKCyAPVtAG/qROiOL1MjXqoTXqvg1k9zAZ1jhU/cSdDOYTVHJANRPLpEpindZR7uCGW8rSdNGTshUgJ5yMCEjQKdfmoQWKecTtA7apG2+qxHyBphEz2LdmQGEoywNHJG/iklcDt5uAS3rv53ZeZBOnVa6KEqA1vVDFmrIoLT4asfjtNTqk2fxpQvFzkpQM3jV+duOL3IH1lfwB3HQ+CO9msWqif0XTnh1Kn5txMOHGg6V2VmpUFuVMuzt2cjHH0WVbyv6/5rE6gMr6/czcJ612rYOXF9r/
*/