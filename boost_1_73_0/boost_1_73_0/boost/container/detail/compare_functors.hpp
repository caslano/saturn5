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
iEIrJlgAAi1njdLSwG7Y+eB86CwjEuw0QS7pvXPgFjaNTs/aYH6dwKWS9xrLOVaVqr2LC+c7G2zy9VZROZY05w0W3lqVwROnyNLRq4NVGWv9EWjoNSYqaFuTnG5oo/oUBFUoeG2w4YJaEi8Wpk9xRQQzva22rRY3nj+eR2k0iWaJ+fL/9M7jmW+5TWn1pJrS//YV56xhaoTksXKkFw/gXwu+2pZUoRrMVl+JKE4zHBywd7cJvSGaCxcpsTEQuo8PIaYCqer7V9B/OioVHI5xD7viDn7bG/bgxhsz+QGt+kxgVzFTkfdm5X6InWz2ST4ql593OtEx7oEAtAJVUo7s6V0J/OQelftqrlaNjTdNPQT5Yun3i+WWzNDtffaCmfcxmAXp0vKKotcCNpp7bPbnfrqYh/DZmy18az4UVefrZ9EZpmTY6ptP60F2bcsF3kb9DdkbLsKzEI+URUbj2qnhqq+9nfg+eLMkwsb9OH9IENioNSzcg/LuNozbPf4WsWn0xy2Cv/zBIEv/N/kPUEsDBAoAAAAIAC1nSlKWoVkv4wMAAJkIAAA5AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fU1BFRURfRE9XTkxPQURfVC4zVVQFAAG2SCRg
*/