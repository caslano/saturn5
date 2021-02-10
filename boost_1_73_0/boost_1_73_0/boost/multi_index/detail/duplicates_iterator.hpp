/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <iterator>

namespace boost{

namespace multi_index{

namespace detail{

/* duplicates_operator is given a range of ordered elements and
 * passes only over those which are duplicated.
 */

template<typename Node,typename Predicate>
class duplicates_iterator
{
public:
  typedef typename Node::value_type        value_type;
  typedef typename Node::difference_type   difference_type;
  typedef const typename Node::value_type* pointer;
  typedef const typename Node::value_type& reference;
  typedef std::forward_iterator_tag        iterator_category;

  duplicates_iterator(Node* node_,Node* end_,Predicate pred_):
    node(node_),begin_chunk(0),end(end_),pred(pred_)
  {
    advance();
  }

  duplicates_iterator(Node* end_,Predicate pred_):
    node(end_),begin_chunk(end_),end(end_),pred(pred_)
  {
  }

  reference operator*()const
  {
    return node->value();
  }

  pointer operator->()const
  {
    return &node->value();
  }

  duplicates_iterator& operator++()
  {
    Node::increment(node);
    sync();
    return *this;
  }

  duplicates_iterator operator++(int)
  {
    duplicates_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  Node* get_node()const{return node;}

private:
  void sync()
  {
    if(node!=end&&pred(begin_chunk->value(),node->value()))advance();
  }

  void advance()
  {
    for(Node* node2=node;node!=end;node=node2){
      Node::increment(node2);
      if(node2!=end&&!pred(node->value(),node2->value()))break;
    }
    begin_chunk=node;
  }

  Node*     node;
  Node*     begin_chunk;
  Node*     end;
  Predicate pred;
};

template<typename Node,typename Predicate>
bool operator==(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return x.get_node()==y.get_node();
}

template<typename Node,typename Predicate>
bool operator!=(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return !(x==y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* duplicates_iterator.hpp
7gURrHYraOAJh0N6Xr1+cqetgyKd4ugkSi7rmKnCloWMXwfo+65RyU3ZzE7/igoo7UJaaeL2FW+a0eSe6Fpzy+7J2E3M8iBzY2ZOb9IEN+Xp3p5HAXB0SH7tj0eNJ8Flyd4tqff6UOwdl+ISYcteYdQY3XcfyIvwolNGDRSmCYJcEhgA+IWP6Vc+DK488GZpjZOwZ8MnU64wrajMC59nBdUUT5XwVTFlMEOneMi4wxzPPkcnbis87bb8gePpZgLnhN+jRvDzHXTX4SlTqxA9ttNfUDCPOPI164Vlob9wx6A77WFwvO9O73BE4BeUios5ntFIwf1jH7+D7SJncN4Lx4bvn4Cuap+qEx7tvE/03QaOS57ew7UdcOVaIQGfRHT6EJHGT4sr9vEu/H+g73wJpfu3Engk9KOQPxPX7udRuv9fKP360D9z2Nfufm18qP0LUEsDBAoAAAAIAC1nSlIyM8gkzQUAAA4OAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTA2LmNVVAUAAbZIJGCtVvtz0zgQ/j1/xV5uCk4xeZTHDIS7udAG6FyadJoU6F0Zj2LLicAvJDltgf7v90m244TClbshfThe7ePT7rcrdXZ/3qdBu3Trx7N/Hj54Wotj
*/