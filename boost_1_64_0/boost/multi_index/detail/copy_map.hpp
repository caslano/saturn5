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
6sXN3dyJPVv0PXVCRDHX7a1SmUwEXuFnbpwIuyhkR9Bdid9TOk1lHhz5WVraVikwayQx7H++1u+xdvBEmaSxkzsOyeXqIrga3VINAgZoEA+WFe2pWFnz2LWtwreU+1Dkgg3AnNxT9JQNgPQX1NpalTcL4NqBujv4MWLzl8vvxLGA+6G8R71fHTZXPWyE4+pAqr2JExGuZwZ4mkLmvdFBzvoa0pB3dghvY2VxIL5dYwM8uE6FPDxzZjw+r/3EwLrblK8zbvIGy3fZ5GxTvmfsMHnDyzc+YfJ4+fBcG3lq6kdDx7vivRbAYWYlONxKQQ68cYcc07oTOeN7CAeimN/YgIsJ7H6KyVnqwt16jOMFN+G4uj5zor3J/Nje1OBszJM767UdEOeoCqT3uJdvpnH81JFyYzxy5ACve7JeeljpDR68YId5ecYQXE7vW23yzTtsfPNSJ0nzMLvuNQVdP9yTtGdbXWGi/m8Yzu74nFMYtrU2ycLyvGuU4235WN8ixEA4Hx1HDvaFOiLknN4xyKmjQc6+ncjBNlDRUN+igxyIBtvx87sA5/WPl4qIbcWBD46gPUHVWaqi6QkN7yU+axR5mPGK1NacznOQg5mq42mjDzZznRM4UWQ7/5Kt2b1Ym3Od08wIxwHEugZ5wM12NXQu3xpDjlF0onfagRwsOk8L7GCAw9sE73Vg23OOOa6ehzgfV7StLv6ooe1/zU0p2pGc3zeCHLqxy/U6cMloJysL8yC/Zt88w9rpIG8nudmg9yEYDiDWrRjn2Lr8VAMBMLRxUxxItYp6gY7LCY2BFODYjMg5vxM5kEb1rQA69Qe8CznwSQELso0tMs83boQ49oGqnPSdeuAstjfBgIz6Ir4JhA+0O+JnBnHIBKZ94KaI835B3xG+r7YbB5Y+3Oj3m/M/aCA+vN9AOjwOs988w+g3Wealrhdcs19Z3W/Q9mCJ+YALk9ILE/mFmJS7EFiMEz+hq/gWIZU5EpSJlIg94YMdDxEQmv95yp8OHCcNwyIRZvwCbEl/L9eEF9vA77VOTMnlZ4P7F7036adSa9TX549wrH1KwSh7ZhRxHTG2/RXAqn4lbzyC58+NBfbO9JiB9+RVPu5LHPGNVbn7In32YRMag/zwsYF+jndpjsSh6Uncd7gRYurBY/lUMsZ9BTE6t6piI+cnN0UOHTNAwm/Z4t5BzvpG+1QHaCQv37gF8Koi4juzNda5JWDbj6+LQ/DOBvGBs28QVxdsyb7nfm3Dj0TqFmniZyKX/uAWWrB1VLcTH6R3IOStkZTJZqLwgixLY195Iyy35ldXFh4xnbTlSzCWtrSV8fA9uI6rw+LKRZgXieXllorrBvoW0UYLHDfUsctL+v2M+dq+iMUVicyPYydTMTn1nVEollo5DGSo0X9n7hyLJxFB5Lpp4Acqpllpfd2SD1G0h5WO70cv0HgeXLpB4USZkAlOk/9ViW/clXx77sPvQuJaH/fki3y/GEelUzh6zzqJJcJ3MRaNN1fC1E9KHyXQ1ePqFtnyTp5SQfAbY5T4jsvFRW6HX8RJ5NlBeJ1zJ9or3b3N79nEiWt7cZ1D3k6r1N7zvtU8hEbmxGcaYltLNQh1i7JwN8T4dKgHtjWX2D2MDOVurcnlI/PBMzqEB18+4JE7XKcWWb9InUz2+Ux0ZKeWpun8jtDzKPdwnGWx7/qp4ioiHdNvNNo5dSPfttNAlIkzOwOagUc14c4kXGTQ7XlP+E7cRq4bF0B2CLHZ2jpV+9Z7njzzu7QdD6+3kr27rLf7jw7jwkqS7JW35a2w+K5sx4PdAmnbx4/2eVBR4HXvULPVk9vq+ac188gla707jHGutmVHX0TDcBVXF+M=
*/