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
BWjCp8/jK4NFwvTelZy/XUhS+8DZb6bMynOw7Z6sFWR0T01jRoFlS7JHXjpxke14DdlpTZS4ZDZyZKin85ol6hm52vksVyZGqdDpLQnI6tPijF++moCV9dVXFlPX95NlLcjwwvexY/Y8S20KdvpK1UEmgSmWwHw6jSeI5leEby+XC6UP1IzGQaNQQcWIeHy/zma6YKXNa+zr0aj4RAlfESxS4ZvKkUwZEVVVhBoqGZESTQFvePaR6Q1kH4GSJdwWKnZFLKe0kiGTusn0dMsUEzApguZpPIPXZBkA6MdP1SY9ftjEz5rrmsvI9ug2FdfyJSIKVWduQA8RysTMhjDK3/6LjSPqTjyAA4nBs8yH6To4ExxdjyBaG1deXCtQBHzHFY5/wNV3qh1Azov+ZAKkF88vcynysijEXFYRep6oscyohpKWInJfURdPc62H/oZgTg18bLR29DM7oXdzshIWspU/oWayt4pZ4IjjT+LM4+0NFIL3OAxHz0YWWa6Enkc6GmbQMcb4MjIO8OeXjSYO3skAJGsA2uM9Cj57AGZzvYYyK9bjUE8oLK6/EQ==
*/