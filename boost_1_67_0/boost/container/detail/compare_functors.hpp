///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP
#define BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/ebo_functor_holder.hpp>

namespace boost {
namespace container {

template<class ValueType>
class equal_to_value
{
   typedef ValueType value_type;
   const value_type &t_;

   public:
   explicit equal_to_value(const value_type &t)
      :  t_(t)
   {}

   bool operator()(const value_type &t)const
   {  return t_ == t;   }
};

template<class Node, class Pred, class Ret = bool>
struct value_to_node_compare
   :  Pred
{
   typedef Pred predicate_type;
   typedef Node node_type;

   value_to_node_compare()
      : Pred()
   {}

   explicit value_to_node_compare(Pred pred)
      :  Pred(pred)
   {}

   Ret operator()(const Node &a, const Node &b) const
   {  return static_cast<const Pred&>(*this)(a.get_data(), b.get_data());  }

   Ret operator()(const Node &a) const
   {  return static_cast<const Pred&>(*this)(a.get_data());  }

   Ret operator()(const Node &a, const Node &b)
   {  return static_cast<Pred&>(*this)(a.get_data(), b.get_data());  }

   Ret operator()(const Node &a)
   {  return static_cast<Pred&>(*this)(a.get_data());  }

   predicate_type &       predicate()        { return static_cast<predicate_type&>(*this); }
   const predicate_type & predicate()  const { return static_cast<predicate_type&>(*this); }
};

template<class KeyPred, class KeyOfValue, class Node, class Ret = bool>
struct key_node_pred
   :  public boost::intrusive::detail::ebo_functor_holder<KeyPred>
{
   BOOST_CONTAINER_FORCEINLINE explicit key_node_pred(const KeyPred &comp)
      :  base_t(comp)
   {}

   typedef boost::intrusive::detail::ebo_functor_holder<KeyPred> base_t;
   typedef KeyPred                     key_predicate;
   typedef KeyOfValue                  key_of_value;
   typedef typename KeyOfValue::type   key_type;


   BOOST_CONTAINER_FORCEINLINE static const key_type &key_from(const Node &n)
   {
      return key_of_value()(n.get_data());
   }

   template <class T>
   BOOST_CONTAINER_FORCEINLINE static const T &
      key_from(const T &t)
   {  return t;  }

   BOOST_CONTAINER_FORCEINLINE const key_predicate &key_pred() const
   {  return static_cast<const key_predicate &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE key_predicate &key_pred()
   {  return static_cast<key_predicate &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_pred()(key);  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE Ret operator()(const U &nonkey) const
   {  return this->key_pred()(this->key_from(nonkey));  }

   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_pred()(key1, key2);  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const U &nonkey2) const
   {  return this->key_pred()(key1, this->key_from(nonkey2));  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const key_type &key2) const
   {  return this->key_pred()(this->key_from(nonkey1), key2);  }

   template<class U, class V>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const V &nonkey2) const
   {  return this->key_pred()(this->key_from(nonkey1), this->key_from(nonkey2));  }
};


}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP

/* compare_functors.hpp
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
*/