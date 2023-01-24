//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SLIST_HPP
#define BOOST_CONTAINER_PMR_SLIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/slist.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using slist = boost::container::slist<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a slist
//! that uses a polymorphic allocator
template<class T>
struct slist_of
{
   typedef boost::container::slist
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* slist.hpp
SYQ8Mfz+t/f55NOKrL9CJzfIqMRUMJ1MydM9yklB0utBrilLDzpkvo0rR2c1Z7S1yTe+onjfj17nxMnrZNc93/jWKV56/h56Xcv3/eIjDO4pOfLZd/H0l3fZ2yqZt2WtnT6HBhdDffVa4AMWIX+NBKJvXJ9LvA4cgIOq8lgrOBuQmnN1m/CYELzgC4u0YDxCu/5gnvyDWRpxeN7F79Ym+SR+xgOWW80LfH2ORSVQ3y7mzqla9y48bBqAuPlcAM0YrSYNSjhsiQjj8bgZBvLdRgCgUQCCr5lemZ2wqZAS+Ft/8PMAWGfx3tK0tBaPF8F5F1o9xZDhzvgml3YuzG5M201cfC58i/Z/c8e2n2/n5dfHSITOs+dn8VfnLP3OEU4OfhFdvQ3z4J/jjj/LZDhiWu4jyRRB4X1CL4NBmpErIUkEE4m3oRdW0zXe3L2NtWSVq26LC+WQ48kZtO+TJxnXR9tMReglHUrn2XUjXhxd403L97GRrXFtqtgVBVnOfUe3+Ml7tumlA7QKjUK8D7KRJJpurnjmeslnn7ckR9bQiaKcCKp8nmMbW+SmID35BHLtNOfOvgXVXw45Aj5YaY1iYi35IGN3PyMdn+ahMxssZU9wVX8eO3wr5x4/w+7td/HgD3+N3tHfpX/sgzzzhWVefmZ34QdoWdcDob+FaILA4WHDWgks9hqIewiH90kkASXUBdhACiYGlNI0+fjE
*/