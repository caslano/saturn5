//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/stable_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using stable_vector = boost::container::stable_vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a stable_vector
//! that uses a polymorphic allocator
template<class T>
struct stable_vector_of
{
   typedef boost::container::stable_vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

/* stable_vector.hpp
HVl1DW1WYkOqKKlUVBnZJqZv00pFaczfcBFeFtUyS03S3qmFC/OoqzQZmWVeHFhTaZwJkmbeW22mpALapyV/GZUbvm2dqNUBIdzqBcWVznEd3AK6SMHxbarySGpLbx1R3+K9bF3+jZDtdI9I5dCKGr0ZDWYNWgqTmjZ9GMzfja/m9KE3nfZG82saX1BvdO3lvR+M3iI3UtyqSX4qtDTQQlO6KrJURgeX/6GVHnTm7+j8ajq8HE/mi8nV7N3F1eh8PhiP6AdqPKN/VTly+9mPDWpk6ZKDTy86z593TvGCnxarKivThZElxxk/SCkDqbN3NOpd9oMvi755SqHIsqUIP8LRyC5RFFrdSWtzJHOOtJH6Ds4oKsTKWIGz69F4MhvMgk4eB39O8zCrIkmvWQ2XlsnPQRAmQtOJVY1ZEykQ2sVyk1erJkJUAZyODg2dIPlM+h+5KAlkrVcPCxEr+VUpIazHkWVnYsgK0nyPeFHb3WTP0AnqUuZlO3gAjxyRFGbzIMlO8YXX5GHSBzX/BuOdSiM6QQnrgi2yQQ0VnH8vBaxZl5CIusxQnl+M/4P32M99X6Fm8xAXd+LUJsLb/ux8OpiwqMBW4pbwVpbuCWW4TiQKkXK5pnfz+aR7xvZLseJyXco0v3W5FdFyw9Ue
*/