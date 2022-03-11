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