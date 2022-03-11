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

#ifndef BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP
#define BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/tree_value_compare.hpp>


namespace boost {
namespace intrusive {
namespace detail {

template < class KeyTypeKeyCompare
         , class ValueTraits
         , class KeyOfValue
         >
struct key_nodeptr_comp_types
{
   typedef ValueTraits                                   value_traits;
   typedef typename value_traits::value_type             value_type;
   typedef typename value_traits::node_ptr               node_ptr;
   typedef typename value_traits::const_node_ptr         const_node_ptr;
   typedef typename detail::if_c
            < detail::is_same<KeyOfValue, void>::value
            , detail::identity<value_type>
            , KeyOfValue
            >::type                                      key_of_value;
   typedef tree_value_compare
      <typename ValueTraits::pointer, KeyTypeKeyCompare, key_of_value>      base_t;
};

//This function object transforms a key comparison type to
//a function that can compare nodes or nodes with nodes or keys.
template < class KeyTypeKeyCompare
         , class ValueTraits
         , class KeyOfValue = void
         >
struct key_nodeptr_comp
   //Use public inheritance to avoid MSVC bugs with closures
   :  public key_nodeptr_comp_types<KeyTypeKeyCompare, ValueTraits, KeyOfValue>::base_t
{
private:
   struct sfinae_type;

public:
   typedef key_nodeptr_comp_types<KeyTypeKeyCompare, ValueTraits, KeyOfValue> types_t;
   typedef typename types_t::value_traits          value_traits;
   typedef typename types_t::value_type            value_type;
   typedef typename types_t::node_ptr              node_ptr;
   typedef typename types_t::const_node_ptr        const_node_ptr;
   typedef typename types_t::base_t                base_t;
   typedef typename types_t::key_of_value          key_of_value;

   template <class P1>
   struct is_same_or_nodeptr_convertible
   {
      static const bool same_type = is_same<P1,const_node_ptr>::value || is_same<P1,node_ptr>::value;
      static const bool value = same_type || is_convertible<P1, const_node_ptr>::value;
   };

   BOOST_INTRUSIVE_FORCEINLINE base_t base() const
   {  return static_cast<const base_t&>(*this); }

   BOOST_INTRUSIVE_FORCEINLINE key_nodeptr_comp(KeyTypeKeyCompare kcomp, const ValueTraits *traits)
      :  base_t(kcomp), traits_(traits)
   {}

   //pred(pnode)
   template<class T1>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T1 &t1, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value, sfinae_type* >::type = 0) const
   {  return base().get()(key_of_value()(*traits_->to_value_ptr(t1)));  }

   //operator() 2 arg
   //pred(pnode, pnode)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value && is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(*traits_->to_value_ptr(t1), *traits_->to_value_ptr(t2));  }

   //pred(pnode, key)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value && !is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(*traits_->to_value_ptr(t1), t2);  }

   //pred(key, pnode)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< !is_same_or_nodeptr_convertible<T1>::value && is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(t1, *traits_->to_value_ptr(t2));  }

   //pred(key, key)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< !is_same_or_nodeptr_convertible<T1>::value && !is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(t1, t2);  }

   const ValueTraits *const traits_;
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP

/* key_nodeptr_comp.hpp
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
*/