// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


#include <boost/range/adaptor/adjacent_filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry, bool DefaultPass>
#if BOOST_VERSION > 104500
struct tag<boost::adjacent_filtered_range<Filter, Geometry, DefaultPass> >
#else
struct tag<boost::range_detail::adjacent_filter_range<Filter, Geometry, DefaultPass> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


/* adjacent_filtered.hpp
ye29JP/WDDvwV9K7vgDnzt4kMDOTfzB8AWGMOT2YpsUte7R7VzP+bHREG6/Cg7a7Msn+FCoAJl/3cMe2tHa/tM/+OVPdK/ti9P4dNIgJaU0hG2DKsrppFSmuY7kGTZP8TOg2Zz45O1UVNCdn+aeWn4OYaMgeDPpEfKI75Po3kuN5eRxuenSu0ANp/Xdw8S1ycfGPS9S6yUtVaS0JCTG395bIBeKnffmbe+oVdEJye93kVX/sjxQUT/VjXPfcnMBou6U/WIFOubNoHIMVq6n0Z0FzYkKvf3iH1Sog+tkxHldF/huvRtActYbcO73uFRqc9EhXGw/KWM/ChUY5onYa8qHzn4863B8iJjyOfnldrap5ULykDcAt9/PmruIM2AQNUn6DLSG/3DtaO1IYMCGvIjn+WFpEy1wtSEwor3+EqczRXB2FdlX9LfC2Qs6JWhp9ciI8zjHGwFMaayMo2lrBVJFmcsBbwLKHoSdsC2jhpLthLbdFHj5yJ4747sM39cXE+FWp4gnPrFURVJtKOPVkTwggEJIX6M21xewa3t6MbnwlVKWNuYKlByAPZdkHHShgY3MRtVcO9o9astbBv5DUwRfHdUvD0yvn8q5CvRQObvak0hBqDtrxKK8UigSvhNu3rwZM6VPSuEU37s3ams/WeUIyFsx/WjbfdwceSTmJMUm37zqcVFiL3R6TcXOka+NYjGqSx7Ieev34pU08
*/