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
  ,enable_shared_from_this<T, VoidAllocator, Deleter> const*pe
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
   typedef typename boost::container::
      allocator_traits<VoidAllocator>::pointer                 void_ptr;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<T>::type                               pointer;
   typedef typename ipcdetail::add_reference
                     <value_type>::type                        reference;
   typedef typename ipcdetail::add_reference
                     <const value_type>::type                  const_reference;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<const Deleter>::type                               const_deleter_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
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
   BOOST_TRY{
      return typename managed_shared_ptr<T, ManagedMemory>::type
      ( constructed_object
      , managed_memory.template get_allocator<void>()
      , managed_memory.template get_deleter<T>()
      );
   }
   BOOST_CATCH(...){
      return typename managed_shared_ptr<T, ManagedMemory>::type();
   } BOOST_CATCH_END
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