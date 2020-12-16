/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_RND_NODE_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_RND_NODE_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/operators.hpp>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Iterator class for node-based indices with random access iterators. */

template<typename Node>
class rnd_node_iterator:
  public random_access_iterator_helper<
    rnd_node_iterator<Node>,
    typename Node::value_type,
    typename Node::difference_type,
    const typename Node::value_type*,
    const typename Node::value_type&>
{
public:
  /* coverity[uninit_ctor]: suppress warning */
  rnd_node_iterator(){}
  explicit rnd_node_iterator(Node* node_):node(node_){}

  const typename Node::value_type& operator*()const
  {
    return node->value();
  }

  rnd_node_iterator& operator++()
  {
    Node::increment(node);
    return *this;
  }

  rnd_node_iterator& operator--()
  {
    Node::decrement(node);
    return *this;
  }

  rnd_node_iterator& operator+=(typename Node::difference_type n)
  {
    Node::advance(node,n);
    return *this;
  }

  rnd_node_iterator& operator-=(typename Node::difference_type n)
  {
    Node::advance(node,-n);
    return *this;
  }

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
  /* Serialization. As for why the following is public,
   * see explanation in safe_mode_iterator notes in safe_mode.hpp.
   */

  BOOST_SERIALIZATION_SPLIT_MEMBER()

  typedef typename Node::base_type node_base_type;

  template<class Archive>
  void save(Archive& ar,const unsigned int)const
  {
    node_base_type* bnode=node;
    ar<<serialization::make_nvp("pointer",bnode);
  }

  template<class Archive>
  void load(Archive& ar,const unsigned int)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
  }
#endif

  /* get_node is not to be used by the user */

  typedef Node node_type;

  Node* get_node()const{return node;}

private:
  Node* node;
};

template<typename Node>
bool operator==(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return x.get_node()==y.get_node();
}

template<typename Node>
bool operator<(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(x.get_node(),y.get_node())>0;
}

template<typename Node>
typename Node::difference_type operator-(
  const rnd_node_iterator<Node>& x,
  const rnd_node_iterator<Node>& y)
{
  return Node::distance(y.get_node(),x.get_node());
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* rnd_node_iterator.hpp
Hw20iH4sz6+5+mK8BA2SbSZNd05LFgDTv/sTTuYHM9y7GKTWrFxkcwcdKYP1xWD5QjwOIj6yBIuyob5pcD6Y9OO/fzVlzaqlS4e2HmYR8SzPFv8prJ6PDZfxSdPdQzKxWDI/mOEe0nAVQ7AhvgSyYsyut/SdiLYeYREuZpV9fyzAfBhpEQ2sym4H+uZBDGMsyc96pH0ML/8KeY61iPuasg8vPV8ivvEWUVQom1Pq8j+IgewOs6V3+n9DDBOSjyvSdPcEEskySMtJVmHvmKoYgxNpXMP0zy2CyLxg+ucWIbp0+ucIoTrTH3PCDDZxYKVeaDOymsy+519WD7GTpWR2e3HXEYidLAVM/wwl0ZBuZ7N+4xD7JL1ZvNuORHwGS1+3ibrnQdaa2dG4fuWxZpFN8FBWY2f7u+jbaRZR3ars8b4sSzF2Z1nEnyzPdAFF26AfZltEDk1ZoTljIrEuzbGIDkLZ0NFT1bvL/9L6wixv2SrqnXyykcyOR8xT75vOtYhsFmXni05JiboskPNPmm7tIfODGa6nF6gxmIPs7Jiu2dEuZN7Mlp4p0xTx6Uw/PmPJvGD68RmnS6cfn/Fk9XmeD8phbQ2Jlf0urfzDoF3o91hVXnbDuVs4WWqYYc0ySRdDlopZ8VM31T1OkzxdJnkmGPL8XGUvnleJhe7T+S50X16ISbrQhfry4t7+UxntYpIuyqS8GJN0sYbydk723oi+NckzwSTPREOeu54+zY92WWTSLotM2mWRPs/dS4YkoF1M8ow2yTPGkOeHtPV+YLyQ+cP01x0ukzwTyNLC9NcdYrHJeDGxoMXu4ws1SRe2WBef7pl3lEmeMSZ5xhry/OHIp46pi923WYJJnomL3beZ7xKTdjGxEBMLXeI+9nCTdFFL9LEPyZJ6O9psiUmbLXHfLvFL3MeeYFJPsdRkLC3V17Pkt/MWtMtS93mGmeQZbshz8KB32TDHTPKMNckzzpDnu5I512COmeSZaJKnWKbPc1CJDs8wXpa574fQZSbzaJn7PooyyTPGJM9YkzzjyQJhhvsFJha03L2FmVi0icWZWIKJ+a5wb6EmFmVisSbmMjGx0r2FmFi4icWYWLyJJZpY0CqT/jOxaBOLI8sE099fSjAx39XuLdTEokws1sRcJibWuLcQEws3sRgTizexRBMLWuvewkws2sTiTCzBxHzXmfSfiUWZWCxZFS3ZspEFd99xC3nGWUQWZhfyzqiPGDbIe6rSfEuMrYL+22gR1ZjdWjZjGvqIbCizkMiTx9U7ZhYxn9m76k3xTqLYbBE5mU2PvTkV6ch+Zxa5/ftYlEeWndnM034LMCbIijL7eG7GEZS3Ra3zQcZjsYkFkbVi9jLC9RhtTebPbHqxDXbURW/68yyyesxaNV+LY2rYVnnMkaY7jpEtYDbrSXQE+nabRTRgdij1BfXOCVkgzHB8MDHf7XKcSdONTxOL2q76KJCsYJG+29BmJuYi+42Z95dWToyJHRYxkVl0QfEZMZB1ZvZ515bmqMtOiyjH7NC1OcXQRwbrcufRUcS+S44JaboxYWIhZBHSspKtCZ0Qi34gq8ns+LwSXVDebosoIC1LUt+uCT2MMUGWg9maMlfUeR2ZP7Obr38rjrYmm86sR9U2KbDu7rEIp6bMubO0hnrulfNPWtfbA1ahnvv09Vw6YYkX6rlPX0/fnbf/QT3JfJktX3OtAOpJ9hezDLufqXfT4i2ijaasy6tdkZjTByzJ78xKa5KvX0/ER+YFM1wjmFi0icWYWKyJxZlYvIm5TCzhgLr3lJlsyLbXz9AuB2VbS7u/eVNXjF2yF8yuFp3eFv13yCISNGXT3rVU7/kfsSS/DyZt4aM=
*/