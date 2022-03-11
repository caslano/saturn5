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
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
*/