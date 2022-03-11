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