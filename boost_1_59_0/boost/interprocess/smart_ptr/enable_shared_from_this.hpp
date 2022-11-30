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
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
*/