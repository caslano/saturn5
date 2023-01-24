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
c5foBsOR82hpErh97pyqSet0rsv3wNlwDXRKPy+2wX4DHdJ/Bk688hQgj4HLe6UKu6exyDmzLFzeSL4HEEcBAt290rBq3d3H1Y8ngC7pTjTn9B/b3UDHXZ7RDckjgDxRd2EWI1WCMlJ0A2cDt/3k3NvuCkQk3FPTUoV3cPvvuoG7PD9gj0GXwOWFWV6cAcQzyX1/Gj9gzwjLpw4LxhGPMg77WVy8HgeQh8vjsqnULKKq2J9GIHe8OkQk8QRLY3FbaOTmbCCc5kcQEn688tQM5Ip3YusIgx8Hz8cF5Elypjiev2SWGwj/PwfI0ycLX7/xnwWy6kSgbr/H/cYv93Pf9ynf9ynf9ynf9ylf7lPc8fZkN/XHWSN0qFWbbsDW2c1Je6ViE+eMtwDyVNqAJSyfitd5bLHJNoBpwEqVkJCX3+9kIG8kYiTCZGOrTZkFYhEzjZhOHANhQNfZT+HtONsaYhSIxcR2OM1LIhXbeicDHQ6dxZLA2yV5Ok6zGMIknUpZGScdP0L3SuNYLFwhRUdUfU4GTgYcPB4e2F54PIR64/F4dB4eD01ipKJJEhI4CuHWOXFwd5k4CuPJRcP1sfDnVBzd8WQ3YOtjegRiZOIoEoHozG/F4x00vHdsv6VH665bjq27zO1bd5jatW4zetK6mW7Zul7LolXuilmr7CWj1lXq+q3LT2q1LlO73LpE+VzrIsUzrQsPnGidv/Pw
*/