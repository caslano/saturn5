//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/shared_ptr.hpp
//
// (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
// (C) Copyright Peter Dimov 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHARED_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_SHARED_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/cast_tags.hpp>
#include <boost/assert.hpp>
#include <boost/interprocess/smart_ptr/detail/shared_count.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/detail/nothrow.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/smart_ptr/deleter.hpp>
#include <boost/static_assert.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#include <iosfwd> // for std::basic_ostream

//!\file
//!Describes the smart pointer shared_ptr

namespace boost{
namespace interprocess{

template<class T, class VoidAllocator, class Deleter> class weak_ptr;
template<class T, class VoidAllocator, class Deleter> class enable_shared_from_this;

namespace ipcdetail{

template<class T, class VoidAllocator, class Deleter>
inline void sp_enable_shared_from_this
  (shared_count<T, VoidAllocator, Deleter> const & pn
  ,enable_shared_from_this<T, VoidAllocator, Deleter> *pe
  ,T *ptr)

{
   (void)ptr;
   if(pe != 0){
      pe->_internal_weak_this._internal_assign(pn);
   }
}

template<class T, class VoidAllocator, class Deleter>
inline void sp_enable_shared_from_this(shared_count<T, VoidAllocator, Deleter> const &, ...)
{}

} // namespace ipcdetail

//!shared_ptr stores a pointer to a dynamically allocated object.
//!The object pointed to is guaranteed to be deleted when the last shared_ptr pointing to
//!it is destroyed or reset.
//!
//!shared_ptr is parameterized on
//!T (the type of the object pointed to), VoidAllocator (the void allocator to be used
//!to allocate the auxiliary data) and Deleter (the deleter whose
//!operator() will be used to delete the object.
//!
//!The internal pointer will be of the same pointer type as typename
//!VoidAllocator::pointer type (that is, if typename VoidAllocator::pointer is
//!offset_ptr<void>, the internal pointer will be offset_ptr<T>).
//!
//!Because the implementation uses reference counting, cycles of shared_ptr
//!instances will not be reclaimed. For example, if main() holds a
//!shared_ptr to A, which directly or indirectly holds a shared_ptr back
//!to A, A's use count will be 2. Destruction of the original shared_ptr
//!will leave A dangling with a use count of 1.
//!Use weak_ptr to "break cycles."
template<class T, class VoidAllocator, class Deleter>
class shared_ptr
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef shared_ptr<T, VoidAllocator, Deleter> this_type;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   typedef T                                                   element_type;
   typedef T                                                   value_type;
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<T>::type                               pointer;
   typedef typename ipcdetail::add_reference
                     <value_type>::type                        reference;
   typedef typename ipcdetail::add_reference
                     <const value_type>::type                  const_reference;
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<const Deleter>::type                               const_deleter_pointer;
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<const VoidAllocator>::type                         const_allocator_pointer;

   BOOST_COPYABLE_AND_MOVABLE(shared_ptr)
   public:

   //!Constructs an empty shared_ptr.
   //!Use_count() == 0 && get()== 0.
   shared_ptr()
      :  m_pn() // never throws
   {}

   //!Constructs a shared_ptr that owns the pointer p. Auxiliary data will be allocated
   //!with a copy of a and the object will be deleted with a copy of d.
   //!Requirements: Deleter and A's copy constructor must not throw.
   explicit shared_ptr(const pointer&p, const VoidAllocator &a = VoidAllocator(), const Deleter &d = Deleter())
      :  m_pn(p, a, d)
   {
      //Check that the pointer passed is of the same type that
      //the pointer the allocator defines or it's a raw pointer
      typedef typename boost::intrusive::
         pointer_traits<pointer>::template
            rebind_pointer<T>::type                         ParameterPointer;

      BOOST_STATIC_ASSERT((ipcdetail::is_same<pointer, ParameterPointer>::value) ||
                          (ipcdetail::is_pointer<pointer>::value));
      ipcdetail::sp_enable_shared_from_this<T, VoidAllocator, Deleter>( m_pn, ipcdetail::to_raw_pointer(p), ipcdetail::to_raw_pointer(p) );
   }

   //!Copy constructs a shared_ptr. If r is empty, constructs an empty shared_ptr. Otherwise, constructs
   //!a shared_ptr that shares ownership with r. Never throws.
   shared_ptr(const shared_ptr &r)
      :  m_pn(r.m_pn) // never throws
   {}

   //!Constructs a shared_ptr that shares ownership with other and stores p.
   //!Postconditions: get() == p && use_count() == r.use_count().
   //!Throws: nothing.
   shared_ptr(const shared_ptr &other, const pointer &p)
      :  m_pn(other.m_pn, p)
   {}

   //!If r is empty, constructs an empty shared_ptr. Otherwise, constructs
   //!a shared_ptr that shares ownership with r. Never throws.
   template<class Y>
   shared_ptr(shared_ptr<Y, VoidAllocator, Deleter> const & r)
      :  m_pn(r.m_pn) // never throws
   {}

   //!Constructs a shared_ptr that shares ownership with r and stores
   //!a copy of the pointer stored in r.
   template<class Y>
   explicit shared_ptr(weak_ptr<Y, VoidAllocator, Deleter> const & r)
      :  m_pn(r.m_pn) // may throw
   {}

   //!Move-Constructs a shared_ptr that takes ownership of other resource and
   //!other is put in default-constructed state.
   //!Throws: nothing.
   explicit shared_ptr(BOOST_RV_REF(shared_ptr) other)
      :  m_pn()
   {  this->swap(other);   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   template<class Y>
   shared_ptr(shared_ptr<Y, VoidAllocator, Deleter> const & r, ipcdetail::static_cast_tag)
      :  m_pn( pointer(static_cast<T*>(ipcdetail::to_raw_pointer(r.m_pn.to_raw_pointer())))
             , r.m_pn)
   {}

   template<class Y>
   shared_ptr(shared_ptr<Y, VoidAllocator, Deleter> const & r, ipcdetail::const_cast_tag)
      :  m_pn( pointer(const_cast<T*>(ipcdetail::to_raw_pointer(r.m_pn.to_raw_pointer())))
             , r.m_pn)
   {}

   template<class Y>
   shared_ptr(shared_ptr<Y, VoidAllocator, Deleter> const & r, ipcdetail::dynamic_cast_tag)
      :  m_pn( pointer(dynamic_cast<T*>(ipcdetail::to_raw_pointer(r.m_pn.to_raw_pointer())))
             , r.m_pn)
   {
      if(!m_pn.to_raw_pointer()){ // need to allocate new counter -- the cast failed
         m_pn = ipcdetail::shared_count<T, VoidAllocator, Deleter>();
      }
   }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //!Equivalent to shared_ptr(r).swap(*this).
   //!Never throws
   template<class Y>
   shared_ptr & operator=(shared_ptr<Y, VoidAllocator, Deleter> const & r)
   {
      m_pn = r.m_pn; // shared_count::op= doesn't throw
      return *this;
   }

   //!Equivalent to shared_ptr(r).swap(*this).
   //!Never throws
   shared_ptr & operator=(BOOST_COPY_ASSIGN_REF(shared_ptr) r)
   {
      m_pn = r.m_pn; // shared_count::op= doesn't throw
      return *this;
   }

   //!Move-assignment. Equivalent to shared_ptr(other).swap(*this).
   //!Never throws
   shared_ptr & operator=(BOOST_RV_REF(shared_ptr) other) // never throws
   {
      this_type(other).swap(*this);
      return *this;
   }

   //!This is equivalent to:
   //!this_type().swap(*this);
   void reset()
   {
      this_type().swap(*this);
   }

   //!This is equivalent to:
   //!this_type(p, a, d).swap(*this);
   template<class Pointer>
   void reset(const Pointer &p, const VoidAllocator &a = VoidAllocator(), const Deleter &d = Deleter())
   {
      //Check that the pointer passed is of the same type that
      //the pointer the allocator defines or it's a raw pointer
      typedef typename boost::intrusive::
         pointer_traits<Pointer>::template
            rebind_pointer<T>::type                         ParameterPointer;
      BOOST_STATIC_ASSERT((ipcdetail::is_same<pointer, ParameterPointer>::value) ||
                          (ipcdetail::is_pointer<Pointer>::value));
      this_type(p, a, d).swap(*this);
   }

   template<class Y>
   void reset(shared_ptr<Y, VoidAllocator, Deleter> const & r, const pointer &p)
   {
      this_type(r, p).swap(*this);
   }

   //!Returns a reference to the
   //!pointed type
   reference operator* () const // never throws
   {  BOOST_ASSERT(m_pn.to_raw_pointer() != 0);  return *m_pn.to_raw_pointer(); }

   //!Returns the pointer pointing
   //!to the owned object
   pointer operator-> () const // never throws
   {  BOOST_ASSERT(m_pn.to_raw_pointer() != 0);  return m_pn.to_raw_pointer();  }

   //!Returns the pointer pointing
   //!to the owned object
   pointer get() const  // never throws
   {  return m_pn.to_raw_pointer();  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   // implicit conversion to "bool"
   void unspecified_bool_type_func() const {}
   typedef void (this_type::*unspecified_bool_type)() const;

   operator unspecified_bool_type() const // never throws
   {  return !m_pn.to_raw_pointer() ? 0 : &this_type::unspecified_bool_type_func;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //!Not operator.
   //!Returns true if this->get() != 0, false otherwise
   bool operator! () const // never throws
   {  return !m_pn.to_raw_pointer();   }

   //!Returns use_count() == 1.
   //!unique() might be faster than use_count()
   bool unique() const // never throws
   {  return m_pn.unique();  }

   //!Returns the number of shared_ptr objects, *this included,
   //!that share ownership with *this, or an unspecified nonnegative
   //!value when *this is empty.
   //!use_count() is not necessarily efficient. Use only for
   //!debugging and testing purposes, not for production code.
   long use_count() const // never throws
   {  return m_pn.use_count();  }

   //!Exchanges the contents of the two
   //!smart pointers.
   void swap(shared_ptr<T, VoidAllocator, Deleter> & other) // never throws
   {  m_pn.swap(other.m_pn);   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   template<class T2, class A2, class Deleter2>
   bool _internal_less(shared_ptr<T2, A2, Deleter2> const & rhs) const
   {  return m_pn < rhs.m_pn;  }

   const_deleter_pointer get_deleter() const
   {  return m_pn.get_deleter(); }

//   const_allocator_pointer get_allocator() const
//   {  return m_pn.get_allocator(); }

   private:

   template<class T2, class A2, class Deleter2> friend class shared_ptr;
   template<class T2, class A2, class Deleter2> friend class weak_ptr;

   ipcdetail::shared_count<T, VoidAllocator, Deleter>   m_pn;    // reference counter
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};  // shared_ptr

template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator==(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a.get() == b.get(); }

template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator!=(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a.get() != b.get(); }

template<class T, class VoidAllocator, class Deleter, class U, class VoidAllocator2, class Deleter2> inline
bool operator<(shared_ptr<T, VoidAllocator, Deleter> const & a, shared_ptr<U, VoidAllocator2, Deleter2> const & b)
{  return a._internal_less(b);   }

template<class T, class VoidAllocator, class Deleter> inline
void swap(shared_ptr<T, VoidAllocator, Deleter> & a, shared_ptr<T, VoidAllocator, Deleter> & b)
{  a.swap(b);  }

template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> static_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::static_cast_tag());   }

template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> const_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::const_cast_tag()); }

template<class T, class VoidAllocator, class Deleter, class U> inline
shared_ptr<T, VoidAllocator, Deleter> dynamic_pointer_cast(shared_ptr<U, VoidAllocator, Deleter> const & r)
{  return shared_ptr<T, VoidAllocator, Deleter>(r, ipcdetail::dynamic_cast_tag());  }

// to_raw_pointer() enables boost::mem_fn to recognize shared_ptr
template<class T, class VoidAllocator, class Deleter> inline
T * to_raw_pointer(shared_ptr<T, VoidAllocator, Deleter> const & p)
{  return p.get();   }

// operator<<
template<class E, class T, class Y, class VoidAllocator, class Deleter> inline
std::basic_ostream<E, T> & operator<<
   (std::basic_ostream<E, T> & os, shared_ptr<Y, VoidAllocator, Deleter> const & p)
{  os << p.get();   return os;   }

//!Returns the type of a shared pointer
//!of type T with the allocator boost::interprocess::allocator allocator
//!and boost::interprocess::deleter deleter
//!that can be constructed in the given managed segment type.
template<class T, class ManagedMemory>
struct managed_shared_ptr
{
   typedef typename ManagedMemory::template allocator<void>::type void_allocator;
   typedef typename ManagedMemory::template deleter<T>::type      deleter;
   typedef shared_ptr< T, void_allocator, deleter>                type;
};

//!Returns an instance of a shared pointer constructed
//!with the default allocator and deleter from a pointer
//!of type T that has been allocated in the passed managed segment
template<class T, class ManagedMemory>
inline typename managed_shared_ptr<T, ManagedMemory>::type
   make_managed_shared_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_shared_ptr<T, ManagedMemory>::type
   ( constructed_object
   , managed_memory.template get_allocator<void>()
   , managed_memory.template get_deleter<T>()
   );
}

//!Returns an instance of a shared pointer constructed
//!with the default allocator and deleter from a pointer
//!of type T that has been allocated in the passed managed segment.
//!Does not throw, return null shared pointer in error.
template<class T, class ManagedMemory>
inline typename managed_shared_ptr<T, ManagedMemory>::type
   make_managed_shared_ptr(T *constructed_object, ManagedMemory &managed_memory, const std::nothrow_t &)
{
   try{
      return typename managed_shared_ptr<T, ManagedMemory>::type
      ( constructed_object
      , managed_memory.template get_allocator<void>()
      , managed_memory.template get_deleter<T>()
      );
   }
   catch(...){
      return typename managed_shared_ptr<T, ManagedMemory>::type();
   }
}


} // namespace interprocess

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#if defined(_MSC_VER) && (_MSC_VER < 1400)
// to_raw_pointer() enables boost::mem_fn to recognize shared_ptr
template<class T, class VoidAllocator, class Deleter> inline
T * to_raw_pointer(boost::interprocess::shared_ptr<T, VoidAllocator, Deleter> const & p)
{  return p.get();   }
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_SHARED_PTR_HPP_INCLUDED

/* shared_ptr.hpp
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
*/