// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAG_HPP
#define BOOST_GEOMETRY_CORE_TAG_HPP


#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class to attach a tag to a geometry
\details All geometries should implement a traits::tag<G>::type metafunction to indicate their
    own geometry type.
\ingroup traits
\par Geometries:
    - all geometries
\par Specializations should provide:
    - typedef XXX_tag type; (point_tag, box_tag, ...)
\tparam Geometry geometry
*/
template <typename Geometry, typename Enable = void>
struct tag
{
    typedef void type;
};

} // namespace traits



/*!
\brief \brief_meta{type, tag, \meta_geometry_type}
\details With Boost.Geometry, tags are the driving force of the tag dispatching
    mechanism. The tag metafunction is therefore used in every free function.
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/tag.qbk]}
*/
template <typename Geometry>
struct tag
{
    typedef typename traits::tag
        <
            typename geometry::util::bare_type<Geometry>::type
        >::type type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAG_HPP

/* tag.hpp
lLV46aFsSFELveez57Pns+ez57Pns+ez57Pns+ez5/P//dl2SMcaK+7f+Ug/1NEpogeK3kt0ruh09cs+mac57bOE+9vsfkwcym3Oo4PJx2/qO/C/Do748SenrFMn/s/Dp0Z8Ulr5pHj4dG/Dp1Z8jojzydmJT5b41CjQyqdOfIbQJUX3b8Mnuw2f1eJzpPZpRz4x8RkqPqlJ5rNNfI6KG5+aXeSjpGG8T5P4ZJvxacMnuw0f3yjH51jt0458BorPcWZ8kswnR3yGtZqHPuV4ADx2PQ+D4jM8fh4m+Oz6uOeLz/HxxyvBZ9fjExKfHPd4eeSz6/lTKz5TtE879qtefC5y8/HYr10fr5j4TNU+7RifRvEpN/MnyfFJP93xmWZ8ktwvv/gscY+7bZKzk/1KTfXOJ1t87oj38e/cp2NH73yC4nOn3q925BMSn7u0TzvyqRWfe8z8aSOf7DbyqRefe+N9/DvxaSOfmPjcb457kvk0is8DxifJfHxnyPyJxh33HG+fgW3k4xefO+J9atry8c4nID534pPSjnxyxecu7dOOfPLFp655v+za3c4nJD53t/BJ2e18asTnHr1f7chnsfjcq33akU+9+CzFJ13PpySP10bxuc/4JHm8GsTnfnyUlXw+TeLzgO2TfD6+0Y7PMrNfSR6vgeLzoPFJ8njliM9D9n4ln88k8XnY9kk+n5D4LMdHN0lP8njVis8K45Pk8aoXn5XGJ8nxiYnPI8YnyfFpFJ+0Zh/3+461G993fGc6Pp3ifHKMz258vwiIT+c4nxrjsxv34UHx8YmPleR+lYpPT+OT5H7NFZ9M45Pkfi0Tn17ik5rkfkXFJ8v1cfdrN77HbRGfvq6Pu1+78X2nUXx+1Wr++Hbzvs43xvEZ0Gr++Hfzvi4gPgdrn1/w/WJn+QTFZ6DxSTKfkPgcavYryfvexeIzyPgked8bFZ8jtE877sO3iU9A+7TjPtw3VvZLyfUryec2fvE5TPeykvfJFp/D6ZLTjudIQfGZZ/Yryec2peIz3/gk+XyjRnxq7fFJPp868bnR9kk+n6j4LNDj3I7nWg3ic4v2acfzHxWU+zEzzkmeF37xedD4JHle5IjPQ/Y4J59Pvvg8bPskn0+N+CzX49yOdaNOfFZon3asG1HxWdnq/PLt5vW9QXweaXV++Vv47DofdZbjU99qHfPt5vU9S3webeXj9/YhH2+fgPg8Zh/35McnKD6P2z7Jj09IfFbZPsmPz1zxecL2SX586sTnSTMPkxyfqPg8ZXySHJ8G8VltfJIcnybxedr4JDk+vnGOz1Fc3+3nj0nePwfE52jjk+T9c1B8jtE+7TjfZ4pPtvZpx/leJz7HGp8k7+dXi89x2qcd68YW8RmmfdqxbjSJz774+PUYt3FdTm9jnH3jHZ/9xMdK0icgPvvbPm3/jjawrXVMfPxx+1XTZj7ex71UfA4w+5Wkz1zxOdDsVxs+A9v6Xik+D22Kf16X7nk9TW/jecJG8VmGT2o7fBrF50HxSU/SJ2uC3Ldskutgkj7Z4rMcn5p2+OSLzwp8lJW8T434rMQnpx3jXCc+z8T9LmPntZvPo1aLzzrz+0WSPlvE51nt0458msTnOfFJTdIn62zHJxo/Pin47OZztoD4vGjGJ0mfoPis1z7tyCckPi+Z8UnSp1Z85rQYnyTWH/G51oxPkj4bxWeu9mlHPtvE5zozPkn6qImOz0ktzq/dv+5kic9IMz5J+mSLzynapx35TBKfU834JOkTEp8q8zwqyfN0sfiEXR87Gb+XT1vfB8VnuvZpx/qzTXxmGJ8k8/GdI8834n+XkXys3RjngPjc4vpIPvE+u84nKD4L7d9lks8=
*/