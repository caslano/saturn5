//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_FLAT_MAP_HPP
#define BOOST_CONTAINER_PMR_FLAT_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key > >
using flat_map = boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
using flat_multimap = boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

#endif

//! A portable metafunction to obtain a flat_map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_map_of
{
   typedef boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

//! A portable metafunction to obtain a flat_multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_multimap_of
{
   typedef boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_FLAT_MAP_HPP

/* flat_map.hpp
2gtgnSKn+S1zWJ+Imzns/a9gnp+i27tsy4SbYEEynnPeux++DUsi4zkD3+1tgmWInH86wjcPlidyvjzx+ythRWR+Zrct2fMUrIrMw8wcc2A1ohazX4I1KdYRnZPtJ+53dbG4nTHnulZtOWDBBkwcM7MdwVw/R8ctTjk/B+YTNsn7bQCWoFiaYtmKFZB5mZl3AGClwqZ5F70OqxI514+efiOsQVji2o31sDaR8/xL/3w8rJvMx2zDxsSRMFd/tL07pvwSmJ+Mt9dxTuReWCIZb+/AWUU2LE3EhRecdz4s2zEu5AqTYd320D7ZjDNYoYljZo6NsDIlrkKxKjIfs5rO3IthjWQ2s+/GTM+AtYs48z1qWJ8wc68cZu2NNvMuGyyOjNdprjdhCWQ2jB+ryNLIvDB+TCULibh53W8lwsLCRmx+ZS+sVOQc/D1hGp8s7ruY2awWGp/Rxrb321xtrH/fx4QGt1uyDsW6yALMYkpP+QTm/oXqZOa9OXsyzEdmM3tx8Y0rYQnC8l66zA1LEznvzji4DBYScU37n06BhYXNCv1jAqxU5Jx30jGlsCqlvfpoY3Pbt7paWHs/xNzmuvmDdQ/Cush8zP6VffF0WITF9cbkuR50D/0FZu+LtqO6RwyFxZN5mfmOPvArLIXMw8ycM8DSyHzMpk6afh8sR7S3bOTcebBC0Z55vxhWJmzTf1797JDd56pmtitm7uC+lazBtMfsT6P3Pg9rE7Zh3/s7YD0iZ/Mx4T/CImQ+ZjdvfGE3zDdAy4WZGdewABlv75eE90tgScKmZZ/SCstQLFexIjIvs8LDh7+KcVbO7MeYOa6nnrvoIKzG5GS246DVAWsScebaCdZO5mHGt+lOkfP2ZX8PwvqFbdozORtm/epsQTJeS2/5lFMP2QxXEhnW0W7aHt6a/YdlsExhj2VfnQXLN+0xm3jpb3NgJaw9Mnb//T5XJRnOpfpiZtA81XvFsEZh5pkFWKeTUf8iZFiee6KW5xyXe/+g/RRzAdv+znFZzH6OmcnOs25z2cz6Y0Isbo7LT4blsjfmAnYvhM7LWdwvdM1sjqmwFDIvM3OPCJZpcjIz94hg+SLO3COCFZPZzMw8H6xS1GL6B6sW7Y26c+nZhyzB1cTi9sWEB/tA1iLM5IS1KdZh2mN29xl5b8H6lfYiZF5mZpnBvAeic5plBosn43FmmcFSRJx5fxMWYibrLCBz6l8Rmc1s5xf+PbAKsjhm24Y/diOsWdS5fLV3FKyDtTcg2utSrIfMZtb7ydCvYK5ItJk5f5hP2HDX+pmwBDIvM9/pxy2BpYo4MwZhIWaylnDEuQ+Fwn7Y+PuPsGKyBGbPfHjeq7AGUefTz8yejjHfSob5kF9pzI/+IeMLWCeZn1l+w9c7YRFhN9zjc8P8v1F7zMzvVsMSyDzMjon9bSssiczHzFxbwDLJbGbeqwOpsDzR3vjU0OmwIpGz7qQj74FVipyLpxzZBKsXOQuv+XkurIX3QexD2hTrELXM7F24G9Yvaum/bMcVMOt3VovY1wXIeNykpmsuhiUJu3Pqtc/DMpScOSLukuEX3QgrFNZztdULKxc5zTEOViPixt/UkgFrErbs1GHjYR0i5+9zav8M6xVxV168/myY+2C0rfn69UyYn4znNHPNsAQyH7N1V5x9KSxd5Jya7n8QliNy3nbfutNgBQedxgRd0zHbHzMzykoUK1OsQrEqxWqEmTlVWJ0S16BYk2ItirUp1qFYl2I9ivUpNqCYi8TJjFjMzJw4zEfmtKwDJDazpxIvLYQlCds87KEyWAaZl5l7wbcHYTlKnXki5w+7jnoFVizs1JFnbIBVivYOWOF5sDoyP7OK6z4=
*/