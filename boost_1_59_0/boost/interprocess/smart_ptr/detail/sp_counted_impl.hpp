#ifndef BOOST_INTERPROCESS_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED
#define BOOST_INTERPROCESS_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

//
//  This file is the adaptation for shared memory memory mapped
//  files of boost/detail/sp_counted_impl.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//  Copyright 2006      Ion Gaztanaga
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/smart_ptr/detail/sp_counted_base.hpp>
#include <boost/interprocess/smart_ptr/scoped_ptr.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/intrusive/pointer_traits.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

//!A deleter for scoped_ptr that deallocates the memory
//!allocated for an object using a STL allocator.
template <class Allocator>
struct scoped_ptr_dealloc_functor
{
   typedef typename boost::container::
      allocator_traits<Allocator>::pointer pointer;

   typedef ipcdetail::integral_constant<unsigned,
      boost::interprocess::version<Allocator>::value>                   alloc_version;
   typedef ipcdetail::integral_constant<unsigned, 1>     allocator_v1;
   typedef ipcdetail::integral_constant<unsigned, 2>     allocator_v2;

   private:
   void priv_deallocate(const pointer &p, allocator_v1)
   {  m_alloc.deallocate(p, 1); }

   void priv_deallocate(const pointer &p, allocator_v2)
   {  m_alloc.deallocate_one(p); }

   public:
   Allocator& m_alloc;

   scoped_ptr_dealloc_functor(Allocator& a)
      : m_alloc(a) {}

   void operator()(pointer ptr)
   {  if (ptr) priv_deallocate(ptr, alloc_version());  }
};



template<class A, class D>
class sp_counted_impl_pd
   :  public sp_counted_base
   ,  boost::container::allocator_traits<A>::template
         portable_rebind_alloc< sp_counted_impl_pd<A, D> >::type
   ,  D  // copy constructor must not throw
{
   private:
   typedef sp_counted_impl_pd<A, D>          this_type;
   typedef typename boost::container::
      allocator_traits<A>::template
         portable_rebind_alloc
            < this_type >::type              this_allocator;
   typedef typename boost::container::
      allocator_traits<A>::template
         portable_rebind_alloc
            < const this_type >::type        const_this_allocator;
   typedef typename boost::container::
      allocator_traits<this_allocator>
         ::pointer                           this_pointer;
   typedef typename boost::container::
      allocator_traits<A>::pointer           a_pointer;
   typedef typename boost::intrusive::
      pointer_traits<this_pointer>           this_pointer_traits;

   sp_counted_impl_pd( sp_counted_impl_pd const & );
   sp_counted_impl_pd & operator= ( sp_counted_impl_pd const & );

   typedef typename boost::intrusive::
      pointer_traits<a_pointer>::template
         rebind_pointer<const D>::type                   const_deleter_pointer;
   typedef typename boost::intrusive::
      pointer_traits<a_pointer>::template
         rebind_pointer<const A>::type                   const_allocator_pointer;

   typedef typename D::pointer   pointer;
   pointer m_ptr;

   public:
   // pre: d(p) must not throw
   template<class Ptr>
   sp_counted_impl_pd(const Ptr & p, const A &a, const D &d )
      :  this_allocator(a), D(d), m_ptr(p)
   {}

   const_deleter_pointer get_deleter() const
   {  return const_deleter_pointer(&static_cast<const D&>(*this)); }

   const_allocator_pointer get_allocator() const
   {  return const_allocator_pointer(&static_cast<const A&>(*this)); }

   void dispose() // nothrow
   {  static_cast<D&>(*this)(m_ptr);   }

   void destroy() // nothrow
   {
      //Self destruction, so move the allocator
      this_allocator a_copy(::boost::move(static_cast<this_allocator&>(*this)));
      BOOST_ASSERT(a_copy == *this);
      this_pointer this_ptr(this_pointer_traits::pointer_to(*this));
      //Do it now!
      scoped_ptr< this_type, scoped_ptr_dealloc_functor<this_allocator> >
         deleter_ptr(this_ptr, a_copy);
      ipcdetail::to_raw_pointer(this_ptr)->~this_type();
   }

   void release() // nothrow
   {
      if(this->ref_release()){
         this->dispose();
         this->weak_release();
      }
   }

   void weak_release() // nothrow
   {
      if(sp_counted_base::weak_release()){
         this->destroy();
      }
   }
};


} // namespace ipcdetail

} // namespace interprocess

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED

/* sp_counted_impl.hpp
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
*/