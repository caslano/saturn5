//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_DEQUE_HPP
#define BOOST_CONTAINER_PMR_DEQUE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/deque.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using deque = boost::container::deque<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a deque
//! that uses a polymorphic allocator
template<class T>
struct deque_of
{
   typedef boost::container::deque
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_DEQUE_HPP

/* deque.hpp
TUFYX1RPVEFMX0NPTk5FQ1RJT05TLjNVVAUAAbZIJGCtVG1P20gQ/u5fMcp9AeQ6cLTqccdVZ0I4LIIdxU5ppEjWJt7gPa13Le86EIkffzNrczTtqfChRsbOeuaZZ96eYDmAo592eQHBwatX7u4cL3w+O00b/Q9f2/93yPMn6P7QcYnPN4QawovXU34Ib/J6ggPnlfexzuk9z98Qbkkk6d+QnJc5veJJ59n7j3S9a8R9aeFgdAgnZ2e/wTv49fjkow+XTAkuIbVcrXhz78N54U7+KtnjY2D4Jx+4BSaDPcCsFAaM3tgH1nDAdynWXBleADNQcLNuxAp/CAW25LARksMomS6i+G8fHkqxLnucnW7BlLqVBZRsy6Hhay62HUzNGgt6gwiIXwhjEbO1QqsAw3OwvKlMD0MkmDQa2JYJyVYYjlkora3N78Phum0kZjIs9NoM18+lCEpbfZPVAtlUbAe6tmA1tIb7QPY+VLoQG3piifCwbldSmNJ/oYUBVTHUDRguZQ+HroKbLgUOaV8tnyyhRvbC0sNoZSjaQ6mrPUMsaw+0aRuF4bAsaFdoLLwPrSp44+xdIZ6j9FV2JX+lZS/cC9AKWcEgTCFKB7BiRhgf7qLsOplncBfOZmGcLSC5gjBe9Hg3UXyJsyEw
*/