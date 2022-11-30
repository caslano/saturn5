/* Copyright 2003-2020 Joaquin M Lopez Munoz.
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

  static pointer rebalance_for_extract(
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
zXLY7A15wpkv+wsO/9vTBt9O3lmwxVjOiAnyd6eg/EiNXfmm+UFE0sZocoWQ4Z8PdR0EW5VXkfSXvFK5mKMKt5wRvIxfX4F9emwBiMLmL9mRK6F4mv1yZWyoOH/ACR698TKAlAWIEXBG6jJZXFYGjshLN6Cp/VgyNW3ALd45uKu1tkn7DChRzH9Bcoll0HvIiYo1wFh1qd6DZnQjwAt2Bv5JZALZP/28EOoK/7kk4YKpEpYvGnnwYkeipqohUOqi6hC8ey7gqsZYiX4205R2HVSC7gQCfwvG8FHNMNWd/0UxcjoNc5u4vpJVuxZBMla6xGVOKXpaLYu+usHTPNNRHx9YIPrsK5msSU6qv2oE+Stnar+clgeUNExJaywwfi8PF1v3kVZ5LZAYeo+sHQyeSewm0FWVTLoS5sJsoaiwwbz260mHTJPH8S94STX11YXYmt6P/mD6iO1uRM2KneP6P1WXaJOHex4JXaRNwyfStEtQMU68PPcKmLSuKGkcitpzwoyUIqEytiaGjcuhN/xaCrA7X42h/vu8nxFhEgOlV6gP7JIKpH3tPXm7pYiqOTtFLZnOxmtdtt0Alyqq6CeONfEJl2GtSH6FHivarJotCkr2wn3YPGz+j+hLvUYqcrrqghABh+hQPQevu/mz4xgvgwx+hDOb2nRaRxCBBGAKLHyaWrHrHnwbWSE6f4Fg9a52d+6qOKf1gWjrhlmCPv4KJ3gVD+GOCeP3/gy+n6iiqzvbdH+rnF6egtrtbzRzWEyJUJMdLy0WY8dKmN7A0MujMX64sdZabsrb2i5qQW2HRJdv9Aeg5WZXaYWkrNrXoZ7r5PuaGEO/0cMNgYW62s2KITxES73Wj1RqPmpbtQO6140x5Sahkl0LkRFUuHKtH8LjG30VuC7NxLfNVMv0g3ncZyytkFta7jTfIKKn9t7hsGKkfvlDIpxbA71VkOJm/OR79s3VqwCztexeDbHNXW4CoA7bocSjuapSdv2XVn4BlTkgBDEX/RvDh7sDk/56uyAeXPpAeZfxSR3N8R33rkPpPRRzNJxhbFQhwSaNxaAAK8999vlwaIk8jUJDcyMuOQ2naN+kx03x3pLa21WYXtKSNPmBKxFyKaxndSZ2Jp5UXAgwhavTljpLrZU2SBvEl7zBh6cgNS8+91st1rqeyn7YyB6Btak0xco6YAYqGcX6vYsZZbFD5uDQgsMYTPjBfHk9hNSmpbGu5bvWelbLG4ca9HB0ZcsDhxM1CvX2GjSchs31J5Nb/CW+f4o9r1RTx3Gj/ENT7LT8VSHTTaXnZOs+y3xQJQUmuJUhJEij6clTud11l3Wqg/NwQB5vdtn+FYjWIomeR2p+C3Vu7z0xkKusrOXoCjdKBO9lbsq0dqW2GOULvH/PD48fPhbwRmHJJ08o4GAIKQOQ1SrWnx0rPaV9a39FnYuLbfUGgqJjsmGXVw9r+Sp1eaghH+nv7cx07/ClUtiiCM60uYDdpnXrkoOjto5W47sbNdO9rpWrcKZoYohcP3U8N7vZ8t32BxS+Pwhc9MyHvNVmzN0NPBKslxkKJY51MQI9nT1ycWlxdSuZTQYMfjglDeoxX22unLkYpsMPcrW6es+d0V5+fgWInDzHIvx6xDXnrWs+9KVpvOoLg+wJNbsIsIGMNU7ljLaa7WMy8NXy+0HGKCjft9SSjV/W4uW+eFgrtSa3esgObp1dk3wWZPTMBlJBvfFvRuN58bL5aHG1vVgTzStc+fq7zfnBrQB6njzcAzcu71SbocUwC3bLpaXfrJVtbu3BUvqwF1D4V2vZi+AxnQZaXcEVo97THCk8e5gbu7XkwCzS3Yo9EJoovdcEuPw1aWQ7Xaxbakj60xWtMk09R9ff8jDBg8fWb3TgC++xZZtzNthPL7IXBMhLR/A9g7EXo2D9QJMwsn0FKCu4pCq5Ax9TwCZn8aldqinsCohGEgbqhxtLv7gCElEkfN9848bFVFD+zvt0ZaS73NQXwaJukGlX0bvgjmNZZySeajxRvU2gfbkiHVJjdh/cBBF5mvVSFdESF7jbt9s6jhz66eG5DiXHRqG3gq8FXpVieD7nQCen8Inz0gjdBZVAf7MOnZwrCiX1KrwZJVfIiXaXQjlvTeqiC/ilUyBQ1LLqymRHl1Aw3ovLKq5+w+ivafGzwigB9wl5Bvs65zZMAaDQRpA6Q5+imXdIKi54HRcKfId/mV3r6unF5fpACA1KCP+p9mFQ4dQDb97VctMYpIBbMn1VdXWBzvDO1Yp3WnSUgPspJ8QIyeZme9XVNri56lHZTDCT9+1Ab1kgM2JlQPs8AlrGcEMLss+MUHdqocMEZ39qUT2rKMaAimyDmIzg1Fm6vPP5e6ZhWTWvHlYjBfa3LiaRS0iOZvm1lsDlcC5IK0Xrhp6dUS6a33sSSumanDRQW+l0g3KAWfWST0rpiiKCJJ6Z1LmCfj2YcK0tXCfcUITy8yrK8Kav48GRkHTWMPW0skBmQ7+/f6T7XwHPNNOSwA0hWkpK5G//OxsRgccwr27jW+7axc0w991dyfSbrqqPhi88r4Cnx6jJL6SRY/1s+MOJaiysMBe6uvsEiGg7Ae9rEsgAekwvsNUsYOgTjFqwtc+SVzsNM4ewE5XtY/9DC3M+hLp4AjFhHGAmvmi2Da2LWlrbG3wMPetn7wGU5fVI9jBZE8/Mrjb5B+sa/to2H9O1o0IBctg1IKthf10affltjth9b39ctgjS47nNp1WM1g8KMEXI9gOn6XhcGApm0qYSaQly9M8NOOMJLbhDMI+rMjknwJxyceafuLQ4W193YQbyHQMXcmlxj5QYIji76MKdXmztGrTFPd1fYX1LN1QRCI6UnwMBh6VK2eXHmH3FmmfAMRLayB21+ufkC6tBuRPIBycJsiSwG6DmmPQZUkZ6vd4CU+fZx594mRFvp0qtqbVAKFQ7MonlRk4p/Hs5oDNdw90bXYB/EpHDAFb23zLXmCGvhIy0P1QDQR+yClIkcUHA2R68BTNYeujiiosrxcjs3U1PP56grKuncct884Dcy/iUdts6PlXh1tJlEnfkarlSIvHg2HR9uf5JNqzXunY0POqpRrTYXt3xcfYbDVBttkm44+PY+6h49K21I6zQEgBDaPa7b6BsOnLsEiLJZ7MPODw/kc0/qtVlDNGmiMmzQ4ehCqyd0yLoNYbKXAb2gP25byAaCxEk6DaVeYKDWP/1s4BYRPy6gxGzV0rozvS3BHL/tqSb+jqFbLLG/p+PiPlNIvO1XZIbEWGNrPE890bYBVv8wI645KS0rr8+/pHJSh9/YmSl52BmbWgMnyvwUuNFrbFXHrvAwCaaM7ZOn6VFKQdhGKuKxL7FACnZN83xDrlL46ipgqEknGP/V9UHAndEB3XhT11u2ei30RrqPXZH/nqalqnXdNPusarfq0+cpE3bbtDjqHAKD1zv00dbIXn5ixCqDfvp4xZJymUonwJupPUfY5bR/fWRGLX6hFOvwYAZSeMtcjX09TXS2XkuRKH3Dqd1RUTBZEnrBFLTF4KNNUOZM85u0rC/pk42E4aVJwJfDM/NTPzrNooFkhB/YRh8T29x1RMnf+kTYHjy+SYzcS9ynpBTnhQmk477qpdNNQuqjiWDEnnGZtBNOSAPyDVoTtTDDrgJfn3s0ne/RH9G4xns1sFYrWG5Dmg3h9Mk2WFQcxtjtEUvtt7gN0M0B46BF5Eu9r9YhzBiw8ruf9iDOqHbVq9sfEIhWfxKPIC/7rk7co6GAwa56fR3J7bnVPmHreNc7d8ediIAKY8nwKMpeENWFwosobLH+E1UY+Aarp5EhM5BELbozgNSyVelLLBEOeamvOhlMoD7uPeMo/CaSYcnIUu+aPCdynBLyDdtWOyPjAhlQBiwbbm9ChLBpcltl8JVssll14x1isbh4BBbijdW/Lc55zTeRN11+0XhHSrzMq0hFoh7oY29gfB5DEzZ2PayCb0cGmIN8pyV+85UWWaReLccqXMBrywImQ1yf5MlUQXXQe60sTYqx/ZLu6H2g+En3Gdbzn2aX3MwqyfeBsmTV6thgzrmSUbWxiePbAPxGm0O4VmyE+H0kJFHLjiRzrTZUjKqtAVyVqAisa4hyx3B7Orxz0JBbM9oHm7ZZlKcVL3nVtUPimYKvRu/KkoTezwrWi3oSoAj/JQy/yHZGo6f9AkQij6lk9eRkvVbiGCTX9dhMrq0ZcLD5UWStJsAsvr4oeSxUVtgdeJrBxvhr6LXgVRZqzzaaHmF3d+O7J34GPdNPTVETxF16/LtQNI3/P7Yg4jaQav8ZPXAvfb4tPvo+oe4hA8fgWeeYvSkEoI9vPFy7fa6krCmZeAek//SREPBsV4J0UChR+Fy3mYI7P0SVoaP2/IV/YRpNFROWHCLUMGBsM7P6WzOtq/F8yH8VwtOh5c03MMrb4xPl/PJQ2gkHuxqehEZzum7WFaMleKCo99h6aOHD3mC3kE6DNC6CmdCdSosnkNvFrrRvIJyCS42lz5yzhYO4joViYjn92yxqOFEl/mS+LpcxwJo4a8RRgukzr97D2IkcJ4+iXxnbB/KXxTK0NIQ1lZp9oKXHddoGh0hHzMvYbPyw0nPtT+/b+LMk99EJTCia50JnON/mxDg7a2tNR2vnZ3uR3HA5Ww+GF05hsmcvwkQoAI9NQj2yh+/KXE+DiUnnYQ/PHg04ABBD1ezUWgOF0AKiGNko2LiQei8rKb9sgICmm8UzQvTidMiNz9D3vwl4eVXxfEl3ugR/NTENHm4RE9GUGH34zPxHUmvarYYN93V1khMhBPAyc6EHSaTDxd9JE9we5dkp7cb2DfVtqtUkMJ3UIYALhWbxqdf2du8Gfhd2tUigIg4j0Tk8MDDwo4KteKsFzPal2AFOubGMAO6J47ZcxtoWw2viQt22Vtol5HihV9H69E88BBuNC6PQYNr7SP7mM4vkPsvtvPjYhFzXFHWYhFo9gc/FtRrEFtQ8PykkmlMtkwFkex7kLKgzdcokmy59LsdVpLSMWIHYZSpiUG/hTrO4t8pJiF4lp7PD45gwTySCJfQchEOd/vt8KCmK2FHTqulSplEpTJuF0mSR8mVKObJQ5NL/k6e4rkhORoTKJqN2vkz5Q4C82U3adcpyjoYs+s2XwOC3A4lQkF7rmePwk+MpLpRPoHMAyY7nz0ix7LR00Ef2zEXo8obV6+IjCNeiAznu2NvfHkoImEKfN8fvyjd3Ci398OdXyDhq2SWY+qBHGVKnb59vHrn+MztQtdyhUUbBvEq9NFfp+mUjiRQzNYtQ4kOF47DHwnkWA4OnvhixfZZsEiUqXWe53yRrvv9G87UWZSCjvILO69vZ9+2iq8jJk9XX56korVeGNgdRzPYh0+Noh2z0rPQXoMWXe7Ha0yDPgmS2bn5+Xt3E8gvhrNmCaJV2Fc8nQ5sfaAC8oG5v1QLqznYKRnf5ghJSN0iHoQTQMBqyWzJT6QjsK6JDSA7dPkf4p0xwHvyCDD7tFIPsQcvor2I7gy5loM082JHvRui/Jvtx/nCnZ0k5EBJqSbBTdAUNQ4XTRIE8RIgDlM0rqFv2SXXSrOHr74fWs7mCLGyQk90GMT+veaZqx8JnSkDQZq7+dCU1DNA6mRtyrK3o5tsuCGb7GsY8bcBOVTEbYMgOjmHW2PzP0W+A89pz9K4aTQlT9vv/svYz0HqRmeavptykI+JDWrd3K9m8iz/elKV4JIOVSFaL9V95lWC88fHNTFlNxhXzjduQKzdCt6QWILrhaJMw9c6wDeJ1HUN/b0nmgOcX3733Z+7cKJcA5LNf4N57g0DHmqnXtpQcsPweNE5Y8ujTxm8K0bLhHA0QRh+IahqFDOqg3j6QG13uChAOxcLk1WKJFzIlpdq96W5LEWNmzAJeaq+WJbOlBsHs9cFCaePApZH8AZ0qlV1qRMdwc61hxEenQNBvHG1PqWsFNwwIdKrahka3HuzsbfqxMIUm7Kp3qyibUuLr1hA7p2GPEJpQPI7ejRqT+1rMJIuhkVceldUW6TWuBKR2Vs3j5Sv1xNHN9FiCEElj6TIgHz0BW9kEZmrYDpCmVPCVqI5J7j77pdKeTRJ09ogwx3LTpSn0o1cqB3gcRbnV9kfMIuNfKhe+LlwC0XjPMt3pZnWg0pPA777MIU7RaJHxgpQbBYa+/2mwnkRTSnMOvZCePJfJN8g8Cot/xCXlr7fzVJZedVNxHyAv3SmKhGHGoviFCqIZBK5RXSz9GOmjDqk7wQGzk+waKC5fD0hGhUEUSXpkL4QRx8MV5wjE1NHqp/URqzCd5Xenl3YznLx4whCWmgJZlBShtm0eKul+Spvb0t4fEnOwRCHG/6kj9Jr09zztX0LozbNEyyM4s7zXR0iV1shXMd2eUWP8UD35qAkJKgImqCBsxnqS8KKF8c2nShJGGFfNPd+sxVM3bsiCApGPlyWITSypqcgWUtDkqcQWtLkeaMEL2/OHB9zdjmyVuvErgwmdnkP3ftnkKvr2u4PVbK7RjUL5QOZP2RFv9CwtohQHzY/sDjyBCMhsHKNRyh7HtyzS2YzHQeEWeu4RVDPB91GOTzMDtHLNch7HIKvvsrfRR3W/hqnL9Ja/AyM6xIZJs28KOX9ZeTcqrSpJjVkZidCIsUwR88Uu5DXcQ0VM3vdKa2Zys5yEB8wivRNSKy1/srKM1Gyz6HZgEA1asrNk0WQfbT+vAfGP0PvnR0ybTBOfgHZh9ueAdkH3oSZ55jCoVpuzH4LGkLBMnOmMnNky8rldmgMoz3Hienm9K1mzx5QHspPiHA+WjGVUQUz3JGrz3R+ulY4VnF++k+7wgpe+VR2QckSSqiBfcWQixhGqcnqccAtnpnF2CiEhZTfoJKUzzkhNyVPpEqB+in/RTyZ8wG8VshHeqb2lULSgdaQUPmgVR214s+LPS/oLcrAGz/8CSiTGKmZjq1TuANEoVVv3GqoO/6JNYVstcwdT8tEvhMf9hw1PA/98DzDJMq6e87Y33hG6hIJxjq7Uqx0/ZvsgGFmTExsdWJE36vDGhQK9Gv0Lks0xrrCvr57ASglbEqGGmaGgQOq2OFUVFBQYFs3P3QxzHvrRnb2ee/4/hF/FDUtdepz71uCjBdKRj/tEsGu9R66eOFHO720NKl2jX9wtCmJav61duU4YElODr9bM0kCSIqiV/XMHFLW1bPzOPlgpMtVFSHF0axGRYqQ+ClAtT0iMQlP/GqxQhwsGLw8VxK7CZNaRW39U6iC/gQPhnkut/moBJGMHOcFZRjQrLPiRvTKRfqYcN6tF2teRj10KqRVPjJ5CdPj3UDdhPAtcdaSlXb6BVmu835jc+4pY6iVdpWOFi7cv/mco6eoRjHtGmFYYbfwXon1TIyUECSh1ZI6q9wdRJ1cjMnoda2MEEXhOdJzFqQhnc72Eg4jUD88N0wYlXlj3I5XmLGj/wn/5VTpKXj5F0i6ysrC7Sf6mcmm5NKiERcC82YQ6LvXbIkfH+7NHfRS09xiDXvUx5D6/PiP5JQgceTgvJ28KsWGp01+eaFuyUUGn8to7u8StuI7gUX6IHtVE9jtZy7Pv7m+7sR53RKxatLe1afnfhWMezBWxNIJoFfMg1KMCo64lnpUUKXyiLHTGLckNo5ZYBL8
*/