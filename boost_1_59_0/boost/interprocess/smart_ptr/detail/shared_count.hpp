//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/detail/shared_count.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Peter Dimov 2004-2005
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_DETAIL_SHARED_COUNT_HPP_INCLUDED
#define BOOST_INTERPROCESS_DETAIL_SHARED_COUNT_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/interprocess/smart_ptr/detail/bad_weak_ptr.hpp>
#include <boost/interprocess/smart_ptr/detail/sp_counted_impl.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less
#include <boost/container/detail/placement_new.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail{

template<class T, class VoidAllocator, class Deleter>
class weak_count;

template<class T, class VoidAllocator, class Deleter>
class shared_count
{
   public:

   typedef typename boost::container::
      allocator_traits<VoidAllocator>::pointer              void_ptr;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<T>::type                            pointer;

   private:
   typedef sp_counted_impl_pd<VoidAllocator, Deleter>       counted_impl;

   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<counted_impl>::type                         counted_impl_ptr;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<sp_counted_base>::type                       counted_base_ptr;

   typedef boost::container::allocator_traits<VoidAllocator>         vallocator_traits;

   typedef typename vallocator_traits::template
      portable_rebind_alloc<counted_impl>::type                      counted_impl_allocator;

   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<const Deleter>::type                         const_deleter_pointer;

   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<const VoidAllocator>::type                   const_allocator_pointer;

   pointer           m_px;
   counted_impl_ptr  m_pi;

   template <class T2, class VoidAllocator2, class Deleter2>
   friend class weak_count;

   template <class T2, class VoidAllocator2, class Deleter2>
   friend class shared_count;

   public:

   shared_count()
      :  m_px(0), m_pi(0) // nothrow
   {}

   template <class Ptr>
   shared_count(const shared_count &other_shared_count, const Ptr &p)
      :  m_px(p), m_pi(other_shared_count.m_pi)
   {}

   template <class Ptr>
   shared_count(const Ptr &p, const VoidAllocator &a, Deleter d)
      :  m_px(p), m_pi(0)
   {
      BOOST_TRY{
         if(p){
            counted_impl_allocator alloc(a);
            m_pi = alloc.allocate(1);
            //Anti-exception deallocator
            scoped_ptr<counted_impl,
                     scoped_ptr_dealloc_functor<counted_impl_allocator> >
                        deallocator(m_pi, alloc);
            //It's more correct to use VoidAllocator::construct but
            //this needs copy constructor and we don't like it
            ::new(ipcdetail::to_raw_pointer(m_pi), boost_container_new_t())counted_impl(p, a, d);
            deallocator.release();
         }
      }
      BOOST_CATCH (...){
         d(p); // delete p
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   ~shared_count() // nothrow
   {
      if(m_pi)
         m_pi->release();
   }

   shared_count(shared_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   { if( m_pi != 0 ) m_pi->add_ref_copy(); }

   //this is a test
   template<class Y>
   explicit shared_count(shared_count<Y, VoidAllocator, Deleter> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if( m_pi != 0 ) m_pi->add_ref_copy();  }

   //this is a test
   template<class Y>
   explicit shared_count(const pointer & ptr, shared_count<Y, VoidAllocator, Deleter> const & r)
      :  m_px(ptr), m_pi(r.m_pi) // nothrow
   {  if( m_pi != 0 ) m_pi->add_ref_copy();  }

/*
   explicit shared_count(weak_count<Y, VoidAllocator, Deleter> const & r)
      // throws bad_weak_ptr when r.use_count() == 0
      : m_pi( r.m_pi )
   {
      if( m_pi == 0 || !m_pi->add_ref_lock() ){
         boost::throw_exception( boost::interprocess::bad_weak_ptr() );
      }
   }
*/
   template<class Y>
   explicit shared_count(weak_count<Y, VoidAllocator, Deleter> const & r)
      // throws bad_weak_ptr when r.use_count() == 0
      : m_px(r.m_px), m_pi( r.m_pi )
   {
      if( m_pi == 0 || !m_pi->add_ref_lock() ){
         throw( boost::interprocess::bad_weak_ptr() );
      }
   }

   const pointer &to_raw_pointer() const
   {  return m_px;   }

   pointer &to_raw_pointer()
   {  return m_px;   }

   shared_count & operator= (shared_count const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release();
         m_pi = tmp;
      }
      return *this;
   }

   template<class Y>
   shared_count & operator= (shared_count<Y, VoidAllocator, Deleter> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if( tmp != m_pi ){
         if(tmp != 0)   tmp->add_ref_copy();
         if(m_pi != 0)  m_pi->release();
         m_pi = tmp;
      }
      return *this;
   }

   void swap(shared_count & r) // nothrow
   {  ::boost::adl_move_swap(m_px, r.m_px);  ::boost::adl_move_swap(m_pi, r.m_pi);   }

   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count(): 0;  }

   bool unique() const // nothrow
   {  return use_count() == 1;   }

   const_deleter_pointer get_deleter() const
   {  return m_pi ? m_pi->get_deleter() : 0; }

//   const_allocator_pointer get_allocator() const
//   {  return m_pi ? m_pi->get_allocator() : 0; }

   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_equal (shared_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return this->m_pi == other.m_pi;   }

   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_less  (shared_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return std::less<counted_base_ptr>()(this->m_pi, other.m_pi);  }
};

template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator==(shared_count<T, VoidAllocator, Deleter> const & a, shared_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_equal(b);  }

template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator<(shared_count<T, VoidAllocator, Deleter> const & a, shared_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_less(b);   }


template<class T, class VoidAllocator, class Deleter>
class weak_count
{
   public:
   typedef typename boost::container::
      allocator_traits<VoidAllocator>::pointer           void_ptr;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<T>::type                         pointer;

   private:

   typedef sp_counted_impl_pd<VoidAllocator, Deleter>                counted_impl;

   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<counted_impl>::type                          counted_impl_ptr;
   typedef typename boost::intrusive::
      pointer_traits<void_ptr>::template
         rebind_pointer<sp_counted_base>::type                       counted_base_ptr;

   pointer           m_px;
   counted_impl_ptr  m_pi;

   template <class T2, class VoidAllocator2, class Deleter2>
   friend class weak_count;

   template <class T2, class VoidAllocator2, class Deleter2>
   friend class shared_count;

   public:

   weak_count(): m_px(0), m_pi(0) // nothrow
   {}

   template <class Y>
   explicit weak_count(shared_count<Y, VoidAllocator, Deleter> const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   weak_count(weak_count const & r)
      :  m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   template<class Y>
   weak_count(weak_count<Y, VoidAllocator, Deleter> const & r)
      : m_px(r.m_px), m_pi(r.m_pi) // nothrow
   {  if(m_pi != 0) m_pi->weak_add_ref(); }

   ~weak_count() // nothrow
   {  if(m_pi != 0) m_pi->weak_release(); }

   template<class Y>
   weak_count & operator= (shared_count<Y, VoidAllocator, Deleter> const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0)   tmp->weak_add_ref();
      if(m_pi != 0)  m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   weak_count & operator= (weak_count const & r) // nothrow
   {
      m_px = r.m_px;
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   void set_pointer(const pointer &ptr)
   {  m_px = ptr; }

   template<class Y>
   weak_count & operator= (weak_count<Y, VoidAllocator, Deleter> const& r) // nothrow
   {
      counted_impl_ptr tmp = r.m_pi;
      if(tmp != 0) tmp->weak_add_ref();
      if(m_pi != 0) m_pi->weak_release();
      m_pi = tmp;
      return *this;
   }

   void swap(weak_count & r) // nothrow
   {  ::boost::adl_move_swap(m_px, r.m_px);  ::boost::adl_move_swap(m_pi, r.m_pi);   }

   long use_count() const // nothrow
   {  return m_pi != 0? m_pi->use_count() : 0;   }

   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_equal (weak_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return this->m_pi == other.m_pi;   }

   template<class T2, class VoidAllocator2, class Deleter2>
   bool internal_less (weak_count<T2, VoidAllocator2, Deleter2> const & other) const
   {  return std::less<counted_base_ptr>()(this->m_pi, other.m_pi);  }
};

template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator==(weak_count<T, VoidAllocator, Deleter> const & a, weak_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_equal(b);  }

template<class T, class VoidAllocator, class Deleter, class T2, class VoidAllocator2, class Deleter2> inline
bool operator<(weak_count<T, VoidAllocator, Deleter> const & a, weak_count<T2, VoidAllocator2, Deleter2> const & b)
{  return a.internal_less(b);   }

} // namespace ipcdetail
} // namespace interprocess
} // namespace boost


#include <boost/interprocess/detail/config_end.hpp>


#endif  // #ifndef BOOST_INTERPROCESS_DETAIL_SHARED_COUNT_HPP_INCLUDED

/* shared_count.hpp
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
*/