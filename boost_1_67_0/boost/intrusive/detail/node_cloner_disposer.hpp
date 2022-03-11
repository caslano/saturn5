/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/detail/assert.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class F, class ValueTraits, algo_types AlgoType, bool IsConst = true>
struct node_cloner
   //Use public inheritance to avoid MSVC bugs with closures
   :  public ebo_functor_holder<F>
{
   typedef ValueTraits                                      value_traits;
   typedef typename value_traits::node_traits               node_traits;
   typedef typename node_traits::node_ptr                   node_ptr;
   typedef ebo_functor_holder<F>                            base_t;
   typedef typename get_algo< AlgoType
                            , node_traits>::type            node_algorithms;
   static const bool safemode_or_autounlink =
      is_safe_autounlink<value_traits::link_mode>::value;
   typedef typename value_traits::value_type                value_type;
   typedef typename value_traits::pointer                   pointer;
   typedef typename value_traits::const_pointer             const_pointer;
   typedef typename node_traits::node                       node;
   typedef typename value_traits::const_node_ptr            const_node_ptr;
   typedef typename pointer_traits<pointer>::reference      reference;
   typedef typename pointer_traits
      <const_pointer>::reference                            const_reference;
   typedef typename if_c<IsConst, const_reference, reference>::type reference_type;

   node_cloner(F f, const ValueTraits *traits)
      :  base_t(f), traits_(traits)
   {}

   // tree-based containers use this method, which is proxy-reference friendly
   BOOST_INTRUSIVE_FORCEINLINE node_ptr operator()(const node_ptr & p)
   {
      reference_type v = *traits_->to_value_ptr(p);
      node_ptr n = traits_->to_node_ptr(*base_t::get()(v));
      //Cloned node must be in default mode if the linking mode requires it
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::unique(n));
      return n;
   }

   const ValueTraits * const traits_;
};

template<class F, class ValueTraits, algo_types AlgoType>
struct node_disposer
   //Use public inheritance to avoid MSVC bugs with closures
   :  public ebo_functor_holder<F>
{
   typedef ValueTraits                          value_traits;
   typedef typename value_traits::node_traits   node_traits;
   typedef typename node_traits::node_ptr       node_ptr;
   typedef ebo_functor_holder<F>                base_t;
   typedef typename get_algo< AlgoType
                            , node_traits>::type   node_algorithms;
   static const bool safemode_or_autounlink =
      is_safe_autounlink<value_traits::link_mode>::value;

   node_disposer(F f, const ValueTraits *cont)
      :  base_t(f), traits_(cont)
   {}

   BOOST_INTRUSIVE_FORCEINLINE void operator()(const node_ptr & p)
   {
      if(safemode_or_autounlink)
         node_algorithms::init(p);
      base_t::get()(traits_->to_value_ptr(p));
   }
   const ValueTraits * const traits_;
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_CLONER_DISPOSER_HPP

/* node_cloner_disposer.hpp
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
*/