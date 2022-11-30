//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP
#define BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/pointer_traits.hpp>

namespace boost{
namespace intrusive{

//Needed to support smart references to value types
template <class From, class ValuePtr>
struct disable_if_smartref_to
   : detail::disable_if_c 
      <  detail::is_same
            <From, typename pointer_traits
               <ValuePtr>
                  ::reference>::value
      || detail::is_same
            <From, typename pointer_traits
                     < typename pointer_rebind
                           < ValuePtr
                           , const typename boost::movelib::pointer_element<ValuePtr>::type>::type>
                  ::reference>::value
      >
{};

//This function object takes a KeyCompare function object
//and compares values that contains keys using KeyOfValue
template< class ValuePtr, class KeyCompare, class KeyOfValue, class Ret = bool
        , bool = boost::intrusive::detail::is_same
   <typename boost::movelib::pointer_element<ValuePtr>::type, typename KeyOfValue::type>::value >
struct tree_value_compare
   :  public boost::intrusive::detail::ebo_functor_holder<KeyCompare>
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef KeyCompare                                 key_compare;
   typedef KeyOfValue                                 key_of_value;
   typedef typename KeyOfValue::type                  key_type;

   typedef boost::intrusive::detail::ebo_functor_holder<KeyCompare> base_t;

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare()
      :  base_t()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_value_compare(const key_compare &kcomp)
      :  base_t(kcomp)
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare (const tree_value_compare &x)
      :  base_t(x.base_t::get())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const tree_value_compare &x)
   {  this->base_t::get() = x.base_t::get();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const key_compare &x)
   {  this->base_t::get() = x;   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_comp()(key);   }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value) const
   {  return this->key_comp()(KeyOfValue()(value));  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey
                                             , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_comp()(key1, key2);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value1, const value_type &value2) const
   {  return this->key_comp()(KeyOfValue()(value1), KeyOfValue()(value2));  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const value_type &value2) const
   {  return this->key_comp()(key1, KeyOfValue()(value2));  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const value_type &value1, const key_type &key2) const
   {  return this->key_comp()(KeyOfValue()(value1), key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const key_type &key1, const U &nonkey2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(key1, nonkey2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey1, const key_type &key2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey1, key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const value_type &value1, const U &nonvalue2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(KeyOfValue()(value1), nonvalue2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonvalue1, const value_type &value2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonvalue1, KeyOfValue()(value2));  }
};

template<class ValuePtr, class KeyCompare, class KeyOfValue, class Ret>
struct tree_value_compare<ValuePtr, KeyCompare, KeyOfValue, Ret, true>
   :  public boost::intrusive::detail::ebo_functor_holder<KeyCompare>
{
   typedef typename
      boost::movelib::pointer_element<ValuePtr>::type value_type;
   typedef KeyCompare                                 key_compare;
   typedef KeyOfValue                                 key_of_value;
   typedef typename KeyOfValue::type                  key_type;

   typedef boost::intrusive::detail::ebo_functor_holder<KeyCompare> base_t;


   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare()
      :  base_t()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit tree_value_compare(const key_compare &kcomp)
      :  base_t(kcomp)
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare (const tree_value_compare &x)
      :  base_t(x.base_t::get())
   {}

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const tree_value_compare &x)
   {  this->base_t::get() = x.base_t::get();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE tree_value_compare &operator=(const key_compare &x)
   {  this->base_t::get() = x;   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE const key_compare &key_comp() const
   {  return static_cast<const key_compare &>(*this);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_comp()(key);   }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const U &nonkey
                                             , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey);  }

   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_comp()(key1, key2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()( const key_type &key1, const U &nonkey2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(key1, nonkey2);  }

   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE Ret operator()(const U &nonkey1, const key_type &key2
                                              , typename disable_if_smartref_to<U, ValuePtr>::type* = 0) const
   {  return this->key_comp()(nonkey1, key2);  }
};

}  //namespace intrusive{
}  //namespace boost{

#endif   //#ifdef BOOST_INTRUSIVE_DETAIL_TREE_VALUE_COMPARE_HPP

/* tree_value_compare.hpp
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
*/