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
5sXsy5NlyTCLkDsR7O0LkybTfSs/91YlFbBQsmBmo18cfQtTkwUxOyK9FQNLIavCTNewRAAsK1m4lpYccIYZhdyw3pZpsHyhXoh+7O8w6XDb3M4pQ1rBlGTOzDpsiZ0HU5P9wizz3OmHsDQyPrt3oaQ8LEfIrckOSYHlk7kwexy6+wKsiIyfUbVBiUdh0hG2z+UdZh49DAsl82V2bPIyD5iKzJVZrU2Pm8A0ZLze6wZtF8J0Qq5d/DwTTC/U8yxqqIJlkrkxm5GUXQmWI8xwdsWHh7A8IddmwJGdMDNZeWYeRYNDYZKRtn3OlNUdDZOSlWbmWPHEVphcyBXe7bEMpiCTMVs1Y19dmJqM91nzytihsDgyfrZ7E9oMgemE3Jdb2n9hejJ/ZsNaNLwByySrxKxamfUzYCayGsymtA6aD3MaZXvNP9ZffgqLICvDzKVcfCJMQ1aTWV+HqYdgBjInPrvHC1dYFlkQs42DXNvDTGR8XxwuOOhhFrIwfu4uvVrCZKNt670btbEfLJTMi9miChl/wpRkJdnrSvmZ563zqcik/J5hTM4BWByZK7P2Nc7Wg+nI+J6dveFyA5ZOJmMWqI+TwLLJHFkvD5uPPgEzCvVufCmYCMsjc2O2aZ1dIMxM5sMsJHdXF1iBMN/TKV/lMKcU2+usw/bmMbBQMn5Gx192DoBFkPky67lueRpMQ+bN7NrYUgUwHRmfr3UPjzYwPZkzt83vvsDSyTx5vYEzOsOyyPi5b5PGL4flkrkzuzi+61yYiYzvi6TVrjBYvpjLjL8LKyLjZ+v2sFR7mGyMvaQcs8UnulyGRZB58X0JeO4FU5PxXo5WaHEMphXWnKAauBmWRsb3s3flMiqYgcyN2THfxlpYFhk/96/mM81heWT8bEvu2vcElk/mx2zYo8+nYE5jbfdsq3P9cJiMjPcZ1ta5LSyUrCyz0rOXz4CpyPheL68ecximJeN7NjFp+xGYnozv9YB1PdfBDGR8hnF/VB0LM5Lx2Ze9+rIAZiZzZqbMPe0Kyxf6jH3wdjHMaZzttbt2QHMHmJzMh+9Z29DusAgyD2a7/nI7B1OTBTBzH+KfBUshC2LWw6VnV9gKMv7c4xie6wlbT1aK2QPvww1hOWT8dTN4R519sFwyN2ZpY4/LYSZhzUQv55YwMxl/Lv/33S17WL6w5uUhbRJhRcJ8GWGlRsDk422viWBFqUhYBBmfIaRwhAtMRebObEHIwP0wDRk/v97rXoXBdGT83GeMcPeCpZOVYXbF1O0sLIfMn1nQPOVdmIlMzuzexgV/worIfJnpwt7fh8km2F4vh2aNHABTkPkwa3q5WjhMRcbrTa95tzRMJ+SO/FF5CyyNjO9ZuXfHfGEGMi9mCX3GSmE5ZMHMBjbufw5mJuPn3so5PwuWT8bP4fOK04dhkonC82fdV2VhMjI/vi9FLX9eE2R8vmbPL3SDqcmcmUW9nDwPFifkbta41ASWQsZnn1XRbxAsncyJ2Yffx3jCMoU1mxx6XA5mFOarNnrdOZiJLIDZi4q35sOKyMoyM5t+8YD5/G57T6Q4VE4Kk5Pxa6L8/TNpMBUZP/eraRczYBoyV2b7EvsnwrRk/LnnY6VTN2E6Yc2pwdkBML2Qm2ZaWQOWJtR7WFAqH2YQcp3Lj/4fLJOM36NE6wb0gBmF3K52TVxhuUKfHb52UsBMQq7/4ZtnYWahz1+kRSdh+ULO+e3zNrACoZ5MqzgKk+htc3ft7abAnMh4vQnTl0XDZGT83MfWOVAVJifj+3Jsdq9zsAghl/nWMRmm1Av3S6YXj2BqstLMZh77VAiLE/rc2qxNGZhOsHajIt/C9EK9pZFzk2Dpwr60WdA=
*/