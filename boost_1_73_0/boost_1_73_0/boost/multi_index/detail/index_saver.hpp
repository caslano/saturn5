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
YLSoSmv+9GJa5szwIpMbaR2Gl1FTUTId/oXF+mF9YP5z5pbx/neZaxbWrnMBghVzFIo3xWHznMCBSK1Y2EnXy8jmDp+xGlk55HYvszt5U8uJq+BqeY11vaPdVNOYlpP1aVDM4P1o195rfXqtxu4aavZgSbwVMFi6rrr2KrqbwOtRu8a7I+Pb7wUnwwF9xPVWH/V0s/ytK+LH+gA8kuqjwSJ4lhx1OfKtfO0q/gxQSwMECgAAAAgALWdKUjVsXVGQBAAAkQoAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1MTAuY1VUBQABtkgkYK1WbVPbRhD+7l+xdYeJbFTLhiQfgHbqgANMjc3YJglTMpqztLaule/UuxPgFP57906yZaDU05kIyOn29vXZZ08Jmt/vqUETtj6h+wvpodVZXCr5B0bm37XD8AGKH7K6oXVbkAAqk4ewAdtNHsBzJmEZ5ci+h+G2QDc2N/tPYC1vQvtKEjKzlscyWyo+Twx4xw3Ya3f24Sda9to+9LnINQw4phoFfMTUfONiDkeplf+asPv7lsZfSj+ThGvQcmbumEKg95RHKDTGwDTEqCPFp7ThAkyCMOMpwvHw8vp8cOrDXcKjxDpZyhx0IvM0hoTdIiiMkN8W
*/