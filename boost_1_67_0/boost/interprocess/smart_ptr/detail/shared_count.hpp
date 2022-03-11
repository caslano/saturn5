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

#include <boost/checked_delete.hpp>
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
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<T>::type                         pointer;

   private:
   typedef sp_counted_impl_pd<VoidAllocator, Deleter>       counted_impl;

   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<counted_impl>::type                         counted_impl_ptr;
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<sp_counted_base>::type                       counted_base_ptr;

   typedef boost::container::allocator_traits<VoidAllocator>         vallocator_traits;

   typedef typename vallocator_traits::template
      portable_rebind_alloc<counted_impl>::type                      counted_impl_allocator;

   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<const Deleter>::type                         const_deleter_pointer;

   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
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
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<T>::type                         pointer;

   private:

   typedef sp_counted_impl_pd<VoidAllocator, Deleter>                counted_impl;

   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
         rebind_pointer<counted_impl>::type                          counted_impl_ptr;
   typedef typename boost::intrusive::
      pointer_traits<typename VoidAllocator::pointer>::template
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