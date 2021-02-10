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
CgZpLWNpFwK4sTHDZSlWcxnB1mel81ngjT1AzHhZ1fmRfUauZnZmBfXxozEvPt4TZkHAH+2ph37grGoumqcL6nkFAqIeMDASu/mxvAy3KhtrdeQP76AAHp0fHto3rhRLBEJ8wxLjM4bJ1B16tmOTMyeoM7gKlEqYiYg3QsOIdzt/v4vji9Udqxxmhbnzud6dPJF3/YRe8vs9i+g+RxxloPGJhDae9ha5/ne9nzFhLrj0xJFdXS1DtVUOp3iJkQj0xLa+Ekid89SxTUVuHQvSpDF8QUY6BvsNM+nh/S/KZvjY/YyenvwODh9nji05ZSsG6VO2KlZrjt1T645nczdcFcutQmnyFKIOzRiUEIk//mg2y7DC6o2NctX5bN5+7KFIPZhStihU6REjxwUkex8vKYGOEKel5Xok98oKfnhKTF3kwCgFMM0pAGz2pEIBHIgghTyt5M+UYNOGCN7jI54Y8lp7ekuxobxWKNl9Pd7WzohQWApBeP9iCTFrxrbbrUstF18W5tZsqXoUapoOAlwG38sYhZ+iqsdLzH6FsrfVPYG0bu3k3WChIDlIrmCtSS8Rk1i4CqriEnx1Eo5cH4X4BA5HWp7qddjGBhWULyzeOI/yMvGbfxjr+yVXo51tomWAOMMPYy6y8S8vnn/Z
*/