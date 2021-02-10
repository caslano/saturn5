/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_BIDIR_NODE_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_BIDIR_NODE_ITERATOR_HPP

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

/* Iterator class for node-based indices with bidirectional
 * iterators (ordered and sequenced indices.)
 */

template<typename Node>
class bidir_node_iterator:
  public bidirectional_iterator_helper<
    bidir_node_iterator<Node>,
    typename Node::value_type,
    typename Node::difference_type,
    const typename Node::value_type*,
    const typename Node::value_type&>
{
public:
  /* coverity[uninit_ctor]: suppress warning */
  bidir_node_iterator(){}
  explicit bidir_node_iterator(Node* node_):node(node_){}

  const typename Node::value_type& operator*()const
  {
    return node->value();
  }

  bidir_node_iterator& operator++()
  {
    Node::increment(node);
    return *this;
  }

  bidir_node_iterator& operator--()
  {
    Node::decrement(node);
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
  const bidir_node_iterator<Node>& x,
  const bidir_node_iterator<Node>& y)
{
  return x.get_node()==y.get_node();
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* bidir_node_iterator.hpp
R4sluYynF2Q5vhq5Tb8a4jZPhsNhq8UllgAydJKcauit5pNu658WwBnOoOdqycA7mK4mk9PaegW9ohKWPzI7EIMpCqIrKbncNEbn5OlH8zn5GI8nq/moWUNZcXW4hzUbBDYYigZj8SoQlxexvEDATtfbN0KtqSBccttxQeRiMvsQT0g8mQQHn1lY99NgZdTsgtFv6JHRMIuXIJgjn8fseklwiMBJcfq03+UoPh/NIzg5YqdpSnIsf8FCDni3DqzBBW9EpnTRrP9+JF5wpGuFEii5V4GpytYyYDdB8OMgcKcWlJVVcepfgsSOnQTeLW2EifzhRYB98F/1gQkhRDdg8KzjYH55F06JzD41VAClRrqs0/6eoYvMFm80Xr7f0lvZjlwmNV6T1b4sruK/ZnPyIT5v1jcKe4DfdSIYlVUZFr62/PCULv9D3ieAaiqsxWPxuMwU0YymP8T1amFc1xMMeqGT1+1eqi02S2kpfiCoEwFB0IDXNtN1U3SlBqF0oloM2OA3CHsodgl/GpgSErx4n1JL+wEE9/NYrTcueeTG9qmSqmDS9cB6Dbv2l4rJhOFH0O5KBqvYIWPAo33WvvsLVC/6e9CsNRVdr9X3slkNEofK6e7zxhdvD7UB/NRlWb+EL6akojF4YTC1r61v
*/