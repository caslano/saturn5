// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP
#define BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

#include <boost/geometry/core/closure.hpp>


namespace boost { namespace geometry
{


template<closure_selector Closure>
struct closure_as_bool
{};


template<>
struct closure_as_bool<closed>
{
    static const bool value = true;
};


template<>
struct closure_as_bool<open>
{
    static const bool value = false;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

/* closure_as_bool.hpp
azwpG56kgOcXkfiZTY3RubvR5+glyucGoAXJvyjIM3ESpm7WMnvqhb0Bx4hWBb86Eh1OdPAuQj4Ybdi4kU7ArIJOQ9eWXqfM2h7tKyN+ZinL1e8n7q4Tyej/SDnNQ+V72UNDed/oW1XRkby7avzHKSUhoysp6VLAZNj8KTu/bD2yc64FhWr/kjm11n2BvU/xzULxR/oxQmTRrOXCkJbo45P3/fvygVOCjnQM7MAno8E6y4t1ZxXDKYmaFS2NbBjmbWNhLgb5qZd4VxJS9+RoQn90VE2ZnoQgBvV+s1QFc2IdnlGJ9jkuXYezAN3UnygHqexZezBbL+SIZ8ccCTbyy0FkEp6jdYxO38oBb5hLknMvXKyXRuGfVU01jHnKk+IspVKIP0hN1TmDS35YmLEv8Itd+BAbAeeyUJHHXIEo2xdALTOgGXcTNP+6wrcY8XEcb8P4lXWtmXeoWXVUiS6Lok+31NN52kdWFt5+UD154WPPfF5hoqcxsD9EyQZ5MrDGGaWg6B5/h7nohThLdpGwqqxakSmhvozw90Geeb2KPD4mctt3ez9OFSJeZA==
*/