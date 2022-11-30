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
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
*/