//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_LIST_HPP
#define BOOST_CONTAINER_PMR_LIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/list.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using list = boost::container::list<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a list
//! that uses a polymorphic allocator
template<class T>
struct list_of
{
   typedef boost::container::list
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* list.hpp
p7VTNTKPJTtLpa1DOkEzMGlKomRAlkQkswazScR0EjGbRaRxQBoGhIEhUKLiAxQ5xtskUYPczCNfSZxfItIvstjPIXOl/JwkYdPyUa6p1+f4vg1AZYpWa4KUgnS2WAUAzkkFsD0tJl9xcYdw3zZ7+mW+74Y6MD8e7kOX6zw8OCAMQ1SWId2urFrnktONGwcQPFIEATkCYKUIlWFmjvC9DWaWGXFVEIUBnXZIqxUwnmXEyjO0OfB9/86o6Ezfc7Pb5smFiKoK4ZUp6fe+muPq0BSOd+H92fs8v8r7qdFkqSKNM5I4IYkj4rhBkkRkaUAWCiQSLZwUIO2BK5bTCVFqq+DAMm+2hHOieFw97tuVFQIqUdnFaFWHx0H1EzhhqkpYytnyIc9VAEcIbAxAI3QhwPPRf+7aHQfmjgh36RZeZw0I3cv5vyUVUsNcONQ5gEP+ew3pYQHX14J8VWSl+tFwSBiGZFlm/LF2ggohOB6PubU7AREihDkM1BEAwO72ihHpc27ipozI2w4CQbcb0W2HHI9T0sQSjhIysmCmuvp8ru+4uBXjfWkiN9oFlbJVImDrdnMkl0I8dyCQRyba/NoqVkqZwJdZYs8KtPEASaqJMoFEI6SzwRTL+fLhF9KXDXBY76SEPDypJM24bbMoYaWoUgzp35Yy1hMWL6k2tLjm3iG9yiCbQTaBdAzZcMrFJyPCMEKpWe18drv/LAgC
*/