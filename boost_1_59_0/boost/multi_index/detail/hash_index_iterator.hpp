/* Copyright 2003-2020 Joaquin M Lopez Munoz.
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

template<
  typename Node,typename BucketArray,
  typename IndexCategory,typename IteratorCategory
>
class hashed_index_iterator:
  public forward_iterator_helper<
    hashed_index_iterator<Node,BucketArray,IndexCategory,IteratorCategory>,
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
    this->increment(IteratorCategory());
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
    load(ar,version,IteratorCategory());
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
    Node::template increment<IndexCategory>(node);
  }

  void increment(hashed_index_local_iterator_tag)
  {
    Node::template increment_local<IndexCategory>(node);
  }

  Node* node;
};

template<
  typename Node,typename BucketArray,
  typename IndexCategory,typename IteratorCategory
>
bool operator==(
  const hashed_index_iterator<
    Node,BucketArray,IndexCategory,IteratorCategory>& x,
  const hashed_index_iterator<
    Node,BucketArray,IndexCategory,IteratorCategory>& y)
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
template<
  typename Node,typename BucketArray,
  typename IndexCategory,typename IteratorCategory
>
struct version<
  boost::multi_index::detail::hashed_index_iterator<
    Node,BucketArray,IndexCategory,IteratorCategory
  >
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