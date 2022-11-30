/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
#include <boost/core/noncopyable.hpp>
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
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
*/