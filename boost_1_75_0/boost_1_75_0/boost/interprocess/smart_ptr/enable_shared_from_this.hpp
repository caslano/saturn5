//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/enable_shared_from_this.hpp
//
// (C) Copyright Peter Dimov 2002
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
#define BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/assert.hpp>
#include <boost/interprocess/smart_ptr/weak_ptr.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>

//!\file
//!Describes an utility to form a shared pointer from this

namespace boost{
namespace interprocess{

//!This class is used as a base class that allows a shared_ptr to the current
//!object to be obtained from within a member function.
//!enable_shared_from_this defines two member functions called shared_from_this
//!that return a shared_ptr<T> and shared_ptr<T const>, depending on constness, to this.
template<class T, class A, class D>
class enable_shared_from_this
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   protected:
   enable_shared_from_this()
   {}

   enable_shared_from_this(enable_shared_from_this const &)
   {}

   enable_shared_from_this & operator=(enable_shared_from_this const &)
   {  return *this;  }

   ~enable_shared_from_this()
   {}
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   shared_ptr<T, A, D> shared_from_this()
   {
      shared_ptr<T, A, D> p(_internal_weak_this);
      BOOST_ASSERT(ipcdetail::to_raw_pointer(p.get()) == this);
      return p;
   }

   shared_ptr<T const, A, D> shared_from_this() const
   {
      shared_ptr<T const, A, D> p(_internal_weak_this);
      BOOST_ASSERT(ipcdetail::to_raw_pointer(p.get()) == this);
      return p;
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef T element_type;
   mutable weak_ptr<element_type, A, D> _internal_weak_this;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED


/* enable_shared_from_this.hpp
kabBAYAlYHNkJ+yWJBVYROkb4Vfh2qgdvOqIDSpTXHffUNPus1gIafkNE7fZssxU0t1yzIw/41/XJT8leLPRP3yplrqxrR/3hrWOWlcTjY+l3aOROmfIYx0oZj0i2x7M/9NBP+dSxX4dIfhxI7vuGkhnADz8keRMNkm0pASWPVrfilC+ryfikxROwlMnoTf+UuuMXfYkLiXpd63+4jxsAxOKUX4SqqPHclVa8DHG/DT/Tl0zNuAurDlC3QefqsR30pTB1v50zJS/aKTJkvhuFJ7tHfjMJkb1ehowAdDMCojB2JMUxjYOoLAZE26sLFGbPMkrvtgQVwGrDTJL5hK0ycHR/VOpZe7NhPe26lNL83dg+TASuKttc3h35I/yCwafkJzXbRg+0TkEfBBrMMUExBt+ZZXlSAIXukPzoeYTtXe+o1N/dAVtc1s0vCw8Z7zwsGWt1i88x6NFW95R24OcHyIKCuwKwChPDP5JJs9g4BKw5GIEHLBnlRwQs8D4JHKH9yjmn2aSH5gXKK1C9Egk+8VwLaS2/KLi2xHfHbU/jSjHFD484gJyIfyI8+gQl3v/xnEKvVJZZnlnHchZFPD9iai9+4sQr2NHrxCdVRGl66DG4KS7lIQ1/RSKaYWQXZ8WMcOpTVsoog3Sri1MKykxYHU4r5n1aGVTI5ft3ksEiv7sLtFiObIrbRztb9qoOscl8Sv9cfergDEJSTeC
*/