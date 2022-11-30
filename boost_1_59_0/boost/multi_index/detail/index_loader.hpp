/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
#include <boost/core/noncopyable.hpp>
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