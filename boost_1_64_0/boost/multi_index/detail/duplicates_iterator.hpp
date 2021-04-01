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
ZffEbR+oU9c2TyNYayjoDjkmmT92sQBR5ns+RwIQvBbd/rTANUVHuBIdWu02AZiou5I3OpfWfgs+atT2N0PeuV1JVaVSkNtkK42XnhienmGalrmG1S4SmM86X0GEA2tK3RZ9fZJZEu3ebL5zZJWlg3v8JG7F6eDzE+htE3fGcKDJndAhl8axsIub1M8K0+R4K2PnMR1VC7ap7Rv71gtzrKuBrV+g7JhMB8eE/x0yzn1Z5bb4FxAmO6pj4YB9yBo7q4fnJPz43GNXypS8UV+WhDZ34n3/g2EzGDe0enmhr2htd0aA8IyyiEmeLikzlTGYh7DJz2O2qHaC1kmGQoCwcHqqeYxZy1exAsG232rMtnCx2vr8B6Y63Fnxp/hHgOz/R5c1c84hbyRZKCMa3xedmgXXX1S9h3sgdQrF8fZDwjqbzKs7uWZLr67anhamADX+L5Q2ajrPjIeujJfvyhKBPdWPGINdVU1Uuk39/0jFtoSpC1j4tIaknP0yzwQ1ubB5BT/gSHHeYsc96EZbnuBrhhM+lIiebJueaQvyszUxGaom30uO30cDlEWOog==
*/