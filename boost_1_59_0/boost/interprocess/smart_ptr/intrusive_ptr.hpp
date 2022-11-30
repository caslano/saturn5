//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/intrusive_ptr.hpp
//
// (C) Copyright Peter Dimov 2001, 2002
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_INTRUSIVE_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_INTRUSIVE_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//!\file
//!Describes an intrusive ownership pointer.

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/assert.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/core.hpp>

#include <iosfwd>               // for std::basic_ostream

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less

namespace boost {
namespace interprocess {

//!The intrusive_ptr class template stores a pointer to an object
//!with an embedded reference count. intrusive_ptr is parameterized on
//!T (the type of the object pointed to) and VoidPointer(a void pointer type
//!that defines the type of pointer that intrusive_ptr will store).
//!intrusive_ptr<T, void *> defines a class with a T* member whereas
//!intrusive_ptr<T, offset_ptr<void> > defines a class with a offset_ptr<T> member.
//!Relies on unqualified calls to:
//!
//!  void intrusive_ptr_add_ref(T * p) BOOST_NOEXCEPT;
//!  void intrusive_ptr_release(T * p) BOOST_NOEXCEPT;
//!
//!  with (p != 0)
//!
//!The object is responsible for destroying itself.
template<class T, class VoidPointer>
class intrusive_ptr
{
   public:
   //!Provides the type of the internal stored pointer.
   typedef typename boost::intrusive::
      pointer_traits<VoidPointer>::template
         rebind_pointer<T>::type                pointer;
   //!Provides the type of the stored pointer.
   typedef T element_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef VoidPointer VP;
   typedef intrusive_ptr this_type;
   typedef pointer this_type::*unspecified_bool_type;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   BOOST_COPYABLE_AND_MOVABLE(intrusive_ptr)

   public:
   //!Constructor. Initializes internal pointer to 0.
   //!Does not throw
   intrusive_ptr() BOOST_NOEXCEPT
	   : m_ptr(0)
   {}

   //!Constructor. Copies pointer and if "p" is not zero and
   //!"add_ref" is true calls intrusive_ptr_add_ref(to_raw_pointer(p)).
   //!Does not throw
   intrusive_ptr(const pointer &p, bool add_ref = true) BOOST_NOEXCEPT
	   : m_ptr(p)
   {
      if(m_ptr != 0 && add_ref) intrusive_ptr_add_ref(ipcdetail::to_raw_pointer(m_ptr));
   }

   //!Copy constructor. Copies the internal pointer and if "p" is not
   //!zero calls intrusive_ptr_add_ref(to_raw_pointer(p)). Does not throw
   intrusive_ptr(intrusive_ptr const & rhs) BOOST_NOEXCEPT
      :  m_ptr(rhs.m_ptr)
   {
      if(m_ptr != 0) intrusive_ptr_add_ref(ipcdetail::to_raw_pointer(m_ptr));
   }

   //!Move constructor. Moves the internal pointer. Does not throw
   intrusive_ptr(BOOST_RV_REF(intrusive_ptr) rhs) BOOST_NOEXCEPT
	   : m_ptr(rhs.m_ptr) 
   {
	   rhs.m_ptr = 0;
   }

   //!Constructor from related. Copies the internal pointer and if "p" is not
   //!zero calls intrusive_ptr_add_ref(to_raw_pointer(p)). Does not throw
   template<class U> intrusive_ptr(intrusive_ptr<U, VP> const & rhs) BOOST_NOEXCEPT
      :  m_ptr(rhs.get())
   {
      if(m_ptr != 0) intrusive_ptr_add_ref(ipcdetail::to_raw_pointer(m_ptr));
   }

   //!Destructor. Calls reset(). Does not throw
   ~intrusive_ptr()
   {
      reset();
   }

   //!Assignment operator. Equivalent to intrusive_ptr(r).swap(*this).
   //!Does not throw
   intrusive_ptr & operator=(BOOST_COPY_ASSIGN_REF(intrusive_ptr) rhs) BOOST_NOEXCEPT
   {
      this_type(rhs).swap(*this);
      return *this;
   }

   //!Move Assignment operator
   //!Does not throw
   intrusive_ptr & operator=(BOOST_RV_REF(intrusive_ptr) rhs) BOOST_NOEXCEPT 
   {
	   rhs.swap(*this);
	   rhs.reset();
	   return *this;
   }

   //!Assignment from related. Equivalent to intrusive_ptr(r).swap(*this).
   //!Does not throw
   template<class U> intrusive_ptr & operator=(intrusive_ptr<U, VP> const & rhs) BOOST_NOEXCEPT
   {
      this_type(rhs).swap(*this);
      return *this;
   }

   //!Assignment from pointer. Equivalent to intrusive_ptr(r).swap(*this).
   //!Does not throw
   intrusive_ptr & operator=(pointer rhs) BOOST_NOEXCEPT
   {
      this_type(rhs).swap(*this);
      return *this;
   }

   //!Release internal pointer and set it to 0. If internal pointer is not 0, calls
   //!intrusive_ptr_release(to_raw_pointer(m_ptr)). Does not throw
   void reset() BOOST_NOEXCEPT {
      if(m_ptr != 0) {
        pointer ptr = m_ptr;
        m_ptr = 0;
        intrusive_ptr_release(ipcdetail::to_raw_pointer(ptr));
      }
   }

   //!Returns a reference to the internal pointer.
   //!Does not throw
   pointer &get() BOOST_NOEXCEPT
   {  return m_ptr;  }

   //!Returns a reference to the internal pointer.
   //!Does not throw
   const pointer &get() const BOOST_NOEXCEPT
   {  return m_ptr;  }

   //!Returns *get().
   //!Does not throw
   T & operator*() const BOOST_NOEXCEPT
   {  return *m_ptr; }

   //!Returns *get().
   //!Does not throw
   const pointer &operator->() const BOOST_NOEXCEPT
   {  return m_ptr;  }

   //!Returns get().
   //!Does not throw
   pointer &operator->() BOOST_NOEXCEPT
   {  return m_ptr;  }

   //!Conversion to boolean.
   //!Does not throw
   operator unspecified_bool_type () const BOOST_NOEXCEPT
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   //!Not operator.
   //!Does not throw
   bool operator! () const BOOST_NOEXCEPT
   {  return m_ptr == 0;   }

   //!Exchanges the contents of the two smart pointers.
   //!Does not throw
   void swap(intrusive_ptr & rhs) BOOST_NOEXCEPT
   {  ::boost::adl_move_swap(m_ptr, rhs.m_ptr);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   pointer m_ptr;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!Returns a.get() == b.get().
//!Does not throw
template<class T, class U, class VP> inline
bool operator==(intrusive_ptr<T, VP> const & a,
                intrusive_ptr<U, VP> const & b) BOOST_NOEXCEPT
{  return a.get() == b.get(); }

//!Returns a.get() != b.get().
//!Does not throw
template<class T, class U, class VP> inline
bool operator!=(intrusive_ptr<T, VP> const & a,
                intrusive_ptr<U, VP> const & b) BOOST_NOEXCEPT
{  return a.get() != b.get(); }

//!Returns a.get() == b.
//!Does not throw
template<class T, class VP> inline
bool operator==(intrusive_ptr<T, VP> const & a,
                       const typename intrusive_ptr<T, VP>::pointer &b) BOOST_NOEXCEPT
{  return a.get() == b; }

//!Returns a.get() != b.
//!Does not throw
template<class T, class VP> inline
bool operator!=(intrusive_ptr<T, VP> const & a,
                const typename intrusive_ptr<T, VP>::pointer &b) BOOST_NOEXCEPT
{  return a.get() != b; }

//!Returns a == b.get().
//!Does not throw
template<class T, class VP> inline
bool operator==(const typename intrusive_ptr<T, VP>::pointer &a,
                intrusive_ptr<T, VP> const & b) BOOST_NOEXCEPT
{  return a == b.get(); }

//!Returns a != b.get().
//!Does not throw
template<class T, class VP> inline
bool operator!=(const typename intrusive_ptr<T, VP>::pointer &a,
                       intrusive_ptr<T, VP> const & b) BOOST_NOEXCEPT
{  return a != b.get(); }

//!Returns a.get() < b.get().
//!Does not throw
template<class T, class VP> inline
bool operator<(intrusive_ptr<T, VP> const & a,
               intrusive_ptr<T, VP> const & b) BOOST_NOEXCEPT
{
   return std::less<typename intrusive_ptr<T, VP>::pointer>()
      (a.get(), b.get());
}

//!Exchanges the contents of the two intrusive_ptrs.
//!Does not throw
template<class T, class VP> inline
void swap(intrusive_ptr<T, VP> & lhs,
          intrusive_ptr<T, VP> & rhs) BOOST_NOEXCEPT
{  lhs.swap(rhs); }

// operator<<
template<class E, class T, class Y, class VP>
inline std::basic_ostream<E, T> & operator<<
   (std::basic_ostream<E, T> & os, intrusive_ptr<Y, VP> const & p) BOOST_NOEXCEPT
{  os << p.get(); return os;  }

//!Returns p.get().
//!Does not throw
template<class T, class VP>
inline typename boost::interprocess::intrusive_ptr<T, VP>::pointer
   to_raw_pointer(intrusive_ptr<T, VP> p) BOOST_NOEXCEPT
{  return p.get();   }

/*Emulates static cast operator. Does not throw*/
/*
template<class T, class U, class VP>
inline boost::interprocess::intrusive_ptr<T, VP> static_pointer_cast
   (boost::interprocess::intrusive_ptr<U, VP> const & p) BOOST_NOEXCEPT
{  return do_static_cast<U>(p.get());  }
*/
/*Emulates const cast operator. Does not throw*/
/*
template<class T, class U, class VP>
inline boost::interprocess::intrusive_ptr<T, VP> const_pointer_cast
   (boost::interprocess::intrusive_ptr<U, VP> const & p) BOOST_NOEXCEPT
{  return do_const_cast<U>(p.get());   }
*/

/*Emulates dynamic cast operator. Does not throw*/
/*
template<class T, class U, class VP>
inline boost::interprocess::intrusive_ptr<T, VP> dynamic_pointer_cast
   (boost::interprocess::intrusive_ptr<U, VP> const & p) BOOST_NOEXCEPT
{  return do_dynamic_cast<U>(p.get()); }
*/

/*Emulates reinterpret cast operator. Does not throw*/
/*
template<class T, class U, class VP>
inline boost::interprocess::intrusive_ptr<T, VP>reinterpret_pointer_cast
   (boost::interprocess::intrusive_ptr<U, VP> const & p) BOOST_NOEXCEPT
{  return do_reinterpret_cast<U>(p.get());   }
*/

} // namespace interprocess

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#if defined(_MSC_VER) && (_MSC_VER < 1400)
//!Returns p.get().
//!Does not throw
template<class T, class VP>
inline T *to_raw_pointer(boost::interprocess::intrusive_ptr<T, VP> p) BOOST_NOEXCEPT
{  return p.get();   }
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_INTRUSIVE_PTR_HPP_INCLUDED

/* intrusive_ptr.hpp
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
*/