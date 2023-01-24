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
8SXlwyNhlnXTeQME83viCco5lteO6HsgN6wuXJJ9FQBdFfzbAR3ugOcBUbw1SvYiig/Yj6Pfw1TbfhDVtu9A87HuCfJ7Q60jSzxYn/eNUINAOchkHzUN05q2D9m0G+kxYQRsWrvvXw/V7gTZYt1VQo8M7TaHbLee2+0QKmRo90rIdgus6C25RSiPoVmeuRmsCb3lg+jTJ3+WCvurSGo5MGSHN1CQs1vBdlHU7pKQ7Wykjt8newHrqlaEakFeeLrasf9jQZkUeuNpWvLYGlTXeGtUR2dxgSol4LTb4AItN8Tjn+ENQctx1ApjORb5zqtqqrxlzp8IlN39qb2sZs7nGiw1Rbvz7xJ2zxXkWvw79/nyCnItJqzcu503K6TiKNiSBagJiPngqM1KVAby7bAM3Ab/NQwR83Pld/yr/DwMryn0+x39fkO/e+m3hn4/p98tw4L3NsMZk/XNcL5LR+ZU+QDgM7ChjP3uRNXln6EhdOerBELf+2/KXFc0BOtT+2echvswLA4X3MeB7S9u9wrH8HErt6e4sBqB8Jf8O9RsJaCBCjaJFsTpd2lDMWMl9L2Scfqzd7AIgThjP+2Q3XxPZp16eLjUIwNuzyj30lmFB+ntqKpU+UuYNNXx/Guhnj5FVGcG0PsMhZpNfo2nWUGqg0GwGxEPEcQ9ZLuasRxAXM4gXvEOGhRHLcdFNsvA/VsZ9x+HMSrtzRq1tb+E
*/