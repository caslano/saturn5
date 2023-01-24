// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP


#include <boost/version.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{

/*!
\brief Flag for iterating a reversible_view in forward or reverse direction
\ingroup views
*/
enum iterate_direction { iterate_forward, iterate_reverse };

/*!
\brief View on a range, reversing direction if necessary
\tparam Range original range
\tparam Direction direction of iteration
\ingroup views
*/
template <typename Range, iterate_direction Direction>
struct reversible_view {};



#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct reversible_view<Range, iterate_forward>
{
    typedef identity_view<Range> type;
};


template <typename Range>
struct reversible_view<Range, iterate_reverse>
{
#if BOOST_VERSION > 104500
    typedef boost::reversed_range<Range> type;
#else
    // For older versions of Boost
    typedef boost::range_detail::reverse_range<Range> type;
#endif
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP

/* reversible_view.hpp
jbMW4U5VvefIgaQGt4BrxT5L2If6bkotYYv14OeEA8G9RDx/kdt840X51YT6dZAFehDTV0QDwacm0mdvlKc0TFjsnkl9K+A6CHq+xbPFZPrshfxbzFW0KezYYOysavxesDSY6PmRTnxzraOXopp+F7WaWiPKQo+RM/4aPn4f3oUU5kkYwU2fFLjPRQSNMqrn2Zw0kUDf62b8xm7GKQzfDd7n71/gdROSh846k05IofoYIoCSWn37bXhCYowB0AHTCDMnHfAuzkFaxT3To1szXlWf3YVWgeiaLCVZTPRkZHp+Qw+wKHkH1tGyIF6BaQ/YDyv8haZlfc2zAnvWdCvb/CxlU+mCOj4Hi4G7vB1pKmEKcA0rq/EjgRjxClNlcI690QU266f2zQOMv9sZZnFedN7tJeoxV+347GO7ZR/Xs0noJLaTzZWnj4+J89RhDBlEd1T2do5OA6N3J4DjQM6NzuCr67DlurplPXtfo6Xv2R5IOH+wIpzEM8R7TWsP+y16CZlF/d5aW8gqUMs6X2dTdUOVkDY1rKr72jpEZ8PiHpWn01a3MbAj9vI3ZzIkmeyuKzQxjMIL5aE6h1Xr1+zBNIOO7Dq/sUSI7/ZoRTPVJjDFbjyO+AoVYz4FJXvDyjQzxytl9w30NWB6uHV37zwBdbuLURHt4z5MZ0/y6XTzssgJWGYh1oiAd035L2O+Ojs9iD4ZVV479E+KEGuv
*/