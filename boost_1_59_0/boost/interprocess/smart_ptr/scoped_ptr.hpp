//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/scoped_ptr.hpp
//
// (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
// (C) Copyright Peter Dimov 2001, 2002
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/pointer_type.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/assert.hpp>
#include <boost/move/adl_move_swap.hpp>

//!\file
//!Describes the smart pointer scoped_ptr

namespace boost {
namespace interprocess {

//!scoped_ptr stores a pointer to a dynamically allocated object.
//!The object pointed to is guaranteed to be deleted, either on destruction
//!of the scoped_ptr, or via an explicit reset. The user can avoid this
//!deletion using release().
//!scoped_ptr is parameterized on T (the type of the object pointed to) and
//!Deleter (the functor to be executed to delete the internal pointer).
//!The internal pointer will be of the same pointer type as typename
//!Deleter::pointer type (that is, if typename Deleter::pointer is
//!offset_ptr<void>, the internal pointer will be offset_ptr<T>).
template<class T, class Deleter>
class scoped_ptr
   : private Deleter
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   scoped_ptr(scoped_ptr const &);
   scoped_ptr & operator=(scoped_ptr const &);

   typedef scoped_ptr<T, Deleter> this_type;
   typedef typename ipcdetail::add_reference<T>::type reference;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   typedef T element_type;
   typedef Deleter deleter_type;
   typedef typename ipcdetail::pointer_type<T, Deleter>::type pointer;

   //!Constructs a scoped_ptr, storing a copy of p(which can be 0) and d.
   //!Does not throw.
   explicit scoped_ptr(const pointer &p = 0, const Deleter &d = Deleter())
      : Deleter(d), m_ptr(p) // throws if pointer/Deleter copy ctor throws
   {}

   //!If the stored pointer is not 0, destroys the object pointed to by the stored pointer.
   //!calling the operator() of the stored deleter. Never throws
   ~scoped_ptr()
   {
      if(m_ptr){
         Deleter &del = static_cast<Deleter&>(*this);
         del(m_ptr);
      }
   }

   //!Deletes the object pointed to by the stored pointer and then
   //!stores a copy of p. Never throws
   void reset(const pointer &p = 0) // never throws
   {  BOOST_ASSERT(p == 0 || p != m_ptr); this_type(p).swap(*this);  }

   //!Deletes the object pointed to by the stored pointer and then
   //!stores a copy of p and a copy of d.
   void reset(const pointer &p, const Deleter &d) // never throws
   {  BOOST_ASSERT(p == 0 || p != m_ptr); this_type(p, d).swap(*this);  }

   //!Assigns internal pointer as 0 and returns previous pointer. This will
   //!avoid deletion on destructor
   pointer release() BOOST_NOEXCEPT
   {  pointer tmp(m_ptr);  m_ptr = 0;  return tmp; }

   //!Returns a reference to the object pointed to by the stored pointer.
   //!Never throws.
   reference operator*() const BOOST_NOEXCEPT
   {  BOOST_ASSERT(m_ptr != 0);  return *m_ptr; }

   //!Returns the internal stored pointer.
   //!Never throws.
   pointer &operator->() BOOST_NOEXCEPT
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the internal stored pointer.
   //!Never throws.
   const pointer &operator->() const BOOST_NOEXCEPT
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   pointer & get() BOOST_NOEXCEPT
   {  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   const pointer & get() const BOOST_NOEXCEPT
   {  return m_ptr;  }

   typedef pointer this_type::*unspecified_bool_type;

   //!Conversion to bool
   //!Never throws
   operator unspecified_bool_type() const BOOST_NOEXCEPT
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   //!Returns true if the stored pointer is 0.
   //!Never throws.
   bool operator! () const BOOST_NOEXCEPT // never throws
   {  return m_ptr == 0;   }

   //!Exchanges the internal pointer and deleter with other scoped_ptr
   //!Never throws.
   void swap(scoped_ptr & b) BOOST_NOEXCEPT // never throws
   {
      ::boost::adl_move_swap(static_cast<Deleter&>(*this), static_cast<Deleter&>(b));
      ::boost::adl_move_swap(m_ptr, b.m_ptr);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   pointer m_ptr;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!Exchanges the internal pointer and deleter with other scoped_ptr
//!Never throws.
template<class T, class D> inline
void swap(scoped_ptr<T, D> & a, scoped_ptr<T, D> & b) BOOST_NOEXCEPT
{  a.swap(b); }

//!Returns a copy of the stored pointer
//!Never throws
template<class T, class D> inline
typename scoped_ptr<T, D>::pointer to_raw_pointer(scoped_ptr<T, D> const & p)
{  return p.get();   }

} // namespace interprocess

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#if defined(_MSC_VER) && (_MSC_VER < 1400)
template<class T, class D> inline
T *to_raw_pointer(boost::interprocess::scoped_ptr<T, D> const & p)
{  return p.get();   }
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // #ifndef BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED

/* scoped_ptr.hpp
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
*/