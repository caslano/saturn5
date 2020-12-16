/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_SAVER_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_SAVER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/index_matcher.hpp>
#include <boost/noncopyable.hpp>
#include <boost/serialization/nvp.hpp>
#include <cstddef>

namespace boost{

namespace multi_index{

namespace detail{

/* index_saver accepts a base sequence of previously saved elements
 * and saves a possibly reordered subsequence in an efficient manner,
 * serializing only the information needed to rearrange the subsequence
 * based on the original order of the base.
 * multi_index_container is in charge of supplying the info about the
 * base sequence, and each index can subsequently save itself using the
 * const interface of index_saver.
 */

template<typename Node,typename Allocator>
class index_saver:private noncopyable
{
public:
  index_saver(const Allocator& al,std::size_t size):alg(al,size){}

  template<class Archive>
  void add(Node* node,Archive& ar,const unsigned int)
  {
    ar<<serialization::make_nvp("position",*node);
    alg.add(node);
  }

  template<class Archive>
  void add_track(Node* node,Archive& ar,const unsigned int)
  {
    ar<<serialization::make_nvp("position",*node);
  }

  template<typename IndexIterator,class Archive>
  void save(
    IndexIterator first,IndexIterator last,Archive& ar,
    const unsigned int)const
  {
    /* calculate ordered positions */

    alg.execute(first,last);

    /* Given a consecutive subsequence of displaced elements
     * x1,...,xn, the following information is serialized:
     *
     *   p0,p1,...,pn,0
     *
     * where pi is a pointer to xi and p0 is a pointer to the element
     * preceding x1. Crealy, from this information is possible to
     * restore the original order on loading time. If x1 is the first
     * element in the sequence, the following is serialized instead:
     *
     *   p1,p1,...,pn,0
     *
     * For each subsequence of n elements, n+2 pointers are serialized.
     * An optimization policy is applied: consider for instance the
     * sequence
     *
     *   a,B,c,D
     * 
     * where B and D are displaced, but c is in its correct position.
     * Applying the schema described above we would serialize 6 pointers:
     *
     *  p(a),p(B),0
     *  p(c),p(D),0
     * 
     * but this can be reduced to 5 pointers by treating c as a displaced
     * element:
     *
     *  p(a),p(B),p(c),p(D),0
     */

    std::size_t last_saved=3; /* distance to last pointer saved */
    for(IndexIterator it=first,prev=first;it!=last;prev=it++,++last_saved){
      if(!alg.is_ordered(get_node(it))){
        if(last_saved>1)save_node(get_node(prev),ar);
        save_node(get_node(it),ar);
        last_saved=0;
      }
      else if(last_saved==2)save_node(null_node(),ar);
    }
    if(last_saved<=2)save_node(null_node(),ar);

    /* marks the end of the serialization info for [first,last) */

    save_node(null_node(),ar);
  }

private:
  template<typename IndexIterator>
  static Node* get_node(IndexIterator it)
  {
    return it.get_node();
  }

  static Node* null_node(){return 0;}

  template<typename Archive>
  static void save_node(Node* node,Archive& ar)
  {
    ar<<serialization::make_nvp("pointer",node);
  }

  index_matcher::algorithm<Node,Allocator> alg;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* index_saver.hpp
bGS5P+P6lhhtqWM1ibn38MwBBXjzrlg0PHK0oIv0tvXXHzMaE8Zsyc+PysTnLaFdruf1WnUhP99/98c8E/kMOeYdsH9uuqndk1n/uls+J6N9x9FYqgf/8UT/Lhvp0aQoRzjLowi0zaGoVHJp2tAYSpqxTN8fhPmt4Yzbs/lgpP3V0jV9vvY7mffvl3YVlD+cg/mXZ/loxAmUz/ztMo3zB3Mx/98u0zj/tZz/r5bAaXzuXsHOby817faOHvK3efVUx3rxWeYzVs4U1zmwIucZeJow5K5X5l9uMwa3tWYlfq5/04R5JtvI622j6esRXhnzUVVNfx2Zbk/BHMN6qKJhopQNWxchpslUZ2ODkKW+mkmFRy/x5vdWGXlsqvWU5XzGeJUZFV69xftsX/GN6md6//4ZLcLRTS2d1vvMX6q4GetKO+vf28+1zF2JumPm30LNsh/IwPzL03T9jMj/t8/ophtjkHzmb18P26QPzFyu/Pw6zfE7LwufXX6Y9dprirVOC0caO2fOFGNki9iklTtR5ppuhGWjTk6hzNrz2fLlHunxK6AlNLqJ7x4UZ6+0bhynveQ+3MXxbbZZPuPdQ0q2iOlptvQklzsVxr7tsx67aHuoIzQT9aB43LRD5nM+W0ywVLRDTtQyb+WTcXW0V0XfodjwCb1Y9hXGXq5zKnS/tcocuDyBU0L2BX5PA78m1Eswn9jwxBDTqMtIu/sYoctMRpMIjqh1aLZRetSG3nSynuMzGARAOPjuUrdrLd4Sv7u0t5CPQ01tfx4Qad2qhpQr/Hso6mrTMFKrKnfrINLtkrHeQZFe1yI0DpQOwz/qM/H/yEyPmdKYA0ZmMr1/sTDjgph5va/b8A0oyTLz2eJToedZmWf5RILn/mx85m9fOddjqczft1uYMnal8j3YXQwHEeHZY52rKRnwPMcOU3fZcWqNee7rBypHnE2aLIJm1sWm4cV5W4vQqEHMVqP7YUruO/2FJ5Lh/769ylvXlhSOSLvJxWYV9j9Nn8L0bTW9Eum6bbVMx2M7klapaVsybRJ6fwXLBE2PJ0dJWn/eSdCm23usau/0OUkRZaNOhFCpiyF8+A3z8fnDNso3Oyr6CeZplI2s03P8/orXX3taGZicocrzHi6Ma3oLlzdZbDfG2iLThAwb50sbFX0XMdtQBnnUhun1feiTJF2/v0xF37kzkphTG0nIAzsixv9k9EeQdTVwvF7VdafOlAhxJkf66TIkjRi8WW4WqTwsLXUxLULyoFSlrtdila9G+BLURBvFPtwcLCVt43i+D32SpGs+66p610REAMLJNPdNVyuNIPKp0DJvzU8Dn9Axz/GdIsvudzZLaf4XyDz978qiqOq5Yqwnn7eykzrC0+PRDol3sCpdh4B6blsZmH1apD2WmIPnozqTwUp+tytTnkiqTuigsgiU+079bpe9oOlpsZ6UZLGWZ1h1WUd48lKOqKafl6anwtUo2LKAqK7vWVwXz6wO6TLu5DLwNUwSR39lL+Q2L2T6NGkzUGxkIVGN+1v95pmKR9cqwJCvHs5nHcjt1vSLmb5NVE12sq7dGrvh3J6pbBMVY1IiinMjMjPO/1bpvLxCldrfduFgGfeLXG8ekkTMJMjlfJ/NAPlErjJd9904T/9jwlOqbThIUt+x5ftgosvDeXT6b3d5xDvN4yvKIybOHSPdCJI88Ful6Z+k6dtEE0nOoMfj99N0PKOI6Eb0sx2q/lO7o9y6SsvPjug4AvXTt8t1OQnFY0oEtVc9EkO6j1a8aND7FsTldKty8PirLgffbxPb1Yke6xDBTunl6qEf68M+rlY+Sa+LqezBMqPej1A+xEV3JWwOx5ZTZx71pOw99cg=
*/