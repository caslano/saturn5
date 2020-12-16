// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP
#define BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


// class to choose between point_iterator and segment_iterator
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct iterator_selector
{
    typedef geometry::segment_iterator<Geometry> iterator_type;

    static inline iterator_type begin(Geometry& geometry)
    {
        return segments_begin(geometry);
    }

    static inline iterator_type end(Geometry& geometry)
    {
        return segments_end(geometry);
    }
};

template <typename MultiPoint>
struct iterator_selector<MultiPoint, multi_point_tag>
{
    typedef geometry::point_iterator<MultiPoint> iterator_type;

    static inline iterator_type begin(MultiPoint& multipoint)
    {
        return points_begin(multipoint);
    }

    static inline iterator_type end(MultiPoint& multipoint)
    {
        return points_end(multipoint);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHS_DETAIL_DISTANCE_ITERATOR_SELECTOR_HPP

/* iterator_selector.hpp
8SuhpnxtglrqX57mNfNe7A9fpvl+fflUS0eOw305HX8VnsKLB9fNxfa1AX8umey8oZcZs5UYTYaVcnFT3xW8yMMrIV/qPPALnoCPY9LBTD12bTkO0ANrvXbPMdwobvnhc/E/cEcHPTjRHqvrS6+t3QUObeBT9aapLwcBLHiuBx/p/cef4H8zZVqaqZee+PEDOniK+WoLLYdrit2iXQuocdi4JIEP+xypBnsM43HVt27arGUK3ks0vY0T59LVhfTKqhlmlspw96A+7obXU6jXaH0jjnPpp7ID6e9XIc7R4G1yeAxzdvWiefiA0XA+qoeZ9QlMuUTbjKTn4e3F5DRIDz3fXI0N5c2Z58vGdZ7U014v+7yCGsnidbGdfVt7GeeNA/fzuubQgwVpy2U4viLt5ee+g/TtgqKwfZe9466jsKLeIj2uzuqFwpcS1pwDhiWEJ3REEd7ZffrgcCGfw6qS3lsRpkylNx+Wpn/FvpJerXrevKJ+5lhTueHqNhk8PmqP5sHBvj8xYTAeoGf1Sf2+ME8fJe5qfvxZrfLQSw9SE334kv3NB63lYBXt594zSohtL/tLbM6Xz8Hb7JOXmL+k3pHPHmrvV2cYpTvI0Tdm+rE0ZLBnF+LLH/1aY4L13TN3mu/LV7emMjC9oz3D6u3DxJzmS/kEp22FEeVpgolwqbJZoqw6LGrmeAqzTph7Xed6PPOSPbQqJf8zfe28+xeGXWLzNfw70c3756sjuJovKW48q05py7Rp9Sj8iKSxInbTq/LaeRSN/JPeiQuTn9DeH6knmFMwoMbj0T36fEahf/svp33P6qoe6KpFl/X3S3MLPnvnubK6Mc/hRarbXHrwW9pWveS/jZMrBdE7dMwdOhGf5sNl1Xyt+nr3umBuhl8Xxsozz3bPuIDnnsRLbvcHxPque4lNKnqhYgyn6aVst2B+S89XwJxE1vH6AX0FJ2Pr9QH3Qsxc1kpPJe5njrpsjtgF1+BvJlq8NOzIXgwG4MHzcOWGuBY2fw6IOcfX+31onDx1eLghYoKH+lWGE+aV06HwvYq5vSOemCFva/VNHjr0mJ7vrjbU4aRyctkQXraG9Snph6nmfuekfi4x8KSkXvsVBtq/udvvY6F5+MWn1cws8R4Q46vdkzP105KmGXkJ7n8pXqtp7cbWdJnHt4V2dt49vbm6/Yu26OGZHLq8Zyjv561z9778eO+9TmPdPS/O9PTZm6AmQt/R+lXpzEx34E473haPoKt1rqNrD/WiX383J/ByFpU3d4R6zwqavzCMGQ/rm/FkwnhBb93rC7U6S7/WEy9reEkXLVM/UZW9T32E7sRB8IZUDeR5K9645iRd3jU2rXDUGVA7PbiHdvK+CDiVKid/MHXMbOMcelgw7xbfi93mC/AmHlwZ7N9TYsRnH/4dPNNvay7yKNvjEXrz7/u8xeo0pZliLj5bATc6821zfsgr6MlXnU9Pw7AtGeAB76O43rwdm/6ywFFzxYI2voUrZ+D1qXHNLgfNKtlg5hvPTcGyuG3tjdeitvwdWbEXl8dj+GXqp9M/YlzcDPOAvlsSwvf2AStr89bG7sVjpWEPvK8Ehw+YIVKo1W/2qK27fKI1tHEDPGEeK2UWGcsneYADPwnwMu1xzho/79cVXtPSk8WzQAY+JY57/p1cTKL9F9mjfJyvrV8a6ZG1tGM9OUvFP+Djdf5CHE/C1DZ8OXNoHLPnuNu8o4tqGR/T+IHeNXiEsKNuaWd1Lc0bV8xDOG8fT+LyeLXER35LG359Bu6l0guuO38yPHpDB9If9SLo6HXWFGy2cw45fBqsceYWJVbXD7iW/n/mNTXO8YP7089JAp414oNXFze9/yEvOxA=
*/