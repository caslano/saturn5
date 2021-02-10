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
IiNHPug36vbxuo8F2jWM+3vDwTssf+5e9yv9PEnQVZX+Ee3GUBifjkaVhjBfbCTNwDvtGYd7jx6/W8sD9Fmi5dVaivLmGFQmtKfAUU27xaPw7Jave2sPu1kqzWok5mZjHgI9qBdZENgyb63DGArOKhVBC8DtWwfzRHKGPgjZB04H4ykZYKYFQtsVcsXl2za/ZGALb/ugu5GzKEK/JwFKRig4GaEjbBpJ0LPN9ENw716LTLaJYpVkEikKnSoDLinxiae1oOVSswi7E2zGfbqj8Nt0G9uzUtA96qGzkQ00abHtVt8qlZGaO+o8abrrnJerRT4Buc65x7KMJ4FjX24YiND5pTCqdoNtlzGURm9LIL/prIXMorUDYCgdES1SjAVbFj/iLMmzYuG6BgZcdcGvG5YhGKeeNdIiBgGdlq3gIkrnLPJEIrRj+Oi9HE2eD0beYDQqFOI80qJYjzclimsMTCd2CxpPjmfe0eDt/mQ8Hu7Ppi49KO1BEXB4q6M4U1f/q/6lL8yvDReFB7KiAqftQPGuzBeMVMZ9DPKynyqDmk11n635VItaX3Omac4WHC3foVknY3rZ6T3qPt7pPhT/zjj7UuLcaPabGHBG98wguXvevduvt1sWodxwUQpTCTzcDYd1JhYpAfM8Vdtp
*/