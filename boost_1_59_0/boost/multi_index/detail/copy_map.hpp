/* Copyright 2003-2022 Joaquin M Lopez Munoz.
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
#include <boost/core/no_exceptions_support.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/auto_space.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>
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