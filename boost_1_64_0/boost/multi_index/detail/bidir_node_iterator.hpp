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
ReHnXhHl1/6mYt3Osdbjneb7rTIIoyyORasrVUnw3gRsd6XSfBG2eHKBCbsW9d/0YdRX6O/YR2lc06UdOKmXhgKqhN79bd9Ov/3/WNifPrXbquykFuGRalgrPEj2s7SUFeBac1btr/6u8NBKE96WUe2PfjVuRPoctUv7zkiNQaPUeN1NoF9i2wGHHbrS99jHKA56gAbKHh5HjDY6pv9RxNUDwAud5rpS8lC7xnCH5kDGtD8Q4ut3guGgPEFs104DW+mX64sMk8lD/6c2M7s4rhZepO4O7gZ8qPlZ49a1jdr3P3I7sFFrSp8VWysP6q/zL7yIfuMcOwy8TN0IcDNY6muLf3Ye/h0qY9sidjw/9WNPTB6aetDh6SMPnjnaml+QqknjG9l4MZ/zbLh44pXX/hZyPRb03ugwjc/1Re7ksZ1b/tDBANuhpFt/u+EfdjUs8hvU2aiOs8fyGIAOMSu9sNg+TvA7sAoaRagziLMKXhOYz3eyOF0wAvE9K7f/iXyin5QLKs4mfBJXxaTxp9FY0byLlPegpUOtBx1pT7XnDy0cftDUIuFd4rz2dvHtPU14h+VrBtvwDjDeofZS9aetebovTda8U2trkrY0ebU/DXL2XxK5GYM3M0SOfvduXNlfbcoBskTH79yIxrrrNYrY+KjGnqIhxCbHEENB5TNZCQIm58pO/w7Fw3ZDWGu+C4/9k/XMJ1X44kars9mUHjDgGeG+7+UbAba01lvqYDyLN6nDZIp0L7TvZnW41A7S8Jm9EN7ZeKp8hoKGf1CFb25srS8+hekA6Dh/cG55jh8HmQCdwuThU1rlY1mCnjNRmQfl8HhaHpdCEqc1eVpz30m5U0kehp6XKC5Gi9x3MW5oFVGcRI7Ky4K+x5VruwDKtSMROFFoWWWk2F0j+242W1qON/uIQ3K+m4X5DrUwD9BrQRrfdOL7ceFaXlUPU8flmK3tRajP9D2VfmVrrdPvJ4dHaHhzYb5Bvo0cW+pQe+xRhqHBJeqFh+EQPXJgbT6EA8mQdO6+Q3PkY7K1apn2k8YE4Gqhze4fnSbhMkaco+aojyZfHuC1epk8Cm2daD9aTM3018qvpeuo5Z5Uele+nvQ66/MUh6NvWNi1FEfotD5qrOvgYK1e183Qdd05g6eP2aVbUuS8h3Jgj4Okw8h5lxEPpAQUKBj6bL+Hsgs/0VqBylTLhUfDWbL24/TWW2ofMejihPtnIn6cnn0VroSfrsfJ+efDGu0R8P0Qjzj0iEewxIU4Ko72v8fnXmisTa3A9e2yvN7vsY7vJzQ+uxCZk2dukLnDv3PzrRX+fUu1c75Y+6R6Ef9u2lnm+Hmcike3wR5h88RGrzqoWZav9a221YN09VEzqEBlTP33KWZoXG4h3NANosiOhuUNVacOT0iQ7+/z2Dznl15kp0koevXLosh7AeMVTpoGiReKrUV9NqTv3jyW2+vX5rT9+zePxfs3SDFu4OCe7+a457vBLev1+M3lHF86s3PH4JtS+9bRHcmCdXntUyuq/fG8VeIlIdyV3O25ySjrhrWFA3l3ZWSAUx3BNYjd8SAHRhp9a4rjtWE35mMQ1wd+yOmMIcccMnh35gfI2XYI9u8KjQ/lgra9rx9lHHTRhfjDdjAc6wXvCnAc6gTvwu6bYJi2JMCZGtc4yEMXc4hN7mQYaGKwfK/lWKfVW9ZxI2fXLsbZbD0Vm7+/TxvgqCwg/ozdJq72aljOn3C8spHAYmI8cL+H8LDdMJ7LHDfd5CFv9caUx9uf+XdDXjUAad/YfzONcePLBl3f7QUOteTuY+EtANMfGqnNanVQZ1feErDBsU99qZ1jHHN+6Jdh3z7g8U/SreUc8zapc9w=
*/