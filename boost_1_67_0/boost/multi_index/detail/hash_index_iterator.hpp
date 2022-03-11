/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_HASH_INDEX_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/operators.hpp>

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Iterator class for hashed indices.
 */

struct hashed_index_global_iterator_tag{};
struct hashed_index_local_iterator_tag{};

template<typename Node,typename BucketArray,typename Category>
class hashed_index_iterator:
  public forward_iterator_helper<
    hashed_index_iterator<Node,BucketArray,Category>,
    typename Node::value_type,
    typename Node::difference_type,
    const typename Node::value_type*,
    const typename Node::value_type&>
{
public:
  /* coverity[uninit_ctor]: suppress warning */
  hashed_index_iterator(){}
  hashed_index_iterator(Node* node_):node(node_){}

  const typename Node::value_type& operator*()const
  {
    return node->value();
  }

  hashed_index_iterator& operator++()
  {
    this->increment(Category());
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
  void load(Archive& ar,const unsigned int version)
  {
    load(ar,version,Category());
  }

  template<class Archive>
  void load(
    Archive& ar,const unsigned int version,hashed_index_global_iterator_tag)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
    if(version<1){
      BucketArray* throw_away; /* consume unused ptr */
      ar>>serialization::make_nvp("pointer",throw_away);
    }
  }

  template<class Archive>
  void load(
    Archive& ar,const unsigned int version,hashed_index_local_iterator_tag)
  {
    node_base_type* bnode;
    ar>>serialization::make_nvp("pointer",bnode);
    node=static_cast<Node*>(bnode);
    if(version<1){
      BucketArray* buckets;
      ar>>serialization::make_nvp("pointer",buckets);
      if(buckets&&node&&node->impl()==buckets->end()->prior()){
        /* end local_iterators used to point to end node, now they are null */
        node=0;
      }
    }
  }
#endif

  /* get_node is not to be used by the user */

  typedef Node node_type;

  Node* get_node()const{return node;}

private:

  void increment(hashed_index_global_iterator_tag)
  {
    Node::increment(node);
  }

  void increment(hashed_index_local_iterator_tag)
  {
    Node::increment_local(node);
  }

  Node* node;
};

template<typename Node,typename BucketArray,typename Category>
bool operator==(
  const hashed_index_iterator<Node,BucketArray,Category>& x,
  const hashed_index_iterator<Node,BucketArray,Category>& y)
{
  return x.get_node()==y.get_node();
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

#if !defined(BOOST_MULTI_INDEX_DISABLE_SERIALIZATION)
/* class version = 1 : hashed_index_iterator does no longer serialize a bucket
 * array pointer.
 */

namespace serialization {
template<typename Node,typename BucketArray,typename Category>
struct version<
  boost::multi_index::detail::hashed_index_iterator<Node,BucketArray,Category>
>
{
  BOOST_STATIC_CONSTANT(int,value=1);
};
} /* namespace serialization */
#endif

} /* namespace boost */

#endif

/* hash_index_iterator.hpp
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
*/