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
3ffDN7UZvy8KiJOTR5kI9vYgPlJPbTB2zXrb2lP/GuVdjDLV4tKtQwItbis/AXMHctnc52d5RSJ2EyeMk0xsmP0FtXGvGmhLb92aMDv4ywL8Zt9X/IMlM/JlLFXn/RcyezubeFMT9/Jmn87X1pkbBL5TFaK5SqJ3Xc/r8yDVOsMt2IC1Hvh7OI7jp3P/4sJ3qyh3VRgr3Tn0+7yH5wiUpxCqSQtX5pXhmWiTxJTnpFeUvu8mpWLRL47xdxYyXiYvk36QOqkADY2Dc0pPzuYVaChwW2cc27xseRlFqeeUpmzMBjJ6fZW1pyOqoICn5gPDRL7vrE7XmI9g7DhF7vnABQWtobnBvo1iT2Su7+eqbQUdZ7mpwzsp9nRUwbs+lQ86K/d3Luz0X7SDIaGYr5DQZ4X1WmqKve/NaerNHVjIsTdyxehOvTJUFY2c2QpYEze888TO/u0RoLFYO5t9cv5xfcWOjeHFgRsf+vyUnkE7LeKvWUd7wXUEeUvZxl3cpf4DNr3ehKB3hjgd9wnwzpBN36fy7z3D6XZs2lfbdH2xU2eCmL+PYerBTfdctmYnY+w7SH+2cHaM2/iIRQcBhP7PSfQ5Hh+K02GLjvijTqTz+O5Xb4sYvSsCugRH0l1YZdF7HkcRB9/l4SQ0lguxtWvm2gu667ReP7sd0mtae6BunRL/u9sjHTaLdDQJvHt1B0pD2bjmvf8xoMMe0eQK4ZvngMM3dLCTkb59R0OHfJCO7Xb/OyF9PCwRvfdd0HVOWeZJUnihXlKMvTXqP41iqyrxpRvWa02DxfXrOYo9meRx4FR5CWtNPlducZlFGnpFHuml05jMVzCZVZR4YaCwpfS57/E7ed6eTODJbTCoLR8avh4OvNhx8wpMVbSgR3eAmMzMzePcD1xY2vJ185cpLheJ9J1MRlG9BubrZizH99kaOCoDP6qkFK4EBuvM5icUezp3syjw0wywTDj6Gfydta/nBpWX5bVljecppo5TLP5imeWl67khrFu47XSc4jJRJTKRceLX61CtbLztHszkekVYVX7igb3N+0NQ3BNyLyqqMMD1Bi/D85kNX+Y+RPtIRqs/+97sNitDnEeVF8kI1n28/65SnF62VFHu5GI1yAJruYc8b+Q8pUyzsnQqEXV3uuoCOjYJewd3mfW5WyZOFceQH/Y5+m+9j7WLr7BJGHtmeczb+jusnmBQp37iQmxMjvsRw6VpFKZp5qj9kIq3808obskrUleGfgm4THpydUyHfsvkVmlYxkHiC5lbcv/A5FZVXgZJFAKOyzVt8DfWBqkMZJZJH4bVM5YdS4+mVig2cwLXz6IS2mAce4xhS0fmaVoUCjtB7r0ZNon9onLdHMYeYrF9H06xC3EVeVEVibBczrnMx1LcKb+KgixLYg10TCtgvD/LbkrCPCp9Rx7WbsK5l5UxcaMwyBJHDDvaZYSXc5diFz2vyGQcwstGnpT2WLtMsSdl4MlcBpEAE53JvMraM86LzA8dPZdlcsWK+fpaln/hZEFcVoHwtjp7o8KSN5KvMdmyjIKyVBD9LSTV65oyv5uV2VcZRJHrwMtZ4753rrEdYHhDLCVlcWxSu2l6HHPp5Mh++C3S4ds8D16YaFdvtIDW2VW9CJHWdtnbpTNAq02HNXK+UB3BdH0oMkVoH74N0iAv1bcj2u5tOQ2MM9znvh3QVBgtRVG5Ic/U7SGdVQt5/nkHoEF1ePm+cwzS6yWGKsB5uK/yUHIG5bL7Fngyg5h3Mgy/k4FndHcex+wTv8b3Af0Wfot3P07p3G/xlPE3eBJfD+aR78Or5KJjjvfIspjw/YzxuSJNith1MlfYV7Usv66bVn5xHCSeH+YjPm4=
*/