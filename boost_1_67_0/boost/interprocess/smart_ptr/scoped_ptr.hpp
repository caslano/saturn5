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
   pointer release()
   {  pointer tmp(m_ptr);  m_ptr = 0;  return tmp; }

   //!Returns a reference to the object pointed to by the stored pointer.
   //!Never throws.
   reference operator*() const
   {  BOOST_ASSERT(m_ptr != 0);  return *m_ptr; }

   //!Returns the internal stored pointer.
   //!Never throws.
   pointer &operator->()
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the internal stored pointer.
   //!Never throws.
   const pointer &operator->() const
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   pointer & get()
   {  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   const pointer & get() const
   {  return m_ptr;  }

   typedef pointer this_type::*unspecified_bool_type;

   //!Conversion to bool
   //!Never throws
   operator unspecified_bool_type() const
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   //!Returns true if the stored pointer is 0.
   //!Never throws.
   bool operator! () const // never throws
   {  return m_ptr == 0;   }

   //!Exchanges the internal pointer and deleter with other scoped_ptr
   //!Never throws.
   void swap(scoped_ptr & b) // never throws
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
void swap(scoped_ptr<T, D> & a, scoped_ptr<T, D> & b)
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