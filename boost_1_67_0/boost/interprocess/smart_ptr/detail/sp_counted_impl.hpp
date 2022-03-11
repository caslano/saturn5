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
   typedef typename Allocator::pointer pointer;
   typedef ipcdetail::integral_constant<unsigned,
      boost::interprocess::version<Allocator>::value>                   alloc_version;
   typedef ipcdetail::integral_constant<unsigned, 1>     allocator_v1;
   typedef ipcdetail::integral_constant<unsigned, 2>     allocator_v2;

   private:
   void priv_deallocate(const typename Allocator::pointer &p, allocator_v1)
   {  m_alloc.deallocate(p, 1); }

   void priv_deallocate(const typename Allocator::pointer &p, allocator_v2)
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
   typedef typename this_allocator::pointer  this_pointer;
   typedef typename boost::intrusive::
      pointer_traits<this_pointer>           this_pointer_traits;

   sp_counted_impl_pd( sp_counted_impl_pd const & );
   sp_counted_impl_pd & operator= ( sp_counted_impl_pd const & );

   typedef typename boost::intrusive::
      pointer_traits<typename A::pointer>::template
         rebind_pointer<const D>::type                   const_deleter_pointer;
   typedef typename boost::intrusive::
      pointer_traits<typename A::pointer>::template
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
      typedef typename this_allocator::value_type value_type;
      ipcdetail::to_raw_pointer(this_ptr)->~value_type();
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