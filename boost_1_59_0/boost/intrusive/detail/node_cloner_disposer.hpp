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
   BOOST_INTRUSIVE_FORCEINLINE node_ptr operator()(node_ptr p)
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

   BOOST_INTRUSIVE_FORCEINLINE void operator()(node_ptr p)
   {
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
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