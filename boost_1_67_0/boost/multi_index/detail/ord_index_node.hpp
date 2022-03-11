/* Copyright 2003-2019 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 *
 * The internal implementation of red-black trees is based on that of SGI STL
 * stl_tree.h file: 
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_NODE_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_NODE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <cstddef>
#include <boost/multi_index/detail/allocator_traits.hpp>
#include <boost/multi_index/detail/raw_ptr.hpp>

#if !defined(BOOST_MULTI_INDEX_DISABLE_COMPRESSED_ORDERED_INDEX_NODES)
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/detail/uintptr_type.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* definition of red-black nodes for ordered_index */

enum ordered_index_color{red=false,black=true};
enum ordered_index_side{to_left=false,to_right=true};

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_impl; /* fwd decl. */

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_traits
{
  typedef typename rebind_alloc_for<
    Allocator,
    ordered_index_node_impl<AugmentPolicy,Allocator>
  >::type                                            allocator;
  typedef allocator_traits<allocator>                alloc_traits;
  typedef typename alloc_traits::pointer             pointer;
  typedef typename alloc_traits::const_pointer       const_pointer;
  typedef typename alloc_traits::difference_type     difference_type;
  typedef typename alloc_traits::size_type           size_type;
};

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_std_base
{
  typedef ordered_index_node_traits<
    AugmentPolicy,Allocator>                    node_traits;
  typedef typename node_traits::allocator       node_allocator;
  typedef typename node_traits::pointer         pointer;
  typedef typename node_traits::const_pointer   const_pointer;
  typedef typename node_traits::difference_type difference_type;
  typedef typename node_traits::size_type       size_type;
  typedef ordered_index_color&                  color_ref;
  typedef pointer&                              parent_ref;

  ordered_index_color& color(){return color_;}
  ordered_index_color  color()const{return color_;}
  pointer&             parent(){return parent_;}
  pointer              parent()const{return parent_;}
  pointer&             left(){return left_;}
  pointer              left()const{return left_;}
  pointer&             right(){return right_;}
  pointer              right()const{return right_;}

private:
  ordered_index_color color_; 
  pointer             parent_;
  pointer             left_;
  pointer             right_;
};

#if !defined(BOOST_MULTI_INDEX_DISABLE_COMPRESSED_ORDERED_INDEX_NODES)
/* If ordered_index_node_impl has even alignment, we can use the least
 * significant bit of one of the ordered_index_node_impl pointers to
 * store color information. This typically reduces the size of
 * ordered_index_node_impl by 25%.
 */

#if defined(BOOST_MSVC)
/* This code casts pointers to an integer type that has been computed
 * to be large enough to hold the pointer, however the metaprogramming
 * logic is not always spotted by the VC++ code analyser that issues a
 * long list of warnings.
 */

#pragma warning(push)
#pragma warning(disable:4312 4311)
#endif

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_compressed_base
{
  typedef ordered_index_node_traits<
    AugmentPolicy,Allocator>                    node_traits;
  typedef ordered_index_node_impl<
    AugmentPolicy,Allocator>*                   pointer;
  typedef const ordered_index_node_impl<
    AugmentPolicy,Allocator>*                   const_pointer;
  typedef typename node_traits::difference_type difference_type;
  typedef typename node_traits::size_type       size_type;

  struct color_ref
  {
    color_ref(uintptr_type* r_):r(r_){}
    color_ref(const color_ref& x):r(x.r){}
    
    operator ordered_index_color()const
    {
      return ordered_index_color(*r&uintptr_type(1));
    }
    
    color_ref& operator=(ordered_index_color c)
    {
      *r&=~uintptr_type(1);
      *r|=uintptr_type(c);
      return *this;
    }
    
    color_ref& operator=(const color_ref& x)
    {
      return operator=(x.operator ordered_index_color());
    }
    
  private:
    uintptr_type* r;
  };
  
  struct parent_ref
  {
    parent_ref(uintptr_type* r_):r(r_){}
    parent_ref(const parent_ref& x):r(x.r){}
    
    operator pointer()const
    {
      return (pointer)(void*)(*r&~uintptr_type(1));
    }
    
    parent_ref& operator=(pointer p)
    {
      *r=((uintptr_type)(void*)p)|(*r&uintptr_type(1));
      return *this;
    }
    
    parent_ref& operator=(const parent_ref& x)
    {
      return operator=(x.operator pointer());
    }

    pointer operator->()const
    {
      return operator pointer();
    }

  private:
    uintptr_type* r;
  };
  
  color_ref           color(){return color_ref(&parentcolor_);}
  ordered_index_color color()const
  {
    return ordered_index_color(parentcolor_&uintptr_type(1));
  }

  parent_ref parent(){return parent_ref(&parentcolor_);}
  pointer    parent()const
  {
    return (pointer)(void*)(parentcolor_&~uintptr_type(1));
  }

  pointer& left(){return left_;}
  pointer  left()const{return left_;}
  pointer& right(){return right_;}
  pointer  right()const{return right_;}

private:
  uintptr_type parentcolor_;
  pointer      left_;
  pointer      right_;
};
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif
#endif

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_impl_base:

#if !defined(BOOST_MULTI_INDEX_DISABLE_COMPRESSED_ORDERED_INDEX_NODES)
  AugmentPolicy::template augmented_node<
    typename mpl::if_c<
      !(has_uintptr_type::value)||
      (alignment_of<
        ordered_index_node_compressed_base<AugmentPolicy,Allocator>
       >::value%2)||
      !(is_same<
        typename ordered_index_node_traits<AugmentPolicy,Allocator>::pointer,
        ordered_index_node_impl<AugmentPolicy,Allocator>*>::value),
      ordered_index_node_std_base<AugmentPolicy,Allocator>,
      ordered_index_node_compressed_base<AugmentPolicy,Allocator>
    >::type
  >::type
#else
  AugmentPolicy::template augmented_node<
    ordered_index_node_std_base<AugmentPolicy,Allocator>
  >::type
#endif

{};

template<typename AugmentPolicy,typename Allocator>
struct ordered_index_node_impl:
  ordered_index_node_impl_base<AugmentPolicy,Allocator>
{
private:
  typedef ordered_index_node_impl_base<AugmentPolicy,Allocator> super;

public:
  typedef typename super::color_ref                             color_ref;
  typedef typename super::parent_ref                            parent_ref;
  typedef typename super::pointer                               pointer;
  typedef typename super::const_pointer                         const_pointer;

  /* interoperability with bidir_node_iterator */

  static void increment(pointer& x)
  {
    if(x->right()!=pointer(0)){
      x=x->right();
      while(x->left()!=pointer(0))x=x->left();
    }
    else{
      pointer y=x->parent();
      while(x==y->right()){
        x=y;
        y=y->parent();
      }
      if(x->right()!=y)x=y;
    }
  }

  static void decrement(pointer& x)
  {
    if(x->color()==red&&x->parent()->parent()==x){
      x=x->right();
    }
    else if(x->left()!=pointer(0)){
      pointer y=x->left();
      while(y->right()!=pointer(0))y=y->right();
      x=y;
    }else{
      pointer y=x->parent();
      while(x==y->left()){
        x=y;
        y=y->parent();
      }
      x=y;
    }
  }

  /* algorithmic stuff */

  static void rotate_left(pointer x,parent_ref root)
  {
    pointer y=x->right();
    x->right()=y->left();
    if(y->left()!=pointer(0))y->left()->parent()=x;
    y->parent()=x->parent();
    
    if(x==root)                    root=y;
    else if(x==x->parent()->left())x->parent()->left()=y;
    else                           x->parent()->right()=y;
    y->left()=x;
    x->parent()=y;
    AugmentPolicy::rotate_left(x,y);
  }

  static pointer minimum(pointer x)
  {
    while(x->left()!=pointer(0))x=x->left();
    return x;
  }

  static pointer maximum(pointer x)
  {
    while(x->right()!=pointer(0))x=x->right();
    return x;
  }

  static void rotate_right(pointer x,parent_ref root)
  {
    pointer y=x->left();
    x->left()=y->right();
    if(y->right()!=pointer(0))y->right()->parent()=x;
    y->parent()=x->parent();

    if(x==root)                     root=y;
    else if(x==x->parent()->right())x->parent()->right()=y;
    else                            x->parent()->left()=y;
    y->right()=x;
    x->parent()=y;
    AugmentPolicy::rotate_right(x,y);
  }

  static void rebalance(pointer x,parent_ref root)
  {
    x->color()=red;
    while(x!=root&&x->parent()->color()==red){
      if(x->parent()==x->parent()->parent()->left()){
        pointer y=x->parent()->parent()->right();
        if(y!=pointer(0)&&y->color()==red){
          x->parent()->color()=black;
          y->color()=black;
          x->parent()->parent()->color()=red;
          x=x->parent()->parent();
        }
        else{
          if(x==x->parent()->right()){
            x=x->parent();
            rotate_left(x,root);
          }
          x->parent()->color()=black;
          x->parent()->parent()->color()=red;
          rotate_right(x->parent()->parent(),root);
        }
      }
      else{
        pointer y=x->parent()->parent()->left();
        if(y!=pointer(0)&&y->color()==red){
          x->parent()->color()=black;
          y->color()=black;
          x->parent()->parent()->color()=red;
          x=x->parent()->parent();
        }
        else{
          if(x==x->parent()->left()){
            x=x->parent();
            rotate_right(x,root);
          }
          x->parent()->color()=black;
          x->parent()->parent()->color()=red;
          rotate_left(x->parent()->parent(),root);
        }
      }
    }
    root->color()=black;
  }

  static void link(
    pointer x,ordered_index_side side,pointer position,pointer header)
  {
    if(side==to_left){
      position->left()=x;  /* also makes leftmost=x when parent==header */
      if(position==header){
        header->parent()=x;
        header->right()=x;
      }
      else if(position==header->left()){
        header->left()=x;  /* maintain leftmost pointing to min node */
      }
    }
    else{
      position->right()=x;
      if(position==header->right()){
        header->right()=x; /* maintain rightmost pointing to max node */
      }
    }
    x->parent()=position;
    x->left()=pointer(0);
    x->right()=pointer(0);
    AugmentPolicy::add(x,pointer(header->parent()));
    ordered_index_node_impl::rebalance(x,header->parent());
  }

  static pointer rebalance_for_erase(
    pointer z,parent_ref root,pointer& leftmost,pointer& rightmost)
  {
    pointer y=z;
    pointer x=pointer(0);
    pointer x_parent=pointer(0);
    if(y->left()==pointer(0)){    /* z has at most one non-null child. y==z. */
      x=y->right();               /* x might be null */
    }
    else{
      if(y->right()==pointer(0)){ /* z has exactly one non-null child. y==z. */
        x=y->left();              /* x is not null */
      }
      else{                       /* z has two non-null children.  Set y to */
        y=y->right();             /* z's successor. x might be null.        */
        while(y->left()!=pointer(0))y=y->left();
        x=y->right();
      }
    }
    AugmentPolicy::remove(y,pointer(root));
    if(y!=z){
      AugmentPolicy::copy(z,y);
      z->left()->parent()=y;   /* relink y in place of z. y is z's successor */
      y->left()=z->left();
      if(y!=z->right()){
        x_parent=y->parent();
        if(x!=pointer(0))x->parent()=y->parent();
        y->parent()->left()=x; /* y must be a child of left */
        y->right()=z->right();
        z->right()->parent()=y;
      }
      else{
        x_parent=y;
      }

      if(root==z)                    root=y;
      else if(z->parent()->left()==z)z->parent()->left()=y;
      else                           z->parent()->right()=y;
      y->parent()=z->parent();
      ordered_index_color c=y->color();
      y->color()=z->color();
      z->color()=c;
      y=z;                    /* y now points to node to be actually deleted */
    }
    else{                     /* y==z */
      x_parent=y->parent();
      if(x!=pointer(0))x->parent()=y->parent();   
      if(root==z){
        root=x;
      }
      else{
        if(z->parent()->left()==z)z->parent()->left()=x;
        else                      z->parent()->right()=x;
      }
      if(leftmost==z){
        if(z->right()==pointer(0)){ /* z->left() must be null also */
          leftmost=z->parent();
        }
        else{              
          leftmost=minimum(x);      /* makes leftmost==header if z==root */
        }
      }
      if(rightmost==z){
        if(z->left()==pointer(0)){  /* z->right() must be null also */
          rightmost=z->parent();
        }
        else{                   /* x==z->left() */
          rightmost=maximum(x); /* makes rightmost==header if z==root */
        }
      }
    }
    if(y->color()!=red){
      while(x!=root&&(x==pointer(0)|| x->color()==black)){
        if(x==x_parent->left()){
          pointer w=x_parent->right();
          if(w->color()==red){
            w->color()=black;
            x_parent->color()=red;
            rotate_left(x_parent,root);
            w=x_parent->right();
          }
          if((w->left()==pointer(0)||w->left()->color()==black) &&
             (w->right()==pointer(0)||w->right()->color()==black)){
            w->color()=red;
            x=x_parent;
            x_parent=x_parent->parent();
          } 
          else{
            if(w->right()==pointer(0 )
                || w->right()->color()==black){
              if(w->left()!=pointer(0)) w->left()->color()=black;
              w->color()=red;
              rotate_right(w,root);
              w=x_parent->right();
            }
            w->color()=x_parent->color();
            x_parent->color()=black;
            if(w->right()!=pointer(0))w->right()->color()=black;
            rotate_left(x_parent,root);
            break;
          }
        } 
        else{                   /* same as above,with right <-> left */
          pointer w=x_parent->left();
          if(w->color()==red){
            w->color()=black;
            x_parent->color()=red;
            rotate_right(x_parent,root);
            w=x_parent->left();
          }
          if((w->right()==pointer(0)||w->right()->color()==black) &&
             (w->left()==pointer(0)||w->left()->color()==black)){
            w->color()=red;
            x=x_parent;
            x_parent=x_parent->parent();
          }
          else{
            if(w->left()==pointer(0)||w->left()->color()==black){
              if(w->right()!=pointer(0))w->right()->color()=black;
              w->color()=red;
              rotate_left(w,root);
              w=x_parent->left();
            }
            w->color()=x_parent->color();
            x_parent->color()=black;
            if(w->left()!=pointer(0))w->left()->color()=black;
            rotate_right(x_parent,root);
            break;
          }
        }
      }
      if(x!=pointer(0))x->color()=black;
    }
    return y;
  }

  static void restore(pointer x,pointer position,pointer header)
  {
    if(position->left()==pointer(0)||position->left()==header){
      link(x,to_left,position,header);
    }
    else{
      decrement(position);
      link(x,to_right,position,header);
    }
  }

#if defined(BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING)
  /* invariant stuff */

  static std::size_t black_count(pointer node,pointer root)
  {
    if(node==pointer(0))return 0;
    std::size_t sum=0;
    for(;;){
      if(node->color()==black)++sum;
      if(node==root)break;
      node=node->parent();
    } 
    return sum;
  }
#endif
};

template<typename AugmentPolicy,typename Super>
struct ordered_index_node_trampoline:
  ordered_index_node_impl<
    AugmentPolicy,
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  >
{
  typedef ordered_index_node_impl<
    AugmentPolicy,
    typename rebind_alloc_for<
      typename Super::allocator_type,
      char
    >::type
  > impl_type;
};

template<typename AugmentPolicy,typename Super>
struct ordered_index_node:
  Super,ordered_index_node_trampoline<AugmentPolicy,Super>
{
private:
  typedef ordered_index_node_trampoline<AugmentPolicy,Super> trampoline;

public:
  typedef typename trampoline::impl_type       impl_type;
  typedef typename trampoline::color_ref       impl_color_ref;
  typedef typename trampoline::parent_ref      impl_parent_ref;
  typedef typename trampoline::pointer         impl_pointer;
  typedef typename trampoline::const_pointer   const_impl_pointer;
  typedef typename trampoline::difference_type difference_type;
  typedef typename trampoline::size_type       size_type;

  impl_color_ref      color(){return trampoline::color();}
  ordered_index_color color()const{return trampoline::color();}
  impl_parent_ref     parent(){return trampoline::parent();}
  impl_pointer        parent()const{return trampoline::parent();}
  impl_pointer&       left(){return trampoline::left();}
  impl_pointer        left()const{return trampoline::left();}
  impl_pointer&       right(){return trampoline::right();}
  impl_pointer        right()const{return trampoline::right();}

  impl_pointer impl()
  {
    return static_cast<impl_pointer>(
      static_cast<impl_type*>(static_cast<trampoline*>(this)));
  }

  const_impl_pointer impl()const
  {
    return static_cast<const_impl_pointer>(
      static_cast<const impl_type*>(static_cast<const trampoline*>(this)));
  }

  static ordered_index_node* from_impl(impl_pointer x)
  {
    return
      static_cast<ordered_index_node*>(
        static_cast<trampoline*>(
          raw_ptr<impl_type*>(x)));
  }

  static const ordered_index_node* from_impl(const_impl_pointer x)
  {
    return
      static_cast<const ordered_index_node*>(
        static_cast<const trampoline*>(
          raw_ptr<const impl_type*>(x)));
  }

  /* interoperability with bidir_node_iterator */

  static void increment(ordered_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::increment(xi);
    x=from_impl(xi);
  }

  static void decrement(ordered_index_node*& x)
  {
    impl_pointer xi=x->impl();
    trampoline::decrement(xi);
    x=from_impl(xi);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_node.hpp
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
*/