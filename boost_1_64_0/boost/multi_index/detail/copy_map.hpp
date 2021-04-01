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
we+wA6qWwyGZotgwWIbh8mSee9sO2TIa9Txaw85PyIQCGqGK5KAi3MNJw3/BdWg2hHqmYDV94oPSLBvP7QJSdvQG8ftosV8RtK0j9DvYbUGnlO+Tg18Xm92CG5n9z7FHdv0KQ2n7eA5jW0y9P6x3rr7zZPMKh5wzsJbj8W2B7PvqQ9nh/LKLucWM88bgwm9TPquEcsiA5U0eE+EFBpIWc8TFDDEoz2+V0U6HwCq9oFKBuaKAwXaTgLw4MOHxqM0AgBF/L/ATklzalRjqFq6LRWuadzR2AwzSBNtXxT5+C+4I/XjTV0dG0kucu7EpFdm5jv0KjSSIUX2AhYHkeWLkaglTDmuEQOzav9JVHxblXlCVIltcfv4+12g/QwLZ61iy0TgB5Ed8uhWBPegLr8fP2HJLDxRn7+uX8OpqDtAnEthDrgUb1ogLWwyhGTI1JLsodYFshgStdXJMHcUYMfEe3fdG4D42H+zjnkVCdJiT/NLFNhO+2FTUtCCloAs2JpNX7tPs3XPKnZF4fX0L0wWh9F1laINkiJPd3bbim39BcJ8qoKCdl1HNHZJTaQ==
*/