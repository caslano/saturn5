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
g+PgSQm/AM8zH7giSuwKsEkA9YTNYSvx94SDsUfAW+FY8U+Go7GLoKqfh9hPwSy4Rvwb4Rzsd+A8uEP8X8IWgdQLtoLfw9bwR9gGGpGsnwPdsAOsCz3pkuCz2C3hGthO/PfAV7Dvg6/CB8X/EdwaxDgS+3v4AfZZsUOjOO9kHERCj10PrsBuDFfCVvBPsL2E94FrsAfC5+Bw+DwcJeET4OvY+WI/ADdhLxB7JXwfe43Y2+Au
*/