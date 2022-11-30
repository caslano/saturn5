/* Copyright 2003-2021 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_NODE_HANDLE_HPP
#define BOOST_MULTI_INDEX_DETAIL_NODE_HANDLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>
#include <boost/core/addressof.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp> 
#include <new>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Node handle template class following [container.node] specs.
 */

#include <boost/multi_index/detail/define_if_constexpr_macro.hpp>

template<typename Node,typename Allocator>
class node_handle
{
public:
  typedef typename Node::value_type        value_type;
  typedef Allocator                        allocator_type;

private:
  typedef allocator_traits<allocator_type> alloc_traits;

public:
  node_handle()BOOST_NOEXCEPT:node(0){}

  node_handle(BOOST_RV_REF(node_handle) x)BOOST_NOEXCEPT:node(x.node)
  {
    if(!x.empty()){
      move_construct_allocator(boost::move(x));
      x.destroy_allocator();
      x.node=0;
    }
  }

  ~node_handle()
  {
    if(!empty()){
      delete_node();
      destroy_allocator();
    }
  }

  node_handle& operator=(BOOST_RV_REF(node_handle) x)
  {
    if(this!=&x){
      if(!empty()){
        delete_node();
        if(!x.empty()){
          BOOST_MULTI_INDEX_IF_CONSTEXPR(
            alloc_traits::propagate_on_container_move_assignment::value){
            move_assign_allocator(boost::move(x));
          }
          x.destroy_allocator();
        }
        else{
          destroy_allocator();
        }
      }
      else if(!x.empty()){
        move_construct_allocator(boost::move(x));
        x.destroy_allocator();
      }
      node=x.node;
      x.node=0;
    }
    return *this;
  }

  value_type& value()const{return node->value();}
  allocator_type get_allocator()const{return *allocator_ptr();}

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS)
  explicit
#endif
  operator bool()const BOOST_NOEXCEPT{return (node!=0);}

#if BOOST_WORKAROUND(BOOST_GCC_VERSION,>=70000)&&__cplusplus<201103L
  /* https://github.com/boostorg/config/issues/336 */
#else
  BOOST_ATTRIBUTE_NODISCARD 
#endif
  bool empty()const BOOST_NOEXCEPT{return (node==0);}

  void swap(node_handle& x)
    BOOST_NOEXCEPT_IF(
      alloc_traits::propagate_on_container_swap::value||
      alloc_traits::is_always_equal::value)
  {
    if(!empty()){
      if(!x.empty()){
        BOOST_MULTI_INDEX_IF_CONSTEXPR(
          alloc_traits::propagate_on_container_swap::value){
          using std::swap;
          swap(*allocator_ptr(),*x.allocator_ptr());
        }
      }
      else{
        x.move_construct_allocator(boost::move(*this));
        destroy_allocator();
      }
    }
    else if(!x.empty()){
      move_construct_allocator(boost::move(x));
      x.destroy_allocator();
    }
    std::swap(node,x.node);
  }

  friend void swap(node_handle& x,node_handle& y)
    BOOST_NOEXCEPT_IF(noexcept(x.swap(y)))
  {
    x.swap(y);
  }

private:
  BOOST_MOVABLE_BUT_NOT_COPYABLE(node_handle)

  template <typename,typename,typename>
  friend class boost::multi_index::multi_index_container;

  node_handle(Node* node_,const allocator_type& al):node(node_)
  {
    ::new (static_cast<void*>(allocator_ptr())) allocator_type(al);
  }

  void release_node()
  {
    if(!empty()){
      node=0;
      destroy_allocator();
    }
  }

#include <boost/multi_index/detail/ignore_wstrict_aliasing.hpp>

  const allocator_type* allocator_ptr()const
  {
    return reinterpret_cast<const allocator_type*>(&space);
  }

  allocator_type* allocator_ptr()
  {
    return reinterpret_cast<allocator_type*>(&space);
  }

#include <boost/multi_index/detail/restore_wstrict_aliasing.hpp>

  void move_construct_allocator(BOOST_RV_REF(node_handle) x)
  {
    ::new (static_cast<void*>(allocator_ptr()))
      allocator_type(boost::move(*x.allocator_ptr()));
  }

  void move_assign_allocator(BOOST_RV_REF(node_handle) x)
  {
    *allocator_ptr()=boost::move(*x.allocator_ptr());
  }

  void destroy_allocator(){allocator_ptr()->~allocator_type();}

  void delete_node()
  {
    typedef typename rebind_alloc_for<
      allocator_type,Node
    >::type                                          node_allocator;
    typedef detail::allocator_traits<node_allocator> node_alloc_traits;
    typedef typename node_alloc_traits::pointer      node_pointer;

    alloc_traits::destroy(*allocator_ptr(),boost::addressof(node->value()));
    node_allocator nal(*allocator_ptr());
    node_alloc_traits::deallocate(nal,static_cast<node_pointer>(node),1);
  }

  Node*                                 node;
  typename aligned_storage<
    sizeof(allocator_type),
    alignment_of<allocator_type>::value
  >::type                               space;
};

#include <boost/multi_index/detail/undef_if_constexpr_macro.hpp>

/* node handle insert return type template class following
 * [container.insert.return] specs.
 */

template<typename Iterator,typename NodeHandle>
struct insert_return_type
{
  insert_return_type(
    Iterator position_,bool inserted_,BOOST_RV_REF(NodeHandle) node_):
    position(position_),inserted(inserted_),node(boost::move(node_)){}
  insert_return_type(BOOST_RV_REF(insert_return_type) x):
    position(x.position),inserted(x.inserted),node(boost::move(x.node)){}

  insert_return_type& operator=(BOOST_RV_REF(insert_return_type) x)
  {
    position=x.position;
    inserted=x.inserted;
    node=boost::move(x.node);
    return *this;
  }

  Iterator   position;
  bool       inserted;
  NodeHandle node;

private:
  BOOST_MOVABLE_BUT_NOT_COPYABLE(insert_return_type)
};

/* utility for SFINAEing merge and related operations */

#if !defined(BOOST_NO_SFINAE)

#define BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(Dst,Src,T)           \
typename enable_if_c<                                              \
  !is_const< Dst >::value&&!is_const< Src >::value&&               \
  is_same<typename Dst::node_type,typename Src::node_type>::value, \
  T                                                                \
>::type

#else

#define BOOST_MULTI_INDEX_ENABLE_IF_MERGEABLE(Dst,Src,T) T

#endif

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* node_handle.hpp
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
*/