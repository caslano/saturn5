/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_INDEX_LOADER_HPP
#define BOOST_MULTI_INDEX_DETAIL_INDEX_LOADER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/archive/archive_exception.hpp>
#include <boost/noncopyable.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/throw_exception.hpp> 
#include <cstddef>

namespace boost{

namespace multi_index{

namespace detail{

/* Counterpart of index_saver (check index_saver.hpp for serialization
 * details.)* multi_index_container is in charge of supplying the info about
 * the base sequence, and each index can subsequently load itself using the
 * const interface of index_loader.
 */

template<typename Node,typename FinalNode,typename Allocator>
class index_loader:private noncopyable
{
public:
  index_loader(const Allocator& al,std::size_t size):
    spc(al,size),size_(size),n(0),sorted(false)
  {
  }

  template<class Archive>
  void add(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
    entries()[n++]=node;
  }

  template<class Archive>
  void add_track(Node* node,Archive& ar,const unsigned int)
  {
    ar>>serialization::make_nvp("position",*node);
  }

  /* A rearranger is passed two nodes, and is expected to
   * reposition the second after the first.
   * If the first node is 0, then the second should be moved
   * to the beginning of the sequence.
   */

  template<typename Rearranger,class Archive>
  void load(Rearranger r,Archive& ar,const unsigned int)const
  {
    FinalNode* prev=unchecked_load_node(ar);
    if(!prev)return;

    if(!sorted){
      std::sort(entries(),entries()+size_);
      sorted=true;
    }

    check_node(prev);

    for(;;){
      for(;;){
        FinalNode* node=load_node(ar);
        if(!node)break;

        if(node==prev)prev=0;
        r(prev,node);

        prev=node;
      }
      prev=load_node(ar);
      if(!prev)break;
    }
  }

private:
  Node** entries()const{return raw_ptr<Node**>(spc.data());}

  /* We try to delay sorting as much as possible just in case it
   * is not necessary, hence this version of load_node.
   */

  template<class Archive>
  FinalNode* unchecked_load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    return static_cast<FinalNode*>(node);
  }

  template<class Archive>
  FinalNode* load_node(Archive& ar)const
  {
    Node* node=0;
    ar>>serialization::make_nvp("pointer",node);
    check_node(node);
    return static_cast<FinalNode*>(node);
  }

  void check_node(Node* node)const
  {
    if(node!=0&&!std::binary_search(entries(),entries()+size_,node)){
      throw_exception(
        archive::archive_exception(
          archive::archive_exception::other_exception));
    }
  }

  auto_space<Node*,Allocator> spc;
  std::size_t                 size_;
  std::size_t                 n;
  mutable bool                sorted;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* index_loader.hpp
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
*/