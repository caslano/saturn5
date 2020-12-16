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
dHY1kM5pms4Zms6Zmk6WpjNS0zlL0xmv6YyVdPBrOl8568fpm/V6OAF3QNOJ1nRiYTKMg71gPOwLE/Q8toaDYTtNLwlOg+3hOTAZzoYpcA48DhbBjnAZPF77pxPg92EnuBJ2gathhl5PXfV66gafhX3hS2qf/w3YH34MM/X6GQBj4EAYC3tBHH6tZ2c9ML9d6vm32o/8Dsbpvhqd4C7YRffVGA5fgaepnfkR8I8wT/2ajq73ZFzHJZ33NJ0PNZ2PNJ0Dms7Hms4nqp8+Qs7nZ3Cu+I37g6YzwuX+ME73bRgPY+EEmAonwgw4CfaGk7U8U1Qv8rqWEKpe087+L6O0n4ex8EUYD38NE+B22Fb8dv+NU30xLv33s6rvOdgKPq/xyp01dfx26ffW6P3vhzAWrtXr4Qa9D66DPeCNen3cBKfDW+A5evxc9ZepX8uva9Fo0y7l36n5fUnLu0vLuxsmwldgkviNfVJUX5KLvtdU3x6tx72wNdwH28DXYTv1a32ytit8fV6j1/G1sBW8zmv0hxov2aU/PEHz0UnP64mwPeyi6fbEZWn8OI0fZcXT+Ekav72Rz+wG8rlF5Z/S8/60ES9f47UKiQc1XnfYEvYw6rncLp9LPR/QeB/reTuo5+2QnrfPpLz4DX1rG9D3pup7S/W9o/o+UH3vqT789c9dDZTrCdW3Wcv1MyMftRqvrUs+7tF498IYeJ+2owc0X/dLO8Jv6KtrQN/Nqu/Hqu8W1Xer6lsn+vAb+jzzw+u7WvWtUn3XqL7rVN+1og+/oS+9AX0bVd8jqu9R1bdJ9T0m+vAb+rIa0Lde9d2h+u5UfTWq7yeiD7+hL78BfWtU3w9V31rV9yPVd4Pqw+/049WqL9WlHy9XfRervsXaziq0X1iq/c0SmKJ+W29NA3rPV70XqN481ZuvegtV71zVW2jorW1A7wTVO1H1TlK9k1VvtuqdqnqzDb11Dei9XPVeoXqrVe8K1btS9V4pevEbej0l4fXOU73zVW+J6r1I9S5UvaWiF7+hN70BvTmq9xzVe67qnal6Z6veWaoXf/37juqNd+knkBW9qfr80MF438nWeA97Qt93OurzwPEwGXaCafBE3SenM8yEg+AAmKHPIV31+aMbnAq76/NODzhX5QthL7gA9oaXwz6wGvaDN8L+8B6YCe/XeA/AgfAh8et9yqtzXXUubZWWvY/u4/Sgl1MPH9X3t8f0fr8JngQfh33gZjgE/gyOgltgDnwaLlH/VXAbXAO3wzvgb+Dd8Lf6/LkTPgCfgxvh87oPVC18HL4In4Q74FO6P9gu3R/sNbhb3vMI1+fTd+Hx8AN4IjwA0+GfYXe4F/aEb8DecA8coHKnwI/hRPgJPA8ehPnwU6/xnr5A79Mu7aeDtss0vc8fZ9zfPaXh7++tNV4b8zmkNHw77aXyvWEc7GOnQ4R0jfd7Pb8ZuBP0/H6JXDr8St9b/w5Ph4fhLNgtmvLC7rAY9oAXwV5wIewNq+HJcC3sD2s0/EE4HG6BmXA7HAZ3aPhrsA/cr+HvafgXMBrGkccWsAuMgT1gHDwTxsO5sDUsgVa8KtgWXgHbwetgMrwepsGb4HFwI+wIH4Wd4NMaX/d/07lp1JvWs7n/2zS9rqfDeDgDtoc5sAM8Bx4PZ8ET/Pq4bvAb7ys1qr/I5X3lFNU/VPUP0/eV4foecZr2FyNgFjwdToejtF8YremQgM75oY70vFt6Dmk6N2k6t+r7ym36PvQU7A6fhifB22F/uB6O0+OT9PhkeCfMhz+Bi2AN/IGGr4b3wcfgBvgEpE1IO3gS/k71var6/ggfgm/Ah2Ed3Ajfho/AT+Hj8HP4BPxG47fw+uO3gpY=
*/