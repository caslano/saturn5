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
kH6ClZiYYY8Eho1jo0hrEZQGLnlXIfkHR8GY1u3BsQZCOiuGttsef0+Pf3TU2gR8ogs+0bhcETpV+kdDx6NBDBsN3GR0EvSzfTf1c1qNOI/1nVBMqItJPCgjCBg6xtFVMJGd5N88/tv0wtTyvTyKeTyKWjVqSkm4lckfjOJ7awy0FgVav+caDM2P40vXGrRLH0dklzUwjlRMKvJepr6clb0aW0imcTwfPI4o+CBKCnzkwDVhqR0UD/+S4J8k+Qdlwt8E+OeE43RnMdZU2q7c3AfjLgMRNhonG9JJDCjzD0IasHMXHQINiNiIVZtwzmD0VB6VkfroHcwbJjZSdyWojtNDaYPcV3XMTEe32NNzdmoKuNNFZ6cCl7GtY/Fvuwqjc1td162DMq1yvcffQ6eqHe4JGn6pyfATVb3ugxaGv+k+6Bf4pOd2MQ4HpoJ8BrjaTUrZj2z8LnM1UGS/KNCFZL90w8x+Z08FMdxgv3T/Fymlp+8tRPvPb0MZbUiscnIDHMjVjbYptVfdbtRyobXi9T8cqxdswoCwnH76ggHp57s0uTaoWMmBdC3ZdFskDFkg7Z31yJfFgdDjSbkszl7Ym10kus/SMvQHNJkl7D7cq02K57BX1r/y7jlKy5olTklIZm45YZiVgjGTPAFvjKjACkij7LqdVhI2uW44pzGPZaeZ43BaAsJUvCfFnZDXWURwVilXQ0+eAnd8VN3F
*/