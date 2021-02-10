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
ATYw0Ag0Ao0rrNM0B3dznkAJW3VbbNVcupvHR9Hm7mbYugA6gL4mRgrWLsKjEB6FV2N+8pNivBqDaKuXQ0vEW4GdYOezsjMzgvPJ0YfFXAG+gO8uwxeABWABWLyTSvC+DiC2qxDDI1QADoCDBfncD1EfbEHiy0aA787CF4G9iFdCvBLerXnSN2KTgSDeaBsQjHijrUAwoAvoArp4uQYv14CNYCOZee8UbMwFGwFDwBAwBAwBw42+Qo9Q2/w+KMWTUYT+IPTnsUTD08etJBoYBoaBYWAYGAaG7QDD8Ll5uC/hvoT7Eu7LrQYl3JdbEeeC/zyWVz4i9OXn4/LH/usY0Al0Ap3bis4pPylICc8oPKPwjIJa8IzuALVg8OXa4IOFB4corLqt5SOsum3l46TIrJ8DloAlYAlYApaAZZ5hORsqClzCRQoXKVykcJHCRbqrVFsVEwOm5c8ERIDMI+nmqzF77PuqL7JNf7QNpiJMRZiKLw+qMBUfh9WXZSrio+LPyFaYlDmjH0zKJ6DfXIlQRR16Q7ncrVTnSrNZfRTrvmRKAmrCS1svcEFX0EuUVKgWJU+Sg7Nj9D/3jX7TtBr2pCgrUMNLmizs/owSl/K13Z/Nd3+2WfeZgq65QWfhaHUykc8nLxgQL5HcOH1S
*/