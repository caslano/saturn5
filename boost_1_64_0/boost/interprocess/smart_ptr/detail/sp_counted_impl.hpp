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
fuHn8jX719OBP+TypcId4PJ9S/OVbwswCngv247+DnAAcCtwEfBB4NXAh4DFwG3AMuD9wGuAtcD1wO08f9jB56c8AKwB1gHvAe4E7uZwD3O8+zneJ4D1wGa+f4Tv6+d5H5LnHLQGOQ+hziZdo4Eu1mGme9A4f7NJ1xKErodD0p20Sddqk05rDk3ndvC6C68fNRAvaD5Cv+n8vp8NTAbmA1PZT3Nw4GDgF4G5wALgF4GFwGXAIuBythHuAc4DbgHOB34HuAC4w3CezpeAD7H/EfYf4HN2DgKv4nlkMfBNYAnwbWAp8CznI43P1ekNrARmAi8DfgG4DLgQuBxYAlwBXAVcBaxm+k1gWBk+WDbBNf7V3vkYW54MfUbG3iflORlNbc6LP4xnGcDjfz3/52Ycf/L8n50R2Xr+zs/Ibg19hsbpJ9t/jkZsE/LeZN9++dgm+2dq5DbJczVKcL24Nfj5Gp4mecbG5qbOnbNR39Rx2+aeVvOZGwebfOdubG5tv53zliZ5Bseppo6dw7G31XwWx7kme+dxuJ/6bJ7JcclToc/lKHrKfDZHxVPtO5+jWfAULvY98AJuAdxNcHVwh+FOwbn/hvzC5cOVwK2F2wxXD3cY7gTcObiMv4OXcGVwm+AOwJ2AizyDuM/8/535cd70/1csW9IV5/8LvavadHwveTVIV5SvrUbEVdWQ0cH97bjvKRT3q6pLV5WVri4rBkEV6fjHJWm6/ImbqznDB7S+U4ewWQ/T/lXhtNnFSyBvvHpphQjv25fcQft0y8u/ot634rAOoo2Ssl+KfStJK/f0sF+r1ptgWrmnV2NDL8y/pyfynEp5lvsFUVImi/cLeJ+P8mC2T7WIbdfN48jnwu1EnEU+Pi1C3V42RpjgKmY5Hf2sbbBNzScO68A9yAKiHrbCdUMYV/c4vYwz5T4O0ZyGiyea8ca9XEqvVt8/lTI9SymNTF3X/g7yd6M4OTwtfqRp8yn8HZNEZv1tScazkMIl2OY3nTVMZTfrAR5gRZVt/A1wH9wepNus4mNx6YplpdiDlG1jWVlxdWVAGQnmp5n+mtWVK1VtT9In8H6sRvmV+5NH6fk3tf74u4jjRbl85/YTKeJjubSIRwTtfPSjGF12ycX7X9vgBHZPsq+3Q+1Qlpfux8r7XC4zb+ewUucy5m0Ft1HvIwrecv0mGdsp3ZL7qLdTuKXaDKU8GceLf/3RNptw41SUr4xOd3SsK+Fz0THOvtC1i3alinYt2xq19wmgxVyf23sva3tnmreiuL13GxmkvUu5+t2UpwuFhrsuX7xP3CMpwAxdvzhUe7+HwiTYri9u78xDc720cL1kcsC+cMcQq/vRtvWyFO+NVWs8mo9HRQi3Fy5BlB/ts+0Z45k27FP6x6/DrIRzB++93g73qLAvYskDTC/y+PVuIrcLQ5soJPrrofczU9UmOD6HLuOgyX1afe99OdHMx7q3U997f57DSRlSpEsigjLtzUQzBt/IESQr8GeK3+OzUaHbCOCwfrk3DruOwibR3v4x8DQX/HiO9uvj46OiI13xiMu/b72Lz2hH/5XyiqLPGcbVxRRfd/b78+806VI+A8KDcM8mSruRkTb0osB3HjtJX4/KhrLinof2p++ltLB+xbovTew/2tNc51viWLrFB7Qn9QP8abXU+bXl1dY6V9Uvh3UE5Mu/6Xmigpf239XIg/LdsYF1yG+A6wZXBdcg5ip7FeUp5nwZ3wWGcWIchelD0uaKcnKccg6D3WrwSIa/UjyHLw7U3fS2Xk1xHTaeo0EyQ5I/N1G4FL3dTCR/hC+dFH63MO+PIB4xDmxFPR5AgXuIcaBHmVVWhGmOg8ZNsiJz/TQokdQ=
*/