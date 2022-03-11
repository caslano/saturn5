/* Copyright 2003-2020 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_COPY_MAP_HPP
#define BOOST_MULTI_INDEX_DETAIL_COPY_MAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/addressof.hpp>
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/move/core.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

/* copy_map is used as an auxiliary structure during copy_() operations.
 * When a container with n nodes is replicated, node_map holds the pairings
 * between original and copied nodes, and provides a fast way to find a
 * copied node from an original one.
 * The semantics of the class are not simple, and no attempt has been made
 * to enforce it: multi_index_container handles it right. On the other hand,
 * the const interface, which is the one provided to index implementations,
 * only allows for:
 *   - Enumeration of pairs of (original,copied) nodes (excluding the headers),
 *   - fast retrieval of copied nodes (including the headers.)
 */

template <typename Node>
struct copy_map_entry
{
  copy_map_entry(Node* f,Node* s):first(f),second(s){}

  Node* first;
  Node* second;

  bool operator<(const copy_map_entry<Node>& x)const
  {
    return std::less<Node*>()(first,x.first);
  }
};

struct copy_map_value_copier
{
  template<typename Value>
  const Value& operator()(Value& x)const{return x;}
};

struct copy_map_value_mover
{
  template<typename Value>
  BOOST_RV_REF(Value) operator()(Value& x)const{return boost::move(x);}
};

template <typename Node,typename Allocator>
class copy_map:private noncopyable
{
  typedef typename rebind_alloc_for<
    Allocator,Node
  >::type                                  allocator_type;
  typedef allocator_traits<allocator_type> alloc_traits;
  typedef typename alloc_traits::pointer   pointer;

public:
  typedef const copy_map_entry<Node>*      const_iterator;
  typedef typename alloc_traits::size_type size_type;

  copy_map(
    const Allocator& al,size_type size,Node* header_org,Node* header_cpy):
    al_(al),size_(size),spc(al_,size_),n(0),
    header_org_(header_org),header_cpy_(header_cpy),released(false)
  {}

  ~copy_map()
  {
    if(!released){
      for(size_type i=0;i<n;++i){
        alloc_traits::destroy(
          al_,boost::addressof((spc.data()+i)->second->value()));
        deallocate((spc.data()+i)->second);
      }
    }
  }

  const_iterator begin()const{return raw_ptr<const_iterator>(spc.data());}
  const_iterator end()const{return raw_ptr<const_iterator>(spc.data()+n);}

  void copy_clone(Node* node){clone(node,copy_map_value_copier());}
  void move_clone(Node* node){clone(node,copy_map_value_mover());}

  Node* find(Node* node)const
  {
    if(node==header_org_)return header_cpy_;
    return std::lower_bound(
      begin(),end(),copy_map_entry<Node>(node,0))->second;
  }

  void release()
  {
    released=true;
  }

private:
  allocator_type                             al_;
  size_type                                  size_;
  auto_space<copy_map_entry<Node>,Allocator> spc;
  size_type                                  n;
  Node*                                      header_org_;
  Node*                                      header_cpy_;
  bool                                       released;

  pointer allocate()
  {
    return alloc_traits::allocate(al_,1);
  }

  void deallocate(Node* node)
  {
    alloc_traits::deallocate(al_,static_cast<pointer>(node),1);
  }

  template<typename ValueAccess>
  void clone(Node* node,ValueAccess access)
  {
    (spc.data()+n)->first=node;
    (spc.data()+n)->second=raw_ptr<Node*>(allocate());
    BOOST_TRY{
      alloc_traits::construct(
        al_,boost::addressof((spc.data()+n)->second->value()),
        access(node->value()));
    }
    BOOST_CATCH(...){
      deallocate((spc.data()+n)->second);
      BOOST_RETHROW;
    }
    BOOST_CATCH_END
    ++n;

    if(n==size_){
      std::sort(
        raw_ptr<copy_map_entry<Node>*>(spc.data()),
        raw_ptr<copy_map_entry<Node>*>(spc.data())+size_);
    }
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* copy_map.hpp
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
*/